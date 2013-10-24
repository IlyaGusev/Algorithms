#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <time.h>
#include <stdlib.h>

using namespace std;

template <class T> class File;
template <class T>
struct binary {
    T data;
    size_t pos;
    binary() : data(), pos(){}
    binary(T const & __t, size_t __p): data(__t), pos(__p){}
    binary(binary const & rhs) : data(rhs.data), pos(rhs.pos) {}
    binary& operator=(binary const & rhs){ data=rhs.data; pos=rhs.pos; return (*this);}
    operator T&() { return data; }
    operator T const &() const { return data; }
    binary& operator=(T const & rhs){ data=rhs; return (*this);}
    void flush(File<T>& f){
        f.fstr.seekp(pos*sizeof(T));
        f.fstr<<(*this);
    }
};
template <class T>
istream & operator>>(istream & is, binary<T> & wt) {
    is.read(reinterpret_cast<char *>(&static_cast<T &>(wt)), sizeof(T));
    return is;
}
template <class T>
ostream & operator<<(ostream & os, binary<T> const & wt) {
    os.write(reinterpret_cast<char const *>(&static_cast<T const &>(wt)), sizeof(T));
    os.flush();
    return os;
}
template <class T>
class File{
    string name;
    fstream fstr;
public:
    size_t cnt;
    File(string n) : name(n), fstr(name, ios_base::binary | ios_base::out | ios_base::in), cnt(0) {}
    ~File(){
        fstr.close();
    }
    binary<T> operator[](size_t);
    binary<T> insert(T const&);
    void insert(T const&, size_t);
    //void clean();
    friend class binary<T>;
};
template <class T> binary<T> File<T>::insert(T const & elem){
    binary<T> w(elem, cnt);
    fstr.seekp(cnt*sizeof(T));
    fstr<<w;
    cnt++;
    return (w);
}
template <class T> void File<T>::insert(T const & elem, size_t pos){
    binary<T> w(elem, pos);
    fstr.seekp(pos*sizeof(T));
    fstr<<w;
    if(pos*sizeof(T) == cnt*sizeof(T))
        cnt++;
}
template <class T> binary<T> File<T>::operator[](size_t pos){
    T p=T();
    binary<T> w(p, pos);
    fstr.seekg(pos*sizeof(T));
    fstr>>w;
    return w;
}


template <class T, int border>
class BTree{
    struct Node{
        size_t cnt;
        T keys[2*border-1];
        int children_pos[2*border];
        bool leaf;
        bool deleted;

        Node() : cnt(0),children_pos(), leaf(true), deleted(false) {
            for(int i=0; i<2*border-1; i++)
                children_pos[i]=-1;
        }
        Node(const Node& rhs): cnt(rhs.cnt), keys(), children_pos(), leaf(rhs.leaf), deleted(false) {
            for(int i=0; i<2*border-1; i++)
                keys[i]=rhs.keys[i];
            for(int i=0; i<2*border-1; i++)
                children_pos[i]=rhs.children_pos[i];
        }
        Node& operator=(const Node& rhs){
            cnt=rhs.cnt;
            for(int i=0; i<2*border-1; i++)
                keys[i]=rhs.keys[i];
            for(int i=0; i<2*border-1; i++)
                children_pos[i]=rhs.children_pos[i];
            leaf=rhs.leaf;
            return (*this);
        }
    };
    void split_child(binary<Node>&, int, binary<Node>&);
    void insert_nonfull(binary<Node>&, T);
    pair<binary<Node>&, int> findfnc(binary<Node>&, T);
    void removefnc(binary<Node>&, T key);
public:
    File<Node> f;
    int root_pos;
    BTree() : f("base.dat"), root_pos(){ Node r; f.insert(r); }

    pair<int, int> find(T key);
    void insert(T key);
    void remove(T key);
};

template <class T, int border>
    void BTree<T,border>::split_child(binary<Node>& parent, int median, binary<Node>& brother){
        Node z;
        binary<Node> dz=f.insert(z);
        z.leaf=brother.data.leaf;
        z.cnt=border-1;
        for(int j=0; j<border-1; j++){
            z.keys[j]=brother.data.keys[border+j];
        }
        if (!z.leaf)
            for(int j=0; j<border; j++)
                z.children_pos[j]=brother.data.children_pos[j+border];
        brother.data.cnt=border-1;
        for(int j=parent.data.cnt; j>=median+1; j--)
            parent.data.children_pos[j+1]=parent.data.children_pos[j];
        parent.data.children_pos[median+1]=dz.pos;
        for(int j=parent.data.cnt-1; j>=median; j--)
            parent.data.keys[j+1]=parent.data.keys[j];
        parent.data.keys[median]=brother.data.keys[border-1];
        parent.data.cnt++;
        brother.flush(f);
        dz=binary<Node>(z, dz.pos);
        dz.flush(f);
        parent.flush(f);
    }
template <class T, int border>
    void BTree<T,border>::insert(T key){
        binary<Node> r=f[root_pos];
        if(r.data.cnt==border*2-1){
            Node new_root;
            new_root.leaf=false;
            new_root.children_pos[0]=root_pos;
            binary<Node> ws=f.insert(new_root);
            root_pos=ws.pos;
            split_child(ws, 0, r);
            insert_nonfull(ws, key);
        }
        else
            insert_nonfull(r, key);
    }
template <class T, int border>
    void BTree<T,border>::insert_nonfull(binary<Node>& cur, T key){
        int i=cur.data.cnt;
        if (cur.data.cnt>=1)
            i=cur.data.cnt-1;
        if (cur.data.leaf){
            if(cur.data.cnt!=0)
                while(i>=0 && key<cur.data.keys[i]){
                    cur.data.keys[i+1]=cur.data.keys[i];
                    i--;
                }
            else
                i=-1;
            cur.data.keys[i+1]=key;
            cur.data.cnt++;
            cur.flush(f);
        }
        else{
            while(i>=0 && key<cur.data.keys[i])
                i--;
            i++;
            binary<Node> m=f[cur.data.children_pos[i]];
            if (m.data.cnt==2*border-1){
                split_child(cur, i, m);
                if (key>cur.data.keys[i]) i++;
            }
            m=f[cur.data.children_pos[i]];
            insert_nonfull(m, key);
        }
    }

template <class T, int border>
    pair<binary<typename BTree<T, border>::Node>&, int> BTree<T,border>::findfnc(binary<Node>& x, T key){
        int i=0;
        while(i<x.data.cnt && key>x.data.keys[i])
            i++;
        if (i<=x.data.cnt && key==x.data.keys[i])
            return pair<binary<Node>&, int>(x, i);
        if (x.data.leaf)
            return pair<binary<Node>&, int>(x, -1);
        else{
            binary<Node> n=f[x.data.children_pos[i]];
            return (findfnc(n, key));
        }
    }

template <class T, int border>
    pair<int, int> BTree<T,border>::find(T key){
        binary<Node> x=f[root_pos];
        pair<binary<Node>&, int> p=(findfnc(x, key));
        return pair<int, int>(p.first.pos, p.second);
    }

template <class T, int border>
    void BTree<T,border>::removefnc(binary<Node>& x, T key){
        //binary<Node> x=f[root_pos];
        int i=x.data.cnt-1;
        if (x.data.leaf){
            while(i>=0 && key<x.data.keys[i]) i--;
            if (i>=0){
                if(key==x.data.keys[i]){
                    for(int j=i; j<x.data.cnt-1; j++)
                        x.data.keys[j]=x.data.keys[j+1];
                    x.data.cnt--;
                }
                else
                    return;
            }
            x.flush(f);
            return;
        }
        else{
            while(i>=0 && key<x.data.keys[i]) i--;
            if(key==x.data.keys[i] && i>=0){
                int flagl=x.data.children_pos[i];
                int flagr=x.data.children_pos[i];
                binary<Node> l=f[flagl];
                binary<Node> r=f[flagr];
                if (l.data.cnt>=border && flagl!=-1 && flagr!=-1){
                    while (!l.data.leaf)
                        l=f[l.data.children_pos[l.data.cnt]];
                    T t_key=l.data.keys[l.data.cnt-1];
                    x.data.keys[i]=t_key;
                    x.flush(f);
                    cout<<"2a"<<endl;
                    removefnc(l, t_key);
                    return;
                }
                if (r.data.cnt>=border && flagl!=-1 && flagr!=-1){
                    while (!r.data.leaf)
                        r=f[r.data.children_pos[0]];
                    T t_key=r.data.keys[0];
                    x.data.keys[i]=t_key;
                    x.flush(f);
                    removefnc(r, t_key);
                    cout<<"2b"<<endl;
                    return;
                }
                if (flagl==-1){
                    for(int j=r.data.cnt-1; j>0; j--)
                        r.data.keys[j+1]=r.data.keys[j];
                    r.data.cnt++;
                    r.data.keys[0]=key;
                    l=r;
                } else
                if (flagr==-1){
                    l.data.keys[l.data.cnt]=key;
                    l.data.cnt++;
                }
                else{
                    l.data.keys[l.data.cnt]=key;
                    l.data.cnt+=border;
                    for (int j=0; j<border-1; j++)
                        l.data.keys[border+j]=r.data.keys[j];
                    r.data.deleted=1;
                }

                for(int j=i+1; j<x.data.cnt; j++)
                    x.data.children_pos[j]=x.data.children_pos[j+1];
                for(int j=i; j<x.data.cnt-1; j++)
                    x.data.keys[j]=x.data.keys[j+1];
                x.data.cnt--;
                cout<<"2c"<<endl;
                removefnc(l, key);
                l.flush(f);
                r.flush(f);
                x.flush(f);
                return;
            }
            else{
                //i key i+1
                binary<Node> c=f[x.data.children_pos[i+1]];
                if (c.data.cnt>border-1){
                    removefnc(c, key);
                    return;
                }
                else{
                    int flagl, flagm, flagr;
                    if(i!=-1){
                        flagl=x.data.children_pos[i];
                        flagm=x.data.children_pos[i+1];
                        flagr=x.data.children_pos[i+2];
                    }
                    else{
                        flagl=-1;
                        flagm=x.data.children_pos[i+1];
                        flagr=x.data.children_pos[i+2];
                    }
                    if (flagm==-1) return;
                    binary<Node> l=f[x.data.children_pos[i]];
                    if (l.data.cnt>=border && flagl!=-1){
                        T t_key=x.data.keys[i+2];
                        int t_pos=l.data.children_pos[l.data.cnt];
                        l.data.cnt--;

                        x.data.keys[i+1]=l.data.keys[l.data.cnt-1];
                        for(int j=c.data.cnt-1; j>0; j--)
                            c.data.keys[j+1]=c.data.keys[j];
                        for(int j=c.data.cnt; j>0; j--)
                            c.data.children_pos[j+1]=c.data.children_pos[j];
                        c.data.cnt++;
                        c.data.keys[0]=t_key;
                        c.data.children_pos[0]=t_pos;
                        l.flush(f);
                        c.flush(f);
                        x.flush(f);
                        cout<<"3a"<<endl;
                        removefnc(c, key);
                        return;
                    }
                    binary<Node> r=f[x.data.children_pos[i+2]];
                    if (r.data.cnt>=border && flagr!=-1){
                        T t_key=x.data.keys[i+1];
                        int t_pos=r.data.children_pos[0];

                        x.data.keys[i+1]=r.data.keys[0];
                        for(int j=0; j<r.data.cnt-1; j++)
                            r.data.keys[j]=r.data.keys[j+1];
                        for(int j=0; j<r.data.cnt; j++)
                            r.data.children_pos[j]=r.data.children_pos[j+1];
                        r.data.cnt--;

                        c.data.keys[c.data.cnt]=t_key;
                        c.data.children_pos[c.data.cnt+1]=t_pos;
                        c.data.cnt++;
                        c.flush(f);
                        x.flush(f);
                        r.flush(f);
                        cout<<"3b"<<endl;
                        removefnc(c, key);
                        return;
                    }
                    if (flagl!=-1){
                        l.data.keys[l.data.cnt]=x.data.keys[i];
                        l.data.cnt+=border;
                        for (int j=0; j<border-1; j++)
                            l.data.keys[border+j]=c.data.keys[j];
                        for (int j=0; j<border; j++)
                            l.data.children_pos[border+j]=c.data.children_pos[j];
                        c.data.deleted=1;
                        for(int j=i+1; j<x.data.cnt; j++)
                            x.data.children_pos[j]=x.data.children_pos[j+1];
                        for(int j=i; j<x.data.cnt-1; j++)
                            x.data.keys[j]=x.data.keys[j+1];
                        x.data.cnt--;
                        if (x.data.cnt==0){
                            root_pos=l.pos;
                            x.data.deleted=1;
                        }
                        c.flush(f);
                        l.flush(f);
                        x.flush(f);
                        removefnc(l, key);
                    }
                    else if(flagr!=-1){
                        c.data.keys[c.data.cnt]=x.data.keys[i+1];
                        c.data.cnt+=border;
                        for (int j=0; j<border-1; j++)
                            c.data.keys[border+j]=r.data.keys[j];
                        for (int j=0; j<border; j++)
                            c.data.children_pos[border+j]=r.data.children_pos[j];
                        r.data.deleted=1;
                        for(int j=i+2; j<x.data.cnt; j++)
                            x.data.children_pos[j]=x.data.children_pos[j+1];
                        for(int j=i+1; j<x.data.cnt-1; j++)
                            x.data.keys[j]=x.data.keys[j+1];
                        x.data.cnt--;
                        if (x.data.cnt==0){
                            root_pos=c.pos;
                            x.data.deleted=1;
                        }
                        r.flush(f);
                        c.flush(f);
                        x.flush(f);
                        removefnc(c, key);
                    }else{
                        return;
                    }
                    cout<<"3c"<<endl;
                    return;
                }

            }
        }
    }

template <class T, int border>
    void BTree<T,border>::remove(T key){
        binary<Node> t=f[root_pos];
        removefnc(t, key);
    }

int main () {
    BTree<int, 10> bt;
    for (size_t i=0; i<11; i++){
        if(!bt.f[i].data.deleted)
        for(size_t j=0; j<bt.f[i].data.cnt; j++){
            cout<<bt.f[i].data.keys[j]<<" ";
        }
        cout<<endl;
    }


}

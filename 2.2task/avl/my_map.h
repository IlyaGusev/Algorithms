#ifndef MY_MAP_H_INCLUDED
#define MY_MAP_H_INCLUDED

#include <iostream>
#include <utility>
#include <iterator>
using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::pair;
using std::less;
using std::endl;

template <class Key, class T, class Compare = less<Key> >
class AVL{
    struct node;
public:
    struct inorder_iterator;

    AVL() : root(nullptr), end_node(node()), _begin(inorder_iterator(&end_node, this)), _end(inorder_iterator(&end_node, this))  {}
    ~AVL();

    pair<inorder_iterator, bool> insert(pair<Key, T>);
    void remove (inorder_iterator);
    void remove (const Key&);

    int size() const;

    void show(node*) const;
    node* root;

    inorder_iterator find (const Key&);
    inorder_iterator begin() const;
    inorder_iterator end() const;
private:
    struct node{
        const Key first;
        T second;
        unsigned char _height;
        node* parent;
        node* left;
        node* right;
        node() : first(Key()), second(T()), _height(0), parent(nullptr), left(nullptr), right(nullptr) {}
        node(Key k, T v) : first(k), second(v), _height(1), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    node end_node;
    inorder_iterator _begin;
    inorder_iterator _end;

    unsigned char height(node* p) const{ return (p!=nullptr)?p->_height:0; }
    int bfactor(node* p) const{ return height(p->right)-height(p->left); }
    void fixheight(node*) const;
    node* right_rotate(node*);
    node* left_rotate(node*);
    node* balance(node*);
};

template <class Key, class T, class Compare>
struct AVL<Key, T, Compare>::inorder_iterator : std::iterator<std::ptrdiff_t, node, node*, node&, std::bidirectional_iterator_tag>{
    node* ptr;
    AVL* tree_ptr;
    inorder_iterator() : ptr(nullptr), tree_ptr(nullptr){}
    inorder_iterator(const inorder_iterator& rhs) : ptr(rhs.ptr), tree_ptr(rhs.tree_ptr){}
    inorder_iterator(node* x, AVL* t) : ptr(x), tree_ptr(t){}

    node* operator->() const { return ptr; }
    node& operator*() const { return *ptr; }
    inorder_iterator& operator++(){
        if (ptr->right!=nullptr){
            ptr=ptr->right;
            while(ptr->left!=nullptr)
                ptr=ptr->left;
        }
        else
            if (ptr->parent!=nullptr){
                if (ptr==ptr->parent->left){
                    ptr=ptr->parent;
                }
                else{
                    while(ptr==ptr->parent->right){
                        ptr=ptr->parent;
                        if (ptr->parent==nullptr)
                            break;
                    }
                    if (ptr->parent!=nullptr)
                        ptr=ptr->parent;
                    else
                        ptr=&tree_ptr->end_node;
                }
            }
            else
               ptr=&tree_ptr->end_node;
        return (*this);
    }
    inorder_iterator operator++(int){
        inorder_iterator temp((*this));
        ++(*this);
        return temp;
    }
    inorder_iterator& operator--(){
        if ((*this)==tree_ptr->_end){
            node* x=tree_ptr->root;

            if (x==nullptr)
                return (*this);
            while(x->right!=nullptr)
                x=x->right;

            (*this)=inorder_iterator(x, tree_ptr);
            return (*this);
        }
        if (ptr->left!=nullptr){
            ptr=ptr->left;
            while(ptr->right!=nullptr)
                ptr=ptr->right;
        }
        else
            if (ptr->parent!=nullptr){
                if (ptr==ptr->parent->right){
                    ptr=ptr->parent;
                }
                else{
                    while(ptr==ptr->parent->left){
                        ptr=ptr->parent;
                        if (ptr->parent==nullptr)
                            break;
                    }
                    if (ptr->parent!=nullptr)
                        ptr=ptr->parent;
                    else
                        (*this)=tree_ptr->_begin;
                }
            }
            else
               (*this)=tree_ptr->_begin;
        return (*this);
    }
    inorder_iterator operator--(int){
        inorder_iterator temp((*this));
        --(*this);
        return temp;
    }
    bool operator==(const inorder_iterator& rhs) const{return (rhs.ptr==ptr && rhs.tree_ptr==tree_ptr);}
    bool operator!=(const inorder_iterator& rhs) const{return !(rhs.ptr==ptr && rhs.tree_ptr==tree_ptr);}
    bool operator<(const inorder_iterator& rhs) const{
        if ((*this)==tree_ptr->_end && rhs!=tree_ptr->_end) return false;
        if (rhs==tree_ptr->_end && (*this)!=tree_ptr->_end) return true;
        return (Compare()((*this)->first, rhs->first));
    }
    bool operator>(const inorder_iterator& rhs) const{
        if ((*this)==tree_ptr->_end && rhs!=tree_ptr->_end) return true;
        if (rhs==tree_ptr->_end && (*this)!=tree_ptr->_end) return false;
        return (Compare()(rhs->first, (*this)->first));
    }
    bool operator<=(const inorder_iterator& rhs) const{return ((*this)<rhs || (*this)==rhs);}
    bool operator>=(const inorder_iterator& rhs) const{return ((*this)>rhs || (*this)==rhs);}
};

template <class Key, class T, class Compare>
    typename AVL<Key,T,Compare>::inorder_iterator AVL<Key,T,Compare>::begin() const{
        return _begin;
    }

template <class Key, class T, class Compare>
    typename AVL<Key,T,Compare>::inorder_iterator AVL<Key,T,Compare>::end() const{
        return _end;
    }

namespace my{
template <class Key, class T, class Compare = less<Key> >
class map{
public:
    typedef AVL<Key, T ,Compare> tree_type;
    typedef pair<const Key, T> value_type;
    typedef typename AVL<Key, T ,Compare>::inorder_iterator iterator;

    map() : data(tree_type()) {}

    iterator begin() const{return data.begin();}
    iterator end() const{return data.end();}
    iterator find (const Key& k) {return data.find(k);}

    bool empty() const{return (begin()==end());}
    int size() const{return data.size();}

    pair<iterator,bool> insert (const value_type& val){return data.insert(val);}
    void erase (iterator position){return data.remove(position);}
    void erase (const Key& k){return data.remove(k);}
    void clear (){
        for(auto it=++begin(); it!=end(); ++it){
            auto temp=it;
            --temp;
            erase(temp);
        }
        if (begin()!=end())
            erase(--data.end());
    }

private:
    tree_type data;
};
}

template <class Key, class T, class Compare>
    AVL<Key,T,Compare>::~AVL(){
        for(auto it=++begin(); it!=end(); ++it){
            auto temp=it;
            --temp;
            remove(temp);
        }
        if (begin()!=end())
            remove(--end());
    }

template <class Key, class T, class Compare>
    void AVL<Key,T,Compare>::fixheight(node* p) const{
        unsigned char hl=height(p->left);
        unsigned char hr=height(p->right);
        p->_height = (hl>hr?hl:hr)+1;
    }

template <class Key, class T, class Compare>
    typename AVL<Key, T, Compare>::node* AVL<Key, T, Compare>::right_rotate(node* p){
        node* q = p->left;

        p->left = q->right;
        if (q->right!=nullptr)
            q->right->parent=p;

        q->parent=p->parent;
        if (p->parent==nullptr) root=q;
        else
            if (p==p->parent->left) q->parent->left=q;
            else q->parent->right=q;

        q->right = p;
        p->parent = q;
        fixheight(p);
        fixheight(q);
        return q;
    }

template <class Key, class T, class Compare>
    typename AVL<Key, T, Compare>::node* AVL<Key, T, Compare>::left_rotate(node* p){
        node* q = p->right;

        p->right = q->left;
        if (q->left!=nullptr)
            q->left->parent=p;

        q->parent=p->parent;
        if (p->parent==nullptr) root=q;
        else
            if (p==p->parent->left) q->parent->left=q;
            else q->parent->right=q;

        q->left = p;
        p->parent = q;
        fixheight(p);
        fixheight(q);
        return q;
    }

template <class Key, class T, class Compare>
    typename AVL<Key, T, Compare>::node* AVL<Key, T, Compare>::balance(node* p){
        fixheight(p);
        if(bfactor(p)==2){
            if(bfactor(p->right) < 0)
                right_rotate(p->right);
            return left_rotate(p);
        }
        if(bfactor(p)==-2){
            if(bfactor(p->left) > 0)
                left_rotate(p->left);
            return right_rotate(p);
        }
        return p;
    }

template <class Key, class T, class Compare>
    pair<typename AVL<Key, T, Compare>::inorder_iterator, bool> AVL<Key, T, Compare>::insert(pair<Key, T> p){
        node* z=new node(p.first, p.second);
        node* y=nullptr;
        node* x=root;
        while (x!=nullptr){
            y=x;
            if (!Compare()(z->first,x->first) && !Compare()(x->first,z->first)){
                delete z;
                return pair<inorder_iterator, bool> (inorder_iterator(x, this), false);
            }
            else
                if (Compare()(z->first,x->first))
                    x=x->left;
                else
                    x=x->right;
        }

        z->parent=y;
        if (y==nullptr){
            root=z;
            _begin=inorder_iterator(z, this);
        }
        else
            if (Compare()(z->first, y->first))
                y->left=z;
            else
                y->right=z;
        if (Compare()(z->first, _begin->first))
            _begin=inorder_iterator(z, this);


        while(y!=nullptr){
            y=balance(y);
            y=y->parent;
        }
        return pair<inorder_iterator, bool> (inorder_iterator(z, this), true);
    }

template <class Key, class T, class Compare>
    void AVL<Key, T, Compare>::show(node * x) const{
        if (x!=nullptr){
            cout<<x->first<<" "<<endl;
            cout<<x->first<<" L: "<<endl;
            show(x->left);
            cout<<x->first<<" R: "<<endl;
            show(x->right);
        }
    }

template <class Key, class T, class Compare>
    void AVL<Key, T, Compare>::remove (inorder_iterator p){
        if (p==end())
            return;
        node* q = p->left;
        node* r = p->right;
        node* s = p->parent;
        bool l=false;
        if (s!=nullptr)
            if (&(*p)==s->left) l=true;
        if (p==_begin) ++_begin;
        delete &(*p);
        if(r!=nullptr){
            node* m=r;
            while(m->left!=nullptr)
                m=m->left;
            node* t=m->parent;

            if (m!=r){
                t->left=m->right;
                if (m->right!=nullptr) m->right->parent=t;

                while(t!=r && r!=m){
                    t=balance(t);
                    t=t->parent;
                }
                r=balance(r);

                m->right=r;
                r->parent=m;
            }
            r=balance(r);
            m->left=q;
            if (q!=nullptr)
                q->parent=m;

            m=balance(m);
            q=m;
        }
        if (s!=nullptr){
            if (q!=nullptr) q->parent=s;
            if (l) s->left=q;
              else s->right=q;
        }
        else root=q;

        while(s!=nullptr){
            s=balance(s);
            s=s->parent;
        }
    }

template <class Key, class T, class Compare>
    void AVL<Key, T, Compare>::remove (const Key& k){
        node* x=root;
        while (x!=nullptr){
            if (!Compare()(k,x->first) && !Compare()(x->first,k)){
                remove(inorder_iterator(x, this));
                return;
            }
            else
                if (Compare()(k,x->first)) x=x->left;
                else x=x->right;
        }
        return;
    }

template <class Key, class T, class Compare>
    typename AVL<Key, T, Compare>::inorder_iterator AVL<Key, T, Compare>::find (const Key& k){
        node* x=root;
        while (x!=nullptr){
            if (!Compare()(k,x->first) && !Compare()(x->first,k)){
                return inorder_iterator(x, this);
            }
            else
                if (Compare()(k,x->first)) x=x->left;
                else x=x->right;
        }
        return end();
    }

template <class Key, class T, class Compare>
    int AVL<Key, T, Compare>::size() const{
        int i=0;
        for (AVL<int, int>::inorder_iterator it=_begin; it!=_end; ++it)
            i++;
        return i;
    }

#endif // MY_MAP_H_INCLUDED

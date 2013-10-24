#include <iostream>
#include <list>
using namespace std;

template <class Key, class Data, Key max>
class BinHeap{
    struct Node{
        Node(Key _key, Data _data) :
            key(_key), data(_data),
            parent(nullptr), sibling(nullptr),
            child(nullptr), degree(0){}
        Node() :
            key(), data(),
            parent(nullptr), sibling(nullptr),
            child(nullptr), degree(0){}
        Key key;
        Data data;
        Node* parent;
        Node* sibling;
        Node* child;
        int degree;
    };
    public:
        BinHeap() : root(nullptr) {}
        void insert(Key, Data);
        void print(Node* a){
            Node* current;
            if(a==nullptr)
                current = root;
            else
                current = a;
            while(current!=nullptr){
                cout<<current->key<<" ";
                current=current->sibling;
            }
            cout<<endl;
        }
        Node* minimum();
        Node* extract_minimum();
    private:
        Node* root;
        Node* merge(Node*, Node*);
        Node* merge_roots(Node*, Node*);
        void link(Node*, Node*);
        void insert(Node*);

        //decrease_key(Node*, T);
        //erase(Node*);

};

template <class Key, class Data, Key max>
    typename BinHeap<Key, Data, max>::Node* BinHeap<Key, Data, max>::merge (Node* first, Node* second){
        Node* x = merge_roots(first, second);
        Node* root = x;
        if (x==nullptr) return root;
        Node* prev_x = nullptr;
        Node* next_x = x->sibling;
        while(next_x != nullptr){
            if (next_x->sibling!=nullptr){
                if (x->degree == next_x->sibling->degree || (x->degree!=next_x->degree)){
                    prev_x = x;
                    x = next_x;
                }
                else{
                    if (x->key<=next_x->key){
                        x->sibling = next_x->sibling;
                        link(next_x, x);
                    }
                    else{
                        if (prev_x==nullptr)
                            root = next_x;
                        else
                            prev_x->sibling = next_x;
                        link(x, next_x);
                        x=next_x;
                    }
                }
            }
            else{
                if (x->degree!=next_x->degree){
                    prev_x = x;
                    x = next_x;
                }
                else{
                    if (x->key<=next_x->key){
                        x->sibling = next_x->sibling;
                        link(next_x, x);
                    }
                    else{
                        if (prev_x==nullptr)
                            root = next_x;
                        else
                            prev_x->sibling = next_x;
                        link(x, next_x);
                        x=next_x;
                    }
                }
            }

            next_x = x->sibling;
        }
        return root;
    }

template <class Key, class Data, Key max>
    void BinHeap<Key, Data, max>::link (Node* first, Node* second){
        first->parent = second;
        first->sibling = second->child;
        second->child = first;
        second->degree++;
    }

template <class Key, class Data, Key max>
    typename BinHeap<Key, Data, max>::Node* BinHeap<Key, Data, max>::merge_roots (Node* first, Node* second){
        Node* x;
        Node* current;
        if (first==nullptr){
            current = second;
            if (second!=nullptr)
                second = second->sibling;
        }
        else
        if (second==nullptr){
            current = first;
            if (first!=nullptr)
                first = first->sibling;
        }
        else
            if (first->degree<second->degree){
                current = first;
                first = first->sibling;

            }else{
                current = second;
                second = second->sibling;
            }
        x = current;


        while(first!=nullptr || second!=nullptr){
            if (first==nullptr){
                current->sibling=second;
                current = second;
                second = second->sibling;
            }
            else
            if (second==nullptr){
                current->sibling=first;
                current = first;
                first = first->sibling;
            }
            else
                if (first->degree<second->degree){
                    current->sibling=first;
                    current = first;
                    first = first->sibling;
                }else{
                    current->sibling=second;
                    current = second;
                    second = second->sibling;
                }
        }
        return x;
    }

template <class Key, class Data, Key max>
    void BinHeap<Key, Data, max>::insert (Node* node){
        root = merge(root, node);
    }

template <class Key, class Data, Key max>
    void BinHeap<Key, Data, max>::insert (Key key, Data data){
        Node* node = new Node(key, data);
        insert(node);
    }

template <class Key, class Data, Key max>
    typename BinHeap<Key, Data, max>::Node* BinHeap<Key, Data, max>::minimum(){
        Node* answer = nullptr;
        Node* current = root;
        Key min = max;
        while(current!=nullptr){
            if (current->key<min){
                min = current->key;
                answer = current;
            }
            current = current->sibling;
        }
        return answer;
    }

template <class Key, class Data, Key max>
    typename BinHeap<Key, Data, max>::Node* BinHeap<Key, Data, max>::extract_minimum(){
        Node* x = minimum();

        Node* temp = root;
        if (root!=x){
            while(temp->sibling!=x){
                temp=temp->sibling;
            }
            temp->sibling = x->sibling;
        }
        else{
            root = root->sibling;
        }

        x->sibling=nullptr;
    //    cout<<"roots: ";print(root);
        Node* p1 = x->child;
    //    cout<<"p1: ";print(p1);
        Node* p2 = nullptr;
        Node* p3 = nullptr;
        while (p1!=nullptr){
            p3=p2;
            p2=p1->sibling;
            p1->sibling=nullptr;
            p1->parent = nullptr;
            p1->sibling=p3;
            if (p2!=nullptr){
                p2->parent = nullptr;
                Node* temp = p1;
                p1 = p2->sibling;
                p2->sibling = temp;
            }
            else{
                break;
            }
        }
        Node* r;
        if (p1==nullptr)
            r=p2;
        else
            r=p1;
    //        cout<<"extr: ";
    //       print(r);
        root = merge(root,r);
        return x;
    }

int main(){
    BinHeap<int, int, 999> heap;
    heap.insert(2, 2);
    heap.insert(1, 2);
    heap.insert(8, 2);
    heap.insert(5, 2);
    heap.insert(4, 2);
    heap.insert(6, 2);
    heap.insert(3, 2);
    heap.insert(10, 2);
    heap.insert(20, 2);
    heap.insert(30, 2);
    heap.insert(25, 2);
    heap.insert(35, 2);
    heap.insert(40, 2);
    heap.insert(9, 2);
    heap.insert(11, 2);
    heap.insert(12, 2);


    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
}

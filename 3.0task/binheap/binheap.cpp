#include <iostream>
#include <list>
using namespace std;
const int MAX_INT = 40000000;
template <class Key, class Data>
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
        void insert(Node*);
        void erase(Node*);
        Node* minimum();
        Node* extract_minimum();
        void decrease_key(Node*, Key);
        void print(Node*);
    private:
        Node* root;
        Node* merge(Node*, Node*);
        Node* merge_roots(Node*, Node*);
        void link(Node*, Node*);

};

template <class Key, class Data>
    typename BinHeap<Key, Data>::Node* BinHeap<Key, Data>::merge (Node* first, Node* second){
        Node* x = merge_roots(first, second);
        Node* root = x;
        if (x==nullptr) return root;
        Node* prev_x = nullptr;
        Node* next_x = x->sibling;
        while(next_x != nullptr){
            int next_x_sibling_degree = -1;
            if (next_x->sibling!=nullptr)
                next_x_sibling_degree = next_x->sibling->degree;

            if (x->degree == next_x_sibling_degree || (x->degree!=next_x->degree)){
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

            next_x = x->sibling;
        }
        return root;
    }

template <class Key, class Data>
    void BinHeap<Key, Data>::link (Node* first, Node* second){
        first->parent = second;
        first->sibling = second->child;
        second->child = first;
        second->degree = second->degree+1;
    }

template <class Key, class Data>
    typename BinHeap<Key, Data>::Node* BinHeap<Key, Data>::merge_roots (Node* first, Node* second){
        Node* x = nullptr;
        Node* current = nullptr;
        int first_degree = MAX_INT;
        int second_degree = MAX_INT;
        if (first == nullptr && second ==nullptr)
            return nullptr;

        while(first!=nullptr || second!=nullptr){
            first_degree = MAX_INT;
            second_degree = MAX_INT;
            if (first!=nullptr)
                first_degree = first->degree;
            if (second!=nullptr)
                second_degree = second->degree;

            if (first_degree<second_degree){
                if (current!=nullptr) current->sibling=first; else x=first;
                current = first;
                first = first->sibling;
            }else{
                if (current!=nullptr) current->sibling=second; else x=second;
                current = second;
                second = second->sibling;
            }
        }
        return x;
    }

template <class Key, class Data>
    void BinHeap<Key, Data>::insert (Node* node){
        root = merge(root, node);
    }

template <class Key, class Data>
    void BinHeap<Key, Data>::insert (Key key, Data data){
        Node* node = new Node(key, data);
        insert(node);
    }

template <class Key, class Data>
    typename BinHeap<Key, Data>::Node* BinHeap<Key, Data>::minimum(){
        Node* answer = nullptr;
        Node* current = root;
        if (current == nullptr)
            return answer;
        Key minimal = current->key;
        answer = current;
        current = current->sibling;
        while(current!=nullptr){
            if (current->key<minimal){
                minimal = current->key;
                answer = current;
            }
            current = current->sibling;
        }
        return answer;
    }

template <class Key, class Data>
    typename BinHeap<Key, Data>::Node* BinHeap<Key, Data>::extract_minimum(){

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

        ///Разворот списка детей x
        Node* p1 = x->child;
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
            else break;
        }
        Node* reversed;
        if (p1==nullptr) reversed=p2; else reversed=p1;
        ///reversed - корень развёрнутого списка детей

        root = merge(root, reversed);
        return x;
    }

template <class Key, class Data>
    void BinHeap<Key, Data>::decrease_key(Node* node, Key new_key){
        if (new_key>=node->key)
            return;
        node->key = new_key;
        Node* current = node;
        Node* current_parent = node->parent;
        while(current_parent!=nullptr){
            if (current->key>current_parent->key)
                break;
            Key temp_key = current->key;
            Data temp_data = current->data;
            current->key=current_parent->key;
            current->data=current_parent->data;
            current_parent->key = temp_key;
            current_parent->data = temp_data;

            current = current_parent;
            current_parent = current->parent;
        }
    }

template <class Key, class Data>
    void BinHeap<Key, Data>::erase(Node* node){
        decrease_key(node, minimum()->key);
        extract_minimum();
    }
template <class Key, class Data>
    void BinHeap<Key, Data>::print(Node* a){
        Node* current;
        if(a==nullptr)
            current = root;
        else
            current = a;
        if (current == nullptr)
            cout<<"Empty";
        while(current!=nullptr){
            cout<<current->key<<" ";
            current=current->sibling;
        }
        cout<<endl;
    }
int main(){
    BinHeap<int, int> heap;
    heap.insert(3, 2);
    heap.insert(1, 2);
    heap.insert(8, 2);
    heap.insert(5, 2);
    heap.insert(4, 2);
    heap.insert(6, 2);
    heap.insert(33, 2);
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
    heap.erase(heap.minimum());
    heap.print(nullptr);
}

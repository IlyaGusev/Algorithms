#include <iostream>
using namespace std;
template <class Key, class Data>
class FibHeap{
    struct Node{
        Node(Key _key, Data _data) :
            key(_key), data(_data), parent(nullptr),
            left(this), right(this), child(nullptr),
            mark(false), degree(0){}
        Node() :
            key(), data(), parent(nullptr),
            left(this), right(this), child(nullptr),
            mark(false), degree(0){}
        Key key;
        Data data;
        Node* parent;
        Node* left;
        Node* right;
        Node* child;
        bool mark;
        int degree;
    };
    public:
        FibHeap() : root(nullptr), number_of_nodes(0) {}
        void insert(Key, Data);
        void insert(Node*);
        void merge(FibHeap*);
        void erase(Node*);
        Node* extract_minimum();
        Node* minimum() {return root;}
        void decrease_key(Node*, Key);
        void print(Node*);
    private:
        Node* root;
        int number_of_nodes;

        void insert_to_root_list(Node*, Node*);
        void erase_from_root_list(Node*);
        void consolidate();
        void cut(Node*, Node*);
        void cascading_cut(Node*);
};

template <class Key, class Data>
    void FibHeap<Key, Data>::insert (Key key, Data data){
        Node* node = new Node(key, data);
        insert(node);
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::insert (Node* node){
        node->degree = 0;
        node->parent = nullptr;
        node->child = nullptr;
        node->left = node;
        node->right = node;
        node->mark = false;

        if (root==nullptr){
            root=node;
        }
        else{
            insert_to_root_list(root, node);
            if (node->key < root->key)
                root = node;
        }
        number_of_nodes++;
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::insert_to_root_list (Node* r, Node* node){
        Node* temp = r->left;
        temp->right = node;
        node->right = r;
        node->left = temp;
        r->left = node;
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::erase_from_root_list (Node* node){
        node->left->right = node->right;
        node->right->left = node->left;
        if (node->parent!=nullptr)
            if (node->parent->child == node){
                if (node != node->right)
                    node->parent->child = node->right;
                else
                    node->parent->child = nullptr;
            }
        node->parent = nullptr;
        node->right = nullptr;
        node->left = nullptr;
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::merge (FibHeap* other){
        if (other == nullptr)
            return;

        Node* temp1 = root->right;
        Node* temp2 = other->root->left;
        root->right = other->root;
        other->root->left = root;
        temp1->left=temp2;
        temp2->right=temp1;
        if (other->root->key<root->key)
            root=other->root;
        number_of_nodes+=other->number_of_nodes;
        (*other) = FibHeap();
    }

template <class Key, class Data>
    typename FibHeap<Key, Data>::Node* FibHeap<Key, Data>::extract_minimum(){
        Node* answer = root;
        if (root!=nullptr){
            Node* current_child = root->child;
            for (int i=1; i<=root->degree; i++){
                current_child->parent = nullptr;
                Node* temp = current_child;
                current_child = current_child->right;
                insert_to_root_list(root, temp);
            }
            if (root == root->right){
                root = nullptr;
                number_of_nodes = 0;
            }else{
                root = root->right;
                erase_from_root_list(answer);
                answer->child = nullptr;
                consolidate();
                number_of_nodes--;
            }
        }
        return answer;
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::consolidate(){
        Node* node_with_degree_i[127];
        for (int i=0; i<128; i++)
            node_with_degree_i[i] = nullptr;

        int number_of_roots = 1;
        Node* temp = root->right;
        while (temp!=root){
            number_of_roots++;
            temp=temp->right;
        }

        Node* current = root;
        for(int i=1; i<=number_of_roots; i++){
            Node* x = current;
            current = current->right;
            int d = x->degree;
            while(node_with_degree_i[d]!=nullptr){

                Node* y = node_with_degree_i[d];
                if (y->key < x->key){
                    Node* temp = x;
                    x = y;
                    y = temp;
                }

                ///Link - begin
                erase_from_root_list(y);
                y->parent = x;
                if(x->child!=nullptr){
                    insert_to_root_list(x->child, y);
                }
                else{
                    x->child = y;
                    y->left = y;
                    y->right = y;
                }
                x->degree++;
                y->mark = false;
                ///Link - end

                node_with_degree_i[d] = nullptr;
                d++;

            }
            node_with_degree_i[d] = x;
        }

        root = nullptr;
        for (int i=0; i<128; i++){
            if(node_with_degree_i[i]!=nullptr){
                if(root==nullptr){
                    root = node_with_degree_i[i];
                    root->left = root;
                    root->right = root;
                }
                else{
                    insert_to_root_list(root, node_with_degree_i[i]);
                    if (root->key > node_with_degree_i[i]->key)
                        root = node_with_degree_i[i];
                }
            }
        }
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::decrease_key(Node* node, Key new_key){
        if (new_key>=node->key)
            return;
        node->key = new_key;
        Node* parent = node->parent;
        if (parent==nullptr){
            if (node->key < root->key)
                root = node;
        }else{
            if (node->key < parent->key){
                cut(node, parent);
                cascading_cut(parent);
            }
        }
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::cut(Node* child, Node* parent){
        erase_from_root_list(child);
        parent->degree--;
        insert_to_root_list(root, child);
        if (child->key < root->key)
            root = child;
        child->parent = nullptr;
        child->mark = false;
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::cascading_cut(Node* child){
        Node* parent = child->parent;
        if (parent!=nullptr){
            if (child->mark==false)
                child->mark = true;
            else{
                cut(child, parent);
                cascading_cut(parent);
            }
        }
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::erase (Node* node){
        decrease_key(node, root->key);
        root = node;
        extract_minimum();
    }

template <class Key, class Data>
    void FibHeap<Key, Data>::print(Node* a){
        Node* current;
        if(a==nullptr)
            current = root;
        else
            current = a;
        if (current == nullptr){
            cout<<"Empty"<<endl;
            return;
        }
        Node* temp =current;
        cout<<current->key<<" ";
        current = current->right;
        while(current!=temp){
            cout<<current->key<<" ";
            current = current->right;
        }
        cout<<endl;
    }

int main(){
    FibHeap<int, int> heap;
    FibHeap<int, int> heap2;
    heap.insert(4,5);
    heap.insert(5,5);
    heap.insert(3,5);
    heap.insert(7,5);
    heap2.insert(1,5);
    heap2.insert(2,5);
    heap2.insert(9,5);
    heap.print(nullptr);
    heap2.print(nullptr);
    heap.merge(&heap2);
    heap.print(nullptr);
    cout<<" "<<heap.extract_minimum()->key<<endl;
    heap.print(nullptr);
    heap.decrease_key(heap.minimum()->child->right, 1);
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

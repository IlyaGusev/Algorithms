#ifndef FIBHEAP_HPP_INCLUDED
#define FIBHEAP_HPP_INCLUDED

#include "fibheap.h"

template <class Key, class Data, class Compare>
    FibHeap<Key, Data, Compare>::~FibHeap(){
        if (root != nullptr)
            destroy(root, root);
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::destroy (Node* current, Node* base) noexcept{
        if (current->child!=nullptr)
            destroy(current->child, current->child);
        if (current->right!=base)
            destroy(current->right, base);
        delete current;
    }

template <class Key, class Data, class Compare>
    typename FibHeap<Key, Data, Compare>::Node* FibHeap<Key, Data, Compare>::insert (Key key, Data data = Data()) noexcept{
        Node* node = new Node(key, data);
        insert(*node);
        return node;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::insert (Node& node) noexcept{
        node.degree = 0;
        node.parent = nullptr;
        node.child = nullptr;
        node.left = &node;
        node.right = &node;
        node.mark = false;

        if (root==nullptr){
            root=&node;
        }
        else{
            insert_to_root_list(root, &node);
            if (Compare()(node.key, root->key)){
                root = &node;
            }
        }
        number_of_nodes++;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::insert_to_root_list (Node* r, Node* node) noexcept{
        Node* temp = r->left;
        temp->right = node;
        node->right = r;
        node->left = temp;
        r->left = node;
        node->parent = r->parent;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::erase_from_root_list (Node* node) noexcept{
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

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::merge (FibHeap* other) noexcept{
        if (other == nullptr)
            return;
        if (root == nullptr){
            this->root = other->root;
            return;
        }

        Node* temp1 = root->right;
        Node* temp2 = other->root->left;
        root->right = other->root;
        other->root->left = root;
        temp1->left=temp2;
        temp2->right=temp1;
        if (Compare()(other->root->key, root->key))
            root=other->root;
        number_of_nodes+=other->number_of_nodes;
        (*other) = FibHeap();
    }

template <class Key, class Data, class Compare>
    typename FibHeap<Key, Data, Compare>::Node* FibHeap<Key, Data, Compare>::extract_minimum(){
        if (root==nullptr)
            throw logic_error("Heap is empty. Don't try to extract minimum.");
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

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::consolidate() noexcept{
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
                if (Compare()(y->key, x->key)){
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
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
                    if (Compare()(node_with_degree_i[i]->key, root->key))
                        root = node_with_degree_i[i];
                }
            }
        }
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::link(Node* child, Node* parent) noexcept{
        erase_from_root_list(child);
        child->parent = parent;
        if(parent->child!=nullptr){
            insert_to_root_list(parent->child, child);
        }
        else{
            parent->child = child;
            child->left = child;
            child->right = child;
            child->parent = parent;
        }
        parent->degree++;
        child->mark = false;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::decrease_key(Node* node, Key new_key) {
        if (node == nullptr)
            throw logic_error("There is no node to decrease key.");
        if (Compare()(node->key, new_key))
            return;
        node->key = new_key;
        Node* parent = node->parent;
        if (parent==nullptr){
            if (Compare()(node->key, root->key))
                root = node;
        }else{
            if (Compare()(node->key, parent->key)){
                cut(node, parent);
                cascading_cut(parent);
            }
        }
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::cut(Node* child, Node* parent) noexcept{
        erase_from_root_list(child);
        parent->degree--;
        insert_to_root_list(root, child);
        if (Compare()(child->key, root->key))
            root = child;
        child->parent = nullptr;
        child->mark = false;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::cascading_cut(Node* child) noexcept{
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

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::erase (Node* node){
        if (node==nullptr)
            throw logic_error("There is no node to erase.");
        decrease_key(node, root->key);
        root = node;
        Node* temp = extract_minimum();
        delete temp;
    }

template <class Key, class Data, class Compare>
    void FibHeap<Key, Data, Compare>::print(Node* current = nullptr, Node* base = nullptr, int level = 0) const noexcept{
        if (root == nullptr){
            cout<<"Empty"<<endl;
            return;
        }
        if (current == nullptr){
            current = root;
            base = root;
        }
        for (int i=0; i<level; i++)
            cout<<"  ";
        cout<<current->key<<endl;
        if (current->child!=nullptr)
            print(current->child, current->child, level+1);
        if (current->right!=base)
            print(current->right, base, level);
    }

#endif // FIBHEAP_HPP_INCLUDED

#ifndef BINHEAP_HPP_INCLUDED
#define BINHEAP_HPP_INCLUDED

#include "binheap.h"

template <class Key, class Data, class Compare>
    BinHeap<Key, Data, Compare>::~BinHeap(){
        if (root != nullptr)
            destroy(root);
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::destroy (Node* current) noexcept{
        if (current->child!=nullptr)
            destroy(current->child);
        if (current->sibling!=nullptr)
            destroy(current->sibling);
        delete current;
    }

template <class Key, class Data, class Compare>
    typename BinHeap<Key, Data, Compare>::Node* BinHeap<Key, Data, Compare>::merge (Node* key, Node* data) noexcept{
        Node* x = merge_roots(key, data);
        Node* answer = x;
        if (x==nullptr) return answer;
        Node* prev_x = nullptr;
        Node* next_x = x->sibling;
        while(next_x != nullptr){
            int next_x_sibling_degree = -1;
            if (next_x->sibling!=nullptr)
                next_x_sibling_degree = next_x->sibling->degree;

            if (x->degree == next_x_sibling_degree || (x->degree!=next_x->degree)){
                prev_x=x;
                x=next_x;
            }
            else{
                if (Compare()(x->key, next_x->key)){
                    x->sibling=next_x->sibling;
                    link(next_x, x);
                }
                else{
                    if (prev_x==nullptr)
                        answer=next_x;
                    else
                        prev_x->sibling=next_x;
                    link(x, next_x);
                    x=next_x;
                }
            }

            next_x=x->sibling;
        }
        return answer;
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::link (Node* child, Node* parent) noexcept{
        child->parent = parent;
        child->sibling = parent->child;
        parent->child = child;
        parent->degree++;
    }

template <class Key, class Data, class Compare>
    typename BinHeap<Key, Data, Compare>::Node* BinHeap<Key, Data, Compare>::merge_roots (Node* key, Node* data) noexcept{
        Node* x = nullptr;
        Node* current = nullptr;
        int key_degree = INT_MAX;
        int data_degree = INT_MAX;
        if (key == nullptr && data == nullptr)
            return nullptr;

        while(key!=nullptr || data!=nullptr){
            key_degree = INT_MAX;
            data_degree = INT_MAX;
            if (key!=nullptr)
                key_degree = key->degree;
            if (data!=nullptr)
                data_degree = data->degree;

            if (key_degree<data_degree){
                if (current!=nullptr) current->sibling=key; else x=key;
                current = key;
                key = key->sibling;
            }else{
                if (current!=nullptr) current->sibling=data; else x=data;
                current = data;
                data = data->sibling;
            }
        }
        return x;
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::insert (Node& node) noexcept{
        node.parent = nullptr;
        node.child = nullptr;
        node.sibling = nullptr;
        node.degree = 0;
        root = merge(root, &node);
    }

template <class Key, class Data, class Compare>
    typename BinHeap<Key, Data, Compare>::Node* BinHeap<Key, Data, Compare>::insert (Key key, Data data = Data()) noexcept{
        Node* node = new Node(key, data);
        insert(*node);
        return node;
    }

template <class Key, class Data, class Compare>
    typename BinHeap<Key, Data, Compare>::Node* BinHeap<Key, Data, Compare>::minimum() const noexcept{
        Node* answer = nullptr;
        Node* current = root;
        if (current == nullptr)
            return answer;
        Key minimal = current->key;
        answer = current;
        current = current->sibling;
        while(current!=nullptr){
            if (Compare()(current->key, minimal)){
                minimal = current->key;
                answer = current;
            }
            current = current->sibling;
        }
        return answer;
    }

template <class Key, class Data, class Compare>
    typename BinHeap<Key, Data, Compare>::Node* BinHeap<Key, Data, Compare>::extract_minimum(){

        Node* x = minimum();
        if (x==nullptr)
            throw logic_error("Heap is empty. Don't try to extract minimum.");

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
            p1->parent=nullptr;
            p1->sibling=p3;
            if (p2!=nullptr){
                p2->parent=nullptr;
                Node* temp=p1;
                p1=p2->sibling;
                p2->sibling=temp;
            }
            else break;
        }
        Node* reversed;
        if (p1==nullptr) reversed=p2; else reversed=p1;
        ///reversed - корень развёрнутого списка детей

        root = merge(root, reversed);
        return x;
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::decrease_key(Node* node, Key new_key){
        if (node == nullptr)
            throw logic_error("There is no node to decrease key.");
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
            current->key = current_parent->key;
            current->data = current_parent->data;
            current_parent->key = temp_key;
            current_parent->data = temp_data;

            current = current_parent;
            current_parent = current->parent;
        }
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::erase(Node* node){
        if (node == nullptr)
            throw logic_error("There is no node to erase.");
        decrease_key(node, minimum()->key);
        extract_minimum();
        delete node;
    }

template <class Key, class Data, class Compare>
    void BinHeap<Key, Data, Compare>::print(Node* a = nullptr, int level = 0) const noexcept{
        if (a==nullptr) a = root;
        if (root == nullptr){cout<<"Empty"<<endl; return;}
        for (int i=0; i<level; i++)
            cout<<"  ";
        cout<<a->key<<endl;
        if (a->child!=nullptr)
            print(a->child, level+1);
        if (a->sibling!=nullptr)
            print(a->sibling, level);
    }

#endif // BINHEAP_HPP_INCLUDED

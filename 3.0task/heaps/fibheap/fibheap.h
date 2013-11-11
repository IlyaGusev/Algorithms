#ifndef FIBHEAP_H_INCLUDED
#define FIBHEAP_H_INCLUDED

#include <iostream>
#include <climits>
#include <stdexcept>
#include <utility>

using std::cout;
using std::endl;
using std::logic_error;
using std::less;

template <class Key, class Data = int, class Compare = less<Key>>
class FibHeap{
    class Node{
        friend class FibHeap;
        public:
            Key first() const { return key; }
            Key second() const { return data; }
        private:
            Key key;
            Data data;
            Node(Key _key, Data _data) :
                key(_key), data(_data), parent(nullptr),
                left(this), right(this), child(nullptr),
                mark(false), degree(0){}
            Node() :
                key(), data(), parent(nullptr),
                left(this), right(this), child(nullptr),
                mark(false), degree(0){}
            Node* parent;
            Node* left;
            Node* right;
            Node* child;
            bool mark;
            int degree;
    };
    public:
        FibHeap() : root(nullptr), number_of_nodes(0) {}
        ~FibHeap();
        void insert(Key, Data)                  noexcept;
        void insert(Node&)                      noexcept;
        void merge(FibHeap*)                    noexcept;
        void erase(Node*);
        Node* extract_minimum();
        Node* minimum()                         const noexcept {return root;}
        void decrease_key(Node*, Key);
        void print(Node*, Node*, int)           const noexcept;
    private:
        void insert_to_root_list(Node*, Node*)  noexcept;
        void erase_from_root_list(Node*)        noexcept;
        void link(Node*, Node*)                 noexcept;
        void destroy(Node*, Node*)              noexcept;
        void consolidate()                      noexcept;
        void cut(Node*, Node*)                  noexcept;
        void cascading_cut(Node*)               noexcept;

        Node* root;
        int number_of_nodes;
};

#include "fibheap.hpp"

#endif // FIBHEAP_H_INCLUDED

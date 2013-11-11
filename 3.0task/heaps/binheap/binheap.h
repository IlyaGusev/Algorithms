#ifndef BINHEAP_H_INCLUDED
#define BINHEAP_H_INCLUDED

#include <iostream>
#include <climits>
#include <stdexcept>
#include <utility>

using std::cout;
using std::endl;
using std::logic_error;
using std::less;

template <class Key, class Data = int, class Compare = less<Key> >
class BinHeap{
    class Node{
        friend class BinHeap;
        public:
            Key first() const {return key;}
            Data second() const {return data;}
        private:
            Node(const Key& _key, const Data& _data = Data()) :
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
        ~BinHeap();
        Node* insert(Key, Data)             noexcept;
        void insert(Node&)                  noexcept;
        void erase(Node*);
        Node* minimum()                     const noexcept;
        Node* extract_minimum();
        void decrease_key(Node*, Key);
        void print(Node*, int)              const noexcept;
    private:
        Node* merge(Node*, Node*)           noexcept;
        Node* merge_roots(Node*, Node*)     noexcept;
        void link(Node*, Node*)             noexcept;
        void destroy(Node*)                 noexcept;

        Node* root;
};

#include "binheap.hpp"

#endif // BINHEAP_H_INCLUDED

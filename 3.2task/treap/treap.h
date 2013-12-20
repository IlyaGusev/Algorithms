#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED

#include <iostream>
#include <memory>
#include <vector>
#include "../../3.1task/speedtest/speedtest.h"

using std::shared_ptr;
using std::weak_ptr;
using std::cout;
using std::cin;
using std::endl;
using std::less;
using std::vector;

template <class Key, class Priority, class CKey = less<Key>, class CPriority = less<Priority> >
class Treap{
    public:
        struct Node{
            friend class Treap;
            Node() : _key(), _priority(), _left(nullptr), _right(nullptr), _parent() {}
            Node(Key k, Priority p) : _key(k), _priority(p), _left(nullptr), _right(nullptr), _parent() {}
            public:
                Key key()                       const noexcept {return _key;}
                Priority priority()             const noexcept {return _priority;}
                shared_ptr<Node> left()         const noexcept {return _left;}
                shared_ptr<Node> right()        const noexcept {return _right;}
                shared_ptr<Node> parent()       const noexcept {return _parent;}
            private:
                Key _key;
                Priority _priority;
                shared_ptr<Node> _left;
                shared_ptr<Node> _right;
                weak_ptr<Node> _parent;
        };
        Treap() : _root(nullptr) {}
        void build(vector<Priority>&)           noexcept;
        void merge(Treap&)                      noexcept;
        void split(Key)                         noexcept;
        void insert(Key, Priority)              noexcept;
        void erase(Key)                         noexcept;
        void clear()                            noexcept;
        shared_ptr<Node> minimum()              const noexcept;
        shared_ptr<Node> maximum()              const noexcept;
        shared_ptr<Node> root()                 const noexcept {return _root;}
        void print(shared_ptr<Node>, int, bool) const noexcept;
    private:
        shared_ptr<Node> _root;
        shared_ptr<Node> merge(shared_ptr<Node>, shared_ptr<Node>) noexcept;
        shared_ptr<Node> split(shared_ptr<Node>, Key) noexcept;
};

#include "treap.hpp"

#endif // TREAP_H_INCLUDED

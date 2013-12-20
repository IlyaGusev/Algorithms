#ifndef DSU_H_INCLUDED
#define DSU_H_INCLUDED

#include <iostream>
#include <vector>
#include <unordered_map>
using std::unordered_map;
using std::vector;
using std::make_pair;

template <class T>
class DSU{
    class Node{
        friend class DSU;
        Node* parent;
        T const& key;
        int rank;
        Node(T const & _key) : parent(), key(_key), rank(0) {}
    };
    public:
        ~DSU(){
            for (auto& i: nodes)
                delete i;
            nodes.clear();
        }
        void make_set(T const& _key){
            nodes.push_back(new Node(_key));
            nodes.back()->parent = nodes.back();
            pointers.insert(make_pair(_key, nodes.size()-1));
        }
        T const& find_set(T const & _key){
            Node* _node = nodes[pointers.at(_key)];
            if (_node->parent!=_node)
                _node->parent = nodes[pointers[find_set(_node->parent->key)]];
            return _node->parent->key;
        }
        T const & merge(T const& f, T const& s) {
            return link(nodes[pointers[find_set(f)]], nodes[pointers[find_set(s)]]);
        }
    private:
        T const & link(Node* f, Node* s){
            if (f->rank>s->rank){
                s->parent = f;
                return f->key;
            }else{
                f->parent = s;
                if (f->rank == s->rank)
                    s->rank++;
                return s->key;
            }
        }

        unordered_map <T, int> pointers;
        vector<Node*> nodes;
};

#endif // DSU_H_INCLUDED

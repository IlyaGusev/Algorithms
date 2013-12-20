#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <memory>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include "../dsu/dsu.h"
#include "../heaps/fibheap/fibheap.h"

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::map;
using std::vector;
using std::set;
using std::stack;
using std::queue;
using std::sort;
using std::min;
using std::ostream;
using std::istream;
using std::logic_error;

template <class I, class E>
struct PairCompare{
    bool operator()(pair<I, E> f, pair<I, E> s){
        return (f.second<s.second);
    }
};

template <class I, class N, class E>
class Graph{
    public:
    class Edge;
    class Node;
    typedef typename unordered_map<I, shared_ptr<Node> >::const_iterator iterator_node;
    typedef typename map<pair<I, I>, shared_ptr<Edge> >::const_iterator iterator_edge;

    class Node{
        friend class Graph;
        private:
            I id;
            N value;
            unordered_map<I, weak_ptr<Edge> > children;
            unordered_map<I, weak_ptr<Edge> > parents;
        public:
            Node(I const&);
            Node(I const&, N const&);
            Node(I const&, N&&);
            Node(Node&)                                                 = delete;
            Node(Node&&)                                                = delete;

            I getId()                                                   const;
            N getValueConst()                                           const;
            N& getValue()                                               ;
        };

    class Edge{
        friend class Graph;
        private:
            E value;
            pair< weak_ptr<Node>, weak_ptr<Node> > nodes;
        public:
            Edge(weak_ptr<Node>, weak_ptr<Node>);
            Edge(weak_ptr<Node>, weak_ptr<Node>, E const &);
            Edge(weak_ptr<Node>, weak_ptr<Node>, E &&);
            Edge(Edge const&)                                           = delete;
            Edge(Edge const&&)                                          = delete;

            E getValueConst()                                           const;
            E& getValue();
            pair<I, I> getNodes()                                       const;
            pair< weak_ptr<Node>, weak_ptr<Node> > getNodesPointers()   const
            {return nodes;}

    };

    template <class Container>
    class iterator_search{
        protected:
            unordered_map<I, int> colors;
            const Graph* G;
            Container touched;
            iterator_node current;
            I beginning;
        public:
            iterator_search(const Graph*);
            iterator_search(const Graph*, I const &);
            iterator_search(const Graph*, iterator_node);
            iterator_search(iterator_search const &);
            iterator_search(iterator_search &&);
            void swap(iterator_search &) noexcept;
            void operator=(iterator_search const &);
            void operator=(iterator_search &&);

            shared_ptr<Node> operator->()                               const;
            Node& operator*();
            bool operator ==(iterator_search const&)                    const;
            bool operator !=(iterator_search const&)                    const;
    };
    public:
        class iterator_dfs : public iterator_search<stack<I>>{
            public:
                iterator_dfs(const Graph* _G);
                iterator_dfs(const Graph* _G, I const & _id);
                iterator_dfs(const Graph* _G, iterator_node _it);
                iterator_dfs(iterator_dfs const & _it);
                iterator_dfs(iterator_dfs && _it);

                void operator=(iterator_dfs const & _it);
                void operator=(iterator_dfs && _it);

                iterator_dfs& operator++();
                iterator_dfs operator++(int);
        };

        class pseudo_iterator_dfs : public iterator_search<stack<I>>{
            public:
                pseudo_iterator_dfs(const Graph* _G);
                pseudo_iterator_dfs(const Graph* _G, I const & _id);
                pseudo_iterator_dfs(const Graph* _G, iterator_node _it);
                pseudo_iterator_dfs(pseudo_iterator_dfs const & _it);
                pseudo_iterator_dfs(pseudo_iterator_dfs && _it);

                void operator=(pseudo_iterator_dfs const & _it);
                void operator=(pseudo_iterator_dfs && _it);

                pseudo_iterator_dfs& operator++();
                pseudo_iterator_dfs operator++(int);

                int getColor()                                           const;
        };

        class iterator_bfs : public iterator_search<queue<I>>{
            public:
                iterator_bfs(const Graph* _G);
                iterator_bfs(const Graph* _G, I const & _id);
                iterator_bfs(const Graph* _G, iterator_node _it);
                iterator_bfs(iterator_bfs const & _it);
                iterator_bfs(iterator_bfs && _it);

                void operator=(iterator_bfs const & _it);
                void operator=(iterator_bfs && _it);

                iterator_bfs& operator++();
                iterator_bfs operator++(int);
        };

        Graph();
        ~Graph();
        Graph(Graph const&)                                             ;
        Graph(Graph&&)                                                  ;
        void operator = (Graph const &)                                 = delete;
        void operator =(Graph&&)                                        = delete;

        iterator_node insertNode(I const&, N const&);
        iterator_node insertNode(I const&);
        iterator_edge insertEdge(I const&, I const&, E const&);
        iterator_edge insertEdge(I const&, I const&);
        void          insertBiEdge(I const&, I const&, E const&);
        void eraseNode(I const&);
        void eraseEdge(I const&, I const&);
        void eraseNode(iterator_node);
        void eraseEdge(iterator_edge);

        E& accessEdge(I const&, I const&);

        vector<shared_ptr<Edge>> getOutEdges(I const&)                             const;
        vector<shared_ptr<Edge>> getInEdges(I const&)                              const;
        vector<shared_ptr<Node>> getOutNodes(I const&)                             const;
        vector<shared_ptr<Node>> getInNodes(I const&)                              const;
        vector<shared_ptr<Node>> getAllNodes()                                     const;
        vector<shared_ptr<Edge>> getAllEdges()                                     const;

        N const& operator[](I const&)                                   const;
        N& operator[](I const&);

        void clear();
        bool empty()                                                    const;
        int size()                                                      const;

        iterator_dfs begin_dfs()                                        const;
        iterator_dfs begin_dfs(I const & i)                             const;
        iterator_dfs end_dfs()                                          const;

        pseudo_iterator_dfs begin_pseudo_dfs()                          const;
        pseudo_iterator_dfs begin_pseudo_dfs(I const & i)               const;
        pseudo_iterator_dfs end_pseudo_dfs()                            const;

        iterator_bfs begin_bfs()                                        const;
        iterator_bfs begin_bfs(I const & i)                             const;
        iterator_bfs end_bfs()                                          const;

        iterator_node begin()                                           const;
        iterator_node end()                                             const;
        iterator_edge begin_edge()                                      const;
        iterator_edge end_edge()                                        const;

        vector<vector<I>> Tarjan()                                      const;
        Graph Prim()                                                    const;
        Graph Kruskal()                                                 const;
    private:
        unordered_map< I, shared_ptr<Node> > nodes;
        map<pair<I, I>, shared_ptr<Edge> > edges;
};

#include "node.hpp"
#include "edge.hpp"
#include "iterator.hpp"
#include "graph.hpp"
#include "algorithms.hpp"
//#include "preflow.hpp"

#endif // GRAPH_H_INCLUDED

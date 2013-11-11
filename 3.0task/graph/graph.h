#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <set>
#include <stack>
#include <queue>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::map;
using std::vector;
using std::stack;
using std::queue;
using std::set;
using std::ostream;
using std::istream;
using std::logic_error;

template <class I, class N, class E>
class Graph{
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
            N getValue()                                                const;
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

            E getValue()                                                const;
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
            bool operator ==(iterator_search)                           const;
            bool operator !=(iterator_search)                           const;
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
        Graph(Graph&)                                                   = delete;
        Graph(Graph&&)                                                  = delete;
        void operator = (Graph const &)                                 = delete;
        void operator =(Graph&&)                                        = delete;

        iterator_node insertNode(I const&, N const&);
        iterator_edge insertEdge(I const&, I const&, E const&);
        void eraseNode(I const&);
        void eraseEdge(I const&, I const&);
        void eraseNode(iterator_node);
        void eraseEdge(iterator_edge);

        vector<pair<I, E> > getOutEdges(I const&)                       const;
        vector<pair<I, E> > getInEdges(I const&)                        const;
        vector<pair<I, N> > getOutNodes(I const&)                       const;
        vector<pair<I, N> > getInNodes(I const&)                        const;
        vector<pair<I, N> > getAllNodes()                               const;

        N const& operator[](I const&)                                   const;
        N& operator[](I const&);

        void clear();
        bool empty()                                                    const;

        iterator_dfs begin_dfs()                                        const;
        iterator_dfs begin_dfs(I const & i)                             const;
        iterator_dfs end_dfs()                                          const;

        iterator_bfs begin_bfs()                                        const;
        iterator_bfs begin_bfs(I const & i)                             const;
        iterator_bfs end_bfs()                                          const;

        iterator_node begin()                                           const;
        iterator_node end()                                             const;
        iterator_edge begin_edge()                                      const;
        iterator_edge end_edge()                                        const;

    private:
        unordered_map< I, shared_ptr<Node> > nodes;
        map<pair<I, I>, shared_ptr<Edge> > edges;
};

#include "node.hpp"
#include "edge.hpp"
#include "iterator.hpp"
#include "graph.hpp"

#endif // GRAPH_H_INCLUDED

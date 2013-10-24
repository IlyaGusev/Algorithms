#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <set>
#include <string>

using std::vector;
using namespace std;
template <class F, class S, class T> struct trine;
template <class F, class S, class T> ostream& operator<< (ostream&, trine<F,S,T> const &);
template <class F, class S, class T>
struct trine{
    F first;
    S second;
    T third;
    trine() : first(F()), second(S()), third(T()) {}
    trine(F _f, S _s, T _t) : first(_f), second(_s), third(_t){}
    bool operator==(const trine& rhs){
        return (rhs.first==first && rhs.second==second && rhs.third==third);
    }
    friend ostream& operator<< <>(ostream& s, trine<F,S,T> const & rhs);
};
template <class F, class S, class T>
    ostream& operator<< (ostream& s, trine<F,S,T> const & rhs){
        s<<"trine ("<<rhs.first<<" "<<rhs.second<<" "<<rhs.third<<")";
        return s;
    }

template <class E> struct Edge;
template <class E> istream& operator>> (istream&, Edge<E>&);
template <class E> ostream& operator<< (ostream&, Edge<E> const &);
template <class E>
struct Edge{
    int index;
    int first;
    int second;
    E value;
    Edge() : index(0), first(0), second(0), value(E()) {}
    Edge(int __index, int __f, int __s, E __val) : index(__index), first(__f), second(__s), value(__val) {}
    bool operator==(const Edge& rhs) const{ return (index==rhs.index); }
    bool operator< (const Edge& rhs) const{ return (index<rhs.index); }
    Edge<E>& operator=(const Edge<E>& rhs){
        index=rhs.index;
        first=rhs.first;
        second=rhs.second;
        value=rhs.value;
        return (*this);
    }
    friend istream& operator>> <>(istream& s, Edge<E>& rhs);
    friend ostream& operator<< <>(ostream& s, Edge<E> const & rhs);
};
template <class E>
    istream& operator>> (istream& s, Edge<E>& rhs){
        s>>rhs.first>>rhs.second>>rhs.value;
        return s;
    }
template <class E>
    ostream& operator<< (ostream& s, Edge<E> const & rhs){
        s<<rhs.index<<" "<<"("<<rhs.first<<" ; "<<rhs.second<<")"<<" : "<<rhs.value;
        return s;
    }

template <class N> struct Node;
template <class N> istream& operator>> (istream&, Node<N>&);
template <class N> ostream& operator<< (ostream&, Node<N> const &);
template <class N>
struct Node{
    int index;
    N value;
    Node(int __index, N __val) : index(__index), value(__val) {}
    bool operator==(const Node& rhs) const{ return (index==rhs.index && value==rhs.value); }
    bool operator< (const Node& rhs) const{ return (index<rhs.index); }
    friend istream& operator>> <>(istream& s, Node<N>& rhs);
    friend ostream& operator<< <>(ostream& s, Node<N> const & rhs);
};
template <class N>
    istream& operator>> (istream& s, Node<N>& rhs){
        s>>rhs.N;
        return s;
    }
template <class N>
    ostream& operator<< (ostream& s, Node<N> const & rhs){
        s<<rhs.index<<" "<<rhs.value;
        return s;
    }

template <class E, class N> class Graph;
template <class E, class N> istream& operator>> (istream&, Graph<E,N>&);
template <class E, class N> ostream& operator<< (ostream&, Graph<E,N> const &);

template <class E, class N>
class Graph{
    typedef pair<bool, E> EdgeProp;
private:
    list< Edge<E> > edges;
    list< Node<N> > nodes;
public:
    Graph() : edges(list< Edge<E> >(0, Edge<E>(0, 0, 0, E()))), nodes(list< Node<N> >(0, Node<N>(0, N()))) {}


    void addNode(N);
    void addEdge(int, int, E);
    void addEdgeOnValue(N, N, E);
    void addBiEdge(int, int, E);
    void removeEdge(int);
    void removeEdge(int, int);
    void removeNode(int);

    bool            isNodeExists(N)                 const;
    Node<N>&        getNode(int)                    ;
    Edge<E>&        getEdge(int, int)               ;
    set<int>        getEdgesIndexFromNode(int)      const;
    set<Edge<E>>    getEdgesCopyFromNode(int)       const;
    set<int>        getNodesIndexFromNode(int)      const;
    set<Node<N>>    getNodesCopyFromNode(int)       const;
    set<int>        getEdgesIndexToNode(int)        const;
    set<Edge<E>>    getEdgesCopyToNode(int)         const;
    set<int>        getNodesIndexToNode(int)        const;
    set<Node<N>>    getNodesCopyToNode(int)         const;
    list<Edge<E>>   getAllEdgesCopy()               const;
    list<Node<N>>   getAllNodesCopy()               const;

    vector<E> Dijkstra(int, E);
    Graph<E,N> BFS(int);
    void DFS(bool&, list<Node<N>>&);
    void DFS_visit(int , vector<int>&, int&, bool&, list<Node<N>>&);
    pair<bool, list<Node<N>>> TSort();

    friend istream& operator>> <>(istream&, Graph<E,N>&);
    friend ostream& operator<< <>(ostream&, Graph<E,N> const &);

    struct iterator;

    typename Graph<E,N>::iterator begin(){
        return Graph<E,N>::iterator(&(*nodes.begin()), this);
    }
    typename Graph<E,N>::iterator findNode(N n){
        for (auto& i: nodes)
            if (n==i.value)
                return Graph<E,N>::iterator(&i, this);
        cout<<"Not found"<<endl;
        return Graph<E,N>::iterator();
    }
};

template <class E, class N>
struct Graph<E,N>::iterator : std::iterator<ptrdiff_t, Node<N>, Node<N>*, Node<N>&, bidirectional_iterator_tag>{
    typedef iterator          Self;
    Graph<E,N>* _graph;
    Node<N>* _node;

    iterator() : _graph(), _node() {}
    explicit iterator(Node<N>* __x, Graph<E,N>* __g) :  _graph(__g), _node(__x){}

    Node<N> operator*() const { return *(_node); }
    Node<N>* operator->() const { return _node; }
    Self& up(){
        set<int> parents=_graph->getNodesIndexToNode(_node->index);
        if (!parents.empty())
            (*this)=iterator(&_graph->getNode(*(parents.begin())), _graph);
        return (*this);
    }
    Self& down(){
        set<int> children=_graph->getNodesIndexFromNode(_node->index);
        if (!children.empty())
            (*this)=iterator(&_graph->getNode(*(children.begin())), _graph);
        return (*this);
    }
    Self& right(){
        set<int> parents=_graph->getNodesIndexToNode(_node->index);
        if (!parents.empty()){
            set<int> children;
            for (auto i : parents){
                set<int> temp=_graph->getNodesIndexFromNode(i);
                children.insert(temp.begin(), temp.end());
            }
            (*this)=iterator(&(_graph->getNode(*(++children.find(_node->index)))), _graph);
        }
        return (*this);
    }
    Self& left(){
        set<int> parents=_graph->getNodesIndexToNode(_node->index);
        if (!parents.empty()){
            set<int> children;
                for (auto i : parents){
                    set<int> temp=_graph->getNodesIndexFromNode(i);
                    children.insert(temp.begin(), temp.end());
                }
            (*this)=iterator(&(_graph->getNode(*(--children.find(_node->index)))), _graph);
        }
        return (*this);
    }
    bool operator==(const Self& __x) const { return (_node==__x._node); }
    bool operator!=(const Self& __x) const { return (_node!=__x._node); }
};

    ///Adds & removes
template <class E, class N>
    void Graph<E,N>::addNode(N __node){
        if (nodes.empty()==false)
            nodes.push_back(Node<N>(nodes.back().index+1, __node));
        else
            nodes.push_back(Node<N>(0, __node));
    }

template <class E, class N>
    void Graph<E,N>::addEdge(int __f, int __s, E __weight){
        if (edges.empty()==false)
            edges.push_back(Edge<E>(edges.back().index+1, __f, __s, __weight));
        else
            edges.push_back(Edge<E>(0, __f, __s, __weight));
    }

template <class E, class N>
    void Graph<E,N>::addEdgeOnValue(N _f, N _s, E __weight){
        int __f=0, __s=0;
        for (auto i : nodes)
            if (i.value==_f)
                __f=i.index;
            else if(i.value==_s)
                __s=i.index;
        addEdge(__f, __s, __weight);
    }

template <class E, class N>
    void Graph<E,N>::addBiEdge(int __f, int __s, E __weight){
        if (edges.empty()==false)
            edges.push_back(Edge<E>(edges.back().index+1, __f, __s, __weight));
        else
            edges.push_back(Edge<E>(0, __f, __s, __weight));
        edges.push_back(Edge<E>(edges.back().index+1, __s, __f, __weight));
    }

template <class E, class N>
    void Graph<E,N>::removeEdge(int __index){
        for (auto i : edges)
            if (i.index==__index){
                edges.remove(i);
                break;
            }
    }

template <class E, class N>
    void Graph<E,N>::removeEdge(int __f, int __s){
        for (typename list< Edge<E> >::iterator it=edges.begin(); it!=edges.end(); it++)
            if ((*it).first==__f && (*it).second==__s){
                typename list< Edge<E> >::iterator temp_it(it);
                it--;
                edges.remove((*temp_it));
            }
    }

template <class E, class N>
    void Graph<E,N>::removeNode(int __index){
        if (__index>=0){
            for (typename list< Edge<E> >::iterator it=edges.begin(); it!=edges.end(); it++)
                if ((*it).first==__index || (*it).second==__index){
                    typename list< Edge<E> >::iterator temp_it(it);
                    it--;
                    edges.remove((*temp_it));
                }
            for (auto i : nodes)
                if (i.index==__index){
                    nodes.remove(i);
                    break;
                }
        }
    }

    ///Input & output
template <class E, class N>
    ostream& operator<< (ostream& s, Graph<E,N> const & m){
        for (auto i : m.nodes)
            s<<i<<endl;
        s<<endl;
        for (auto i : m.edges)
            s<<i<<endl;
        s<<endl;
        return s;
    }

template <class E, class N>
    istream& operator>> (istream& stream, Graph<E,N> & m){
        string str;
        while(str!="exit" && str!="end" && str!="q"){
            stream>>str;
            if (str=="biedge"){
                int f, s;
                E data;
                stream>>f>>s>>data;
                m.addBiEdge(f,s,data);
                str="";
            }
            if (str=="node" || str=="Node"){
                N data;
                stream>>data;
                m.addNode(data);
                str="";
            }
            if (str=="edge" || str=="Edge"){
                int f, s;
                E data;
                stream>>f>>s>>data;
                m.addEdge(f,s,data);
                str="";
            }
        }
        return stream;
    }

    ///Getters
template <class E, class N>
    bool Graph<E,N>::isNodeExists(N _node) const{
        for (auto i : nodes)
            if (i.value==_node)
                return true;
        return false;
    }

template <class E, class N>
    Node<N>& Graph<E,N>::getNode(int __index){
        for (auto& i : nodes)
            if (i.index==__index)
                return (i);
        cout<<"Not found"<<endl;
        return (*nodes.begin());
    }

template <class E, class N>
    Edge<E>& Graph<E,N>::getEdge(int lhs, int rhs){
        for (auto& i : edges)
            if (i.first==lhs && i.second==rhs)
                return i;
        cout<<"Not found"<<endl;
        return (*edges.begin());
    }

template <class E, class N>
    set<int> Graph<E,N>::getEdgesIndexFromNode(int __index) const{
        set<int> res;
        for (auto i : edges)
            if (i.first==__index)
                res.insert(i.index);
        return res;
    }

template <class E, class N>
    set<Edge<E>> Graph<E,N>::getEdgesCopyFromNode(int __index) const{
        set<Edge<E>> res;
        for (auto i : edges)
            if (i.first==__index)
                res.insert(i);
        return res;
    }

template <class E, class N>
    set<int> Graph<E,N>::getNodesIndexFromNode(int __index) const{
        set<int> res;
        for (auto i : edges)
            if (i.first==__index)
                res.insert(i.second);
        return res;
    }

template <class E, class N>
    set<Node<N>> Graph<E,N>::getNodesCopyFromNode(int __index) const{
        set<Node<N>> res;
        for (auto i : edges)
            if (i.first==__index)
                res.insert(i);
        return res;
    }

template <class E, class N>
    set<int> Graph<E,N>::getEdgesIndexToNode(int __index) const{
        set<int> res;
        for (auto i : edges)
            if (i.second==__index)
                res.insert(i.index);
        return res;
    }

template <class E, class N>
    set<Edge<E>> Graph<E,N>::getEdgesCopyToNode(int __index) const{
        set<Edge<E>> res;
        for (auto i : edges)
            if (i.second==__index)
                res.insert(i);
        return res;
    }

template <class E, class N>
    set<int> Graph<E,N>::getNodesIndexToNode(int __index) const{
        set<int> res;
        for (auto i : edges)
            if (i.second==__index)
                res.insert(i.first);
        return res;
    }

template <class E, class N>
    set<Node<N>> Graph<E,N>::getNodesCopyToNode(int __index) const{
        set<Node<N>> res;
        for (auto i : edges)
            if (i.second==__index)
                res.insert(i);
        return res;
    }

template <class E, class N>
    list< Edge<E> > Graph<E,N>::getAllEdgesCopy() const{
        return(list< Edge<E> >(edges));
    }

template <class E, class N>
    list< Node<N> > Graph<E,N>::getAllNodesCopy() const{
        return(list< Node<N> >(nodes));
    }

    /// Algorithms
template <class E, class N>
    vector<E> Graph<E,N>::Dijkstra(int __index, E max_distance){
        vector<bool> visited=vector<bool>(nodes.back().index+1, true);
        for (auto i : nodes)
            visited[i.index]=false;
        vector<E> distance=vector<E>(nodes.back().index+1, max_distance);
        distance[__index]=0;
        bool loop_exit_flag=false;
        while(loop_exit_flag!=true){
            E min_distance=max_distance;
            int min_distance_node=__index;
            loop_exit_flag=true;
            for(int i=0; i<visited.size(); i++)
                if (visited[i]==false){
                    loop_exit_flag=false;
                    if (distance[i]<=min_distance){
                        min_distance=distance[i];
                        min_distance_node=i;
                    }
                }
            if(loop_exit_flag==true)
                break;
            visited[min_distance_node]=true;

            set<Edge<E>> nbh=getEdgesCopyFromNode(min_distance_node);
            for (auto i : nbh)
                if (visited[i.second])
                    nbh.erase(i);
            for (auto i : nbh)
                if (distance[i.first]+i.value<distance[i.second])
                    distance[i.second]=distance[i.first]+i.value;
        }
        return distance;
    }

template <class E, class N>
    Graph<E,N> Graph<E,N>::BFS(int __index){
        vector<int> colors(nodes.size(), 0);
        Graph<E, int> tree;
        tree.addNode(__index);
        colors[__index]=1;
        list<int> gray_nodes;
        gray_nodes.push_back(__index);

        while(!gray_nodes.empty()){
            int current=gray_nodes.back();
            set<int> children=getNodesIndexFromNode(current);
            gray_nodes.pop_back();
            for (auto i : children){
                if (colors[i]==0){
                    colors[i]=1;
                    tree.addNode(i);
                    tree.addEdge(current, i, getEdge(current, i).value);
                    gray_nodes.push_back(i);
                }
            }
            colors[current]=2;
        }
        return tree;
    }

template <class E, class N>
    void Graph<E,N>::DFS(bool& cycled, list<Node<N>>& ordered){
        vector<int> colors(nodes.size(), 0);
        int time=0;
        for (auto i : nodes)
            if (colors[i.index]==0){
                DFS_visit(i.index, colors, time, cycled, ordered);
            }
    }
template <class E, class N>
    void Graph<E,N>::DFS_visit(int current, vector<int>& colors, int& time, bool& cycled, list<Node<N>>& ordered){
        colors[current]=1;
        time++;
        set<int> children=getNodesIndexFromNode(current);
        for (auto i : children){
            if (colors[i]==0)
                DFS_visit(i, colors, time, cycled, ordered);
            if (colors[i]==1)
                cycled=true;
        }
        ordered.push_back(getNode(current));
        colors[current]=2;

        time++;
    }
template <class E, class N>
    pair<bool, list<Node<N>>> Graph<E,N>::TSort(){
        list<Node<N>> ordered;
        bool cycled=false;
        DFS(cycled, ordered);
        return make_pair(cycled, ordered);
    }


#endif // GRAPH_H_INCLUDED

#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

template <class I, class N, class E>
    Graph<I, N, E>::Graph() : nodes(), edges(){}
template <class I, class N, class E>
    Graph<I, N, E>::Graph(Graph const& g) : nodes(g.nodes), edges(g.edges){}
template <class I, class N, class E>
    Graph<I, N, E>::Graph(Graph && g){
        nodes = std::move(g.nodes);
        edges = std::move(g.edges);
    }

template <class I, class N, class E>
    Graph<I, N, E>::~Graph(){ clear(); }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_node Graph<I, N, E>::insertNode(I const& _id, N const& _value){
        if (nodes.find(_id)==nodes.end())
            return nodes.insert(make_pair(_id, shared_ptr<Node>(new Node(_id, _value)))).first;
        else
            throw logic_error("Error in insertNode. Node has already existed");
    }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_node Graph<I, N, E>::insertNode(I const& _id){
        return insertNode(_id, N());
    }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_edge Graph<I, N, E>::insertEdge(I const& _id1, I const& _id2, E const& _value){
        iterator_node it1 = nodes.find(_id1);
        iterator_node it2 = nodes.find(_id2);
        if (it1==nodes.end() || it2==nodes.end())
            throw logic_error("Error in insertEdge. There is no node to insert edge.");
        if (edges.find(make_pair(_id1, _id2))!=edges.end())
            throw logic_error("Error in insertEdge. Edge has already existed");
        shared_ptr<Edge> new_edge(new Edge(static_cast<weak_ptr<Node>>(it1->second),
                                  static_cast<weak_ptr<Node>>(it2->second), _value));

        (it1->second->children).insert(make_pair(_id2, static_cast<weak_ptr<Edge>>(new_edge)));
        (it2->second->parents).insert(make_pair(_id1, static_cast<weak_ptr<Edge>>(new_edge)));

        return edges.insert(make_pair(make_pair(_id1, _id2), new_edge)).first;
    }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_edge Graph<I, N, E>::insertEdge(I const& _id1, I const& _id2){
        return insertEdge(_id1, _id2, E());
    }

template <class I, class N, class E>
    void Graph<I, N, E>::insertBiEdge(I const& _id1, I const& _id2, E const& _value){
        insertEdge(_id1, _id2, _value);
        insertEdge(_id2, _id1, _value);
    }

template <class I, class N, class E>
     N const& Graph<I, N, E>::operator[](I const& _id) const{
        iterator_node it = nodes.find(_id);
        if (it==nodes.end())
            throw logic_error("Error in operator[]. There is no node with this id.");
        else
            return it->second->value;
     }

template <class I, class N, class E>
    N& Graph<I, N, E>::operator[](I const& _id){
        auto it = nodes.find(_id);
        if (it==nodes.end())
            throw logic_error("Error in operator[]. There is no node with this id.");
        else
            return it->second->value;
    }

template <class I, class N, class E>
    E& Graph<I, N, E>::accessEdge(I const& _id1, I const& _id2){
        auto it = nodes.find(_id1);
        if (it!=nodes.end()){
            return it->second->children.at(_id2);
        }
        else
            throw logic_error("Error in accessEdge. There is no node with this id.");
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Edge> > Graph<I, N, E>::getOutEdges(I const& _id) const{
        auto it = nodes.find(_id);
        if (it!=nodes.end()){
            vector<shared_ptr<Edge>> answer;
            vector< typename unordered_map<I, weak_ptr<Edge> >::iterator > erasing;
            for (auto i=it->second->children.begin(); i!=it->second->children.end(); i++){
                if(!i->second.expired())
                    answer.push_back(i->second.lock());
                else
                    erasing.push_back(i);
            }
            for (auto& i: erasing)
                it->second->children.erase(i);
            return answer;
        }
        else
            throw logic_error("Error in getOutEdges. There is no node with this id.");
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Edge>> Graph<I, N, E>::getInEdges(I const& _id) const{
        auto it = nodes.find(_id);
        if (it!=nodes.end()){
            vector<shared_ptr<Edge>> answer;
            vector< typename unordered_map<I, weak_ptr<Edge> >::iterator> erasing;
            for (auto i=it->second->parents.begin(); i!=it->second->parents.end(); i++){
                if(!i->second.expired())
                    answer.push_back(i->second.lock());
                else
                    erasing.push_back(i);
            }
            for (auto& i: erasing){
                it->second->parents.erase(i);
            }
            return answer;
        }
        else
            throw logic_error("Error in getInEdges. There is no node with this id.");
    }

template <class I, class N, class E>
    void Graph<I, N, E>::eraseEdge(I const& _id1, I const& _id2){
        auto it = edges.find(make_pair(_id1, _id2));
        if (it!=edges.end())
            edges.erase(it);
        else
            throw logic_error("Error in eraseEdge. There is no edge to erase.");
    }

template <class I, class N, class E>
    void Graph<I, N, E>::eraseEdge(iterator_edge it){
        edges.erase(it);
    }

template <class I, class N, class E>
    void Graph<I, N, E>::eraseNode(I const& _id){
        auto it = nodes.find(_id);
        if (it == nodes.end())
            throw logic_error("Error in eraseNode. There is no node to erase.");
        else{
            auto node = it->second;
            for (auto& i: node->children){
                if (!i.second.expired()){
                    eraseEdge(_id, i.first);
                }
            }
            for (auto& i: node->parents){
                if (!i.second.expired()){
                    eraseEdge(i.first, _id);
                }
            }
            nodes.erase(it);
        }
    }

template <class I, class N, class E>
    void Graph<I, N, E>::eraseNode(iterator_node it){
        auto node = it->second;
        for (auto& i: node->children){
            if (!i.second.expired()){
                eraseEdge(it->first, i.first);
            }
        }
        for (auto& i: node->parents){
            if (!i.second.expired()){
                eraseEdge(i.first, it->first);
            }
        }
        nodes.erase(it);
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Node>> Graph<I, N, E>::getOutNodes(I const& _id) const{
        auto it = nodes.find(_id);
        if (it!=nodes.end()){
            vector<shared_ptr<Node>> answer;
            for (auto i=it->second->children.begin(); i!=it->second->children.end(); i++){
                if(!i->second.expired())
                    answer.push_back(nodes.find(i->first)->second);
            }
            return answer;
        }
        else
            throw logic_error("Error in getOutNodes. There is no node with this id.");
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Node>> Graph<I, N, E>::getInNodes(I const& _id) const{
        auto it = nodes.find(_id);
        if (it!=nodes.end()){
            vector<shared_ptr<Node>> answer;
            for (auto i=it->second->parents.begin(); i!=it->second->parents.end(); i++){
                if(!i->second.expired())
                    answer.push_back(nodes.find(i->first)->second);
            }
            return answer;
        }
        else
            throw logic_error("Error in getInNodes. There is no node with this id.");
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Node>> Graph<I, N, E>::getAllNodes() const{
        vector<shared_ptr<Node>> answer;
        for (auto i=nodes.begin(); i!=nodes.end(); i++){
            answer.push_back(i->second);
        }
        return answer;
    }

template <class I, class N, class E>
    vector<shared_ptr<typename Graph<I, N, E>::Edge>> Graph<I, N, E>::getAllEdges() const{
        vector<shared_ptr<Edge>> answer;
        for (auto i=edges.begin(); i!=edges.end(); i++){
            answer.push_back(i->second);
        }
        return answer;
    }

template <class I, class N, class E>
    void Graph<I, N, E>::clear(){
        nodes.clear();
        edges.clear();
    }

template <class I, class N, class E>
    int Graph<I, N, E>::size() const{
        return nodes.size();
    }

template <class I, class N, class E>
    bool Graph<I, N, E>::empty() const{return nodes.empty();}

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_dfs Graph<I, N, E>::begin_dfs() const {return iterator_dfs(this);}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_dfs Graph<I, N, E>::begin_dfs(I const & i) const {return iterator_dfs(this, i);}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_dfs Graph<I, N, E>::end_dfs() const{return iterator_dfs(this, nodes.end()); }

template <class I, class N, class E>
    typename Graph<I, N, E>::pseudo_iterator_dfs Graph<I, N, E>::begin_pseudo_dfs() const {return pseudo_iterator_dfs(this);}
template <class I, class N, class E>
    typename Graph<I, N, E>::pseudo_iterator_dfs Graph<I, N, E>::begin_pseudo_dfs(I const & i) const {return pseudo_iterator_dfs(this, i);}
template <class I, class N, class E>
    typename Graph<I, N, E>::pseudo_iterator_dfs Graph<I, N, E>::end_pseudo_dfs() const{return pseudo_iterator_dfs(this, nodes.end()); }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_bfs Graph<I, N, E>::begin_bfs() const{return iterator_bfs(this);}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_bfs Graph<I, N, E>::begin_bfs(I const & i) const {return iterator_bfs(this, i);}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_bfs Graph<I, N, E>::end_bfs() const{return iterator_bfs(this, nodes.end()); }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_node Graph<I, N, E>::begin() const {return nodes.begin();}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_node Graph<I, N, E>::end() const {return nodes.end();}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_edge Graph<I, N, E>::begin_edge() const {return edges.begin();}
template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_edge Graph<I, N, E>::end_edge() const {return edges.end();}

#endif // GRAPH_HPP_INCLUDED

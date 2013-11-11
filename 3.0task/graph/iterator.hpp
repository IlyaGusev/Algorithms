#ifndef ITERATOR_HPP_INCLUDED
#define ITERATOR_HPP_INCLUDED

template <class I, class N, class E>
template <class Container>
    Graph<I, N, E>::iterator_search<Container>::iterator_search(const Graph* _G) : colors(), G(_G),
                                                                                   touched(), current(G->nodes.begin()),
                                                                                   beginning(current->first){
        auto it = G->nodes.begin();
        colors.insert(make_pair(it->first, 2));
        ++it;
        for (; it!= G->nodes.end(); it++)
            colors.insert(make_pair(it->first, 0));
    }

template <class I, class N, class E>
template <class Container>
    Graph<I, N, E>::iterator_search<Container>::iterator_search(const Graph* _G, I const & _id) : colors(), G(_G),
                                                                                                  touched(),
                                                                                                  current(G->nodes.find(_id)){
        if (current==G->nodes.end())
            throw logic_error("Error in creating DFS or BFS or BFS search iterator. There is no node with this id.");
        beginning = current->first;
        for (auto it = G->nodes.begin(); it!= G->nodes.end(); it++)
            if(it->first!=_id)
                colors.insert(make_pair(it->first, 0));
            else
                colors.insert(make_pair(it->first, 2));
    }

template <class I, class N, class E>
template <class Container>
    Graph<I, N, E>::iterator_search<Container>::iterator_search(const Graph* _G, iterator_node _it) : colors(), G(_G),
                                                                                                      touched(),
                                                                                                      current(_it){
        if (_it!=G->nodes.end()){
            beginning = current->first;
            for (auto it = G->nodes.begin(); it!= G->nodes.end(); it++)
                if(it->first!=_it->first)
                    colors.insert(make_pair(it->first, 0));
                else
                    colors.insert(make_pair(it->first, 2));
        }
    }


template <class I, class N, class E>
template <class Container>
    Graph<I, N, E>::iterator_search<Container>::iterator_search(iterator_search const& _it): colors(_it.colors), G(_it.G),
                                                                                             touched(),
                                                                                             current(_it.current),
                                                                                             beginning(_it.beginning){}

template <class I, class N, class E>
template <class Container>
    Graph<I, N, E>::iterator_search<Container>::iterator_search(iterator_search && _it) : G(_it.G){
        colors = std::move(_it.colors);
        touched = std::move(_it.touched);
        current = std::move(_it.current);
        beginning = std::move(_it.beginning);
    }

template <class I, class N, class E>
template <class Container>
    void Graph<I, N, E>::iterator_search<Container>::swap (iterator_search & _it) noexcept{
        std::swap(colors, _it.colors);
        std::swap(touched, _it.touched);
        std::swap(current, _it.current);
        std::swap(G, _it.G);
        std::swap(beginning, _it.beginning);
    }

template <class I, class N, class E>
template <class Container>
    void Graph<I, N, E>::iterator_search<Container>::operator=(iterator_search const & _it){
        colors = _it.colors;
        current = _it.current;
        touched = _it.touched;
        G = _it.G;
        beginning = _it.beginning;
    }

template <class I, class N, class E>
template <class Container>
    void Graph<I, N, E>::iterator_search<Container>::operator =(iterator_search && _it){
        colors = std::move(_it.colors);
        touched = std::move(_it.touched);
        current = std::move(_it.current);
        G = _it.G;
        beginning = std::move(_it.beginning);
    }

template <class I, class N, class E>
template <class Container>
    shared_ptr<typename Graph<I, N, E>::Node> Graph<I, N, E>::iterator_search<Container>::operator->() const{
        if (current!=G->nodes.end()){
            return (current->second);
        }
        else throw logic_error("Error in DFS or BFS iterator operator->.");
    }

template <class I, class N, class E>
template <class Container>
    typename Graph<I, N, E>::Node& Graph<I, N, E>::iterator_search<Container>::operator*(){
        if (current!=G->nodes.end()){
            return (*current->second);
        }
        else throw logic_error("Error in DFS or BFS iterator operator*.");
    }

template <class I, class N, class E>
template <class Container>
    bool Graph<I, N, E>::iterator_search<Container>::operator ==(iterator_search _it) const{
        if ((G == _it.G && beginning == _it.beginning && current == _it.current) ||
            (current==G->nodes.end() && _it.current==G->nodes.end()))
            return true;
        else
            return false;
    }

template <class I, class N, class E>
template <class Container>
    bool Graph<I, N, E>::iterator_search<Container>::operator !=(iterator_search _it) const{
        return !((*this)==_it);
    }

///----------------------------------------------------------------------------------------///

template <class I, class N, class E>
    Graph<I, N, E>::iterator_dfs::iterator_dfs(const Graph* _G) : iterator_search<stack<I>>(_G){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_dfs::iterator_dfs(const Graph* _G, I const & _id) : iterator_search<stack<I>>(_G, _id){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_dfs::iterator_dfs(const Graph* _G, iterator_node _it) : iterator_search<stack<I>>(_G, _it){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_dfs::iterator_dfs(iterator_dfs const & _it) : iterator_search<stack<I>>(_it){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_dfs::iterator_dfs(iterator_dfs && _it) : iterator_search<stack<I>>(_it){}

template <class I, class N, class E>
    void Graph<I, N, E>::iterator_dfs::operator=(iterator_dfs const & _it) {return iterator_search<stack<I>>::operator=(_it);}
template <class I, class N, class E>
    void Graph<I, N, E>::iterator_dfs::operator=(iterator_dfs && _it) {return iterator_search<stack<I>>::operator=(_it);}

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_dfs& Graph<I, N, E>::iterator_dfs::operator++(){
        if (this->current!=this->G->nodes.end()){
            for (auto it = this->current->second->children.begin(); it!=this->current->second->children.end(); it++)
                if (this->colors[it->first]==0){
                    this->touched.push(it->first);
                    this->colors[it->first] = 1;
                }
            if (!this->touched.empty()){
                this->current = this->G->nodes.find(this->touched.top());
                this->colors[this->touched.top()] = 2;
                this->touched.pop();
                return (*this);
            }
            else{
                for (auto it = this->colors.begin(); it!= this->colors.end(); it++)
                    if (it->second == 0){
                        it->second = 2;
                        this->current = this->G->nodes.find(it->first);
                        return (*this);
                    }
                this->current = this->G->nodes.end();
                return (*this);
            }
        }
        return (*this);
    }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_dfs Graph<I, N, E>::iterator_dfs::operator++(int){
        auto temp((*this));
        ++(*this);
        return temp;
    }

///----------------------------------------------------------------------------------------///

template <class I, class N, class E>
    Graph<I, N, E>::iterator_bfs::iterator_bfs(const Graph* _G) : iterator_search<queue<I>>(_G){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_bfs::iterator_bfs(const Graph* _G, I const & _id) : iterator_search<queue<I>>(_G, _id){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_bfs::iterator_bfs(const Graph* _G, iterator_node _it) : iterator_search<queue<I>>(_G, _it){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_bfs::iterator_bfs(iterator_bfs const & _it) : iterator_search<queue<I>>(_it){}
template <class I, class N, class E>
    Graph<I, N, E>::iterator_bfs::iterator_bfs(iterator_bfs && _it) : iterator_search<queue<I>>(_it){}

template <class I, class N, class E>
    void Graph<I, N, E>::iterator_bfs::operator=(iterator_bfs const & _it) {return iterator_search<queue<I>>::operator=(_it);}
template <class I, class N, class E>
    void Graph<I, N, E>::iterator_bfs::operator=(iterator_bfs && _it) {return iterator_search<queue<I>>::operator=(_it);}

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_bfs& Graph<I, N, E>::iterator_bfs::operator++(){
        if (this->current!=this->G->nodes.end()){
            for (auto it = this->current->second->children.begin(); it!=this->current->second->children.end(); it++)
                if (this->colors[it->first]==0){
                    this->touched.push(it->first);
                    this->colors[it->first] = 1;
                }
            if (!this->touched.empty()){
                this->current = this->G->nodes.find(this->touched.front());
                this->colors[this->touched.front()] = 2;
                this->touched.pop();
                return (*this);
            }
            else{
                for (auto it = this->colors.begin(); it!= this->colors.end(); it++)
                    if (it->second == 0){
                        it->second = 2;
                        this->current = this->G->nodes.find(it->first);
                        return (*this);
                    }
                this->current = this->G->nodes.end();
                return (*this);
            }
        }
        return (*this);
    }

template <class I, class N, class E>
    typename Graph<I, N, E>::iterator_bfs Graph<I, N, E>::iterator_bfs::operator++(int){
        auto temp((*this));
        ++(*this);
        return temp;
    }

#endif // ITERATOR_HPP_INCLUDED

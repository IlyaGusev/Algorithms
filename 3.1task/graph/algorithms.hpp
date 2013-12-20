#ifndef ALGORITHMS_HPP_INCLUDED
#define ALGORITHMS_HPP_INCLUDED

template <class I, class N, class E>
    vector<vector<I>> Graph<I, N, E>::Tarjan() const{
        vector<vector<I> >                  answer;
        stack<I>                            algo_stack;
        unordered_map<I, pair<int, int> >   indexes;

        vector<shared_ptr<Node> > all = getAllNodes();
        for (auto it = all.begin(); it != all.end(); it++)
            indexes.insert(make_pair((*it)->getId(), make_pair(-1, -1)));

        int i =0;
        for (auto it = begin_pseudo_dfs(); it != end_pseudo_dfs(); it++){
            if (it.getColor() != 1){
                vector<shared_ptr<Node>> children = getOutNodes(it->getId());
                for (auto inner_it = children.begin(); inner_it != children.end(); inner_it++)
                    if ((indexes[it->getId()].second > indexes[(*inner_it)->getId()].second) && indexes[(*inner_it)->getId()].second != -1)
                        indexes[it->getId()].second = indexes[(*inner_it)->getId()].second;

                if (indexes[it->getId()].second == indexes[it->getId()].first){
                    vector<I> component;
                    while(it->getId() != algo_stack.top()){
                        indexes[it->getId()].second = -1;
                        component.push_back(algo_stack.top());
                        algo_stack.pop();
                    }
                    indexes[algo_stack.top()].second = -1;
                    component.push_back(algo_stack.top());
                    algo_stack.pop();
                    answer.push_back(component);
                }
            }else{
                algo_stack.push(it->getId());
                indexes[it->getId()].first = i;
                indexes[it->getId()].second = i;
                i++;
            }
        }
        return answer;
    }

template <class I, class N, class E>
    Graph<I, N, E> Graph<I, N, E>::Prim() const{
        E max_edge = E();
        for (auto it = begin_edge(); it!= end_edge(); it++)
            if (it->second->getValue()>max_edge)
                max_edge = it->second->getValue();

        Graph<I, N, E> tree;
        FibHeap<pair<iterator_node, E>, int, PairCompare<iterator_node,E> > heap;
        map<I, typename FibHeap<pair<iterator_node, E>, int, PairCompare<iterator_node,E> >::Node*>  heap_ptrs;
        unordered_map<I, bool> used;
        unordered_map<I, E> distances;
        map<I, iterator_node> parents;

        for (auto it = begin(); it!= end(); it++){
            tree.insertNode(it->first, it->second->getValue());
            auto n = heap.insert(make_pair(it, max_edge));
            heap_ptrs.insert(make_pair(it->first, n));
        }
        for (auto it = tree.begin(); it!= tree.end(); it++)
            used.insert(make_pair(it->first, 0));
        for (auto it = tree.begin(); it!= tree.end(); it++)
            distances.insert(make_pair(it->first, max_edge));
        for (auto it = tree.begin(); it!= tree.end(); it++)
            parents.insert(make_pair(it->first, tree.end()));

        auto current = heap.extract_minimum()->first().first;
        while(!heap.empty()){
            vector<shared_ptr<Edge>> children = getOutEdges(current->second->getId());
            for (auto it = children.begin(); it!=children.end(); it++){
                if (!used[(*it)->getNodes().second] && (*it)->getValue()<distances[(*it)->getNodes().second]){
                    distances[(*it)->getNodes().second] = (*it)->getValue();
                    heap.decrease_key(heap_ptrs[(*it)->getNodes().second],
                                      make_pair(heap_ptrs[(*it)->getNodes().second]->first().first, (*it)->getValue()));
                    parents[(*it)->getNodes().second] = current;
                }
            }
            used[current->first] = 1;
            current = heap.extract_minimum()->first().first;
            tree.insertEdge(parents[current->first]->first, current->first);
        }
        return tree;
    }

template <class I, class N, class E>
    Graph<I, N, E> Graph<I, N, E>::Kruskal() const{
        vector<shared_ptr<Edge>> all_edges = getAllEdges();
        Graph<I, N, E> tree;
        DSU<I> dsu;
        for (auto it = begin(); it!= end(); it++){
            auto v = tree.insertNode(it->first, it->second->getValue());
            dsu.make_set(v->first);
        }
        sort(all_edges.begin(), all_edges.end(), [](shared_ptr<Edge> a, shared_ptr<Edge> b){ return a->getValue() < b->getValue();});
        for (auto& it : all_edges){
            if (dsu.find_set(it->getNodes().first)!=dsu.find_set(it->getNodes().second)){
                tree.insertBiEdge(it->getNodes().first, it->getNodes().second, it->getValue());
                dsu.merge(it->getNodes().first, it->getNodes().second);
            }
        }
        return tree;
    }

#endif // ALGORITHMS_HPP_INCLUDED

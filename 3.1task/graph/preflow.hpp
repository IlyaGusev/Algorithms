#ifndef PREFLOW_HPP_INCLUDED
#define PREFLOW_HPP_INCLUDED
struct PreflowNode{
    int height;
    int excess;
    list<shared_ptr<typename Graph<int, PreflowNode, PreflowEdge>::Node> > neighbours;
    shared_ptr<typename Graph<int, PreflowNode, PreflowEdge>::Node> current;
    PreflowNode() : height(), excess() {}
    PreflowNode(int h, int e) : height(h), excess(e){}
};

struct PreflowEdge{
    int flow;
    int capacity;
    PreflowEdge() : flow(), capacity() {}
    PreflowEdge(int c) : flow(), capacity(c) {}
    PreflowEdge(int f, int c) : flow(f), capacity(c) {}
};

namespace preflow{
    void push(PreflowNode* u, PreflowNode* v, PreflowEdge* uv, PreflowEdge* vu){
        //PreflowNode* u = &g[u_id];
        //PreflowNode* v = &g[v_id];
        //PreflowEdge* uv = &g.accessEdge(u_id, v_id);
        //PreflowEdge* vu = &g.accessEdge(v_id, u_id);
        int d = min(u->excess, uv->capacity - uv->flow);
        uv->flow += d;
        vu->flow = -(uv->flow);
        u->excess -= d;
        v->excess += d;
    }
    void relabel(PreflowNode* u, vector<pair<int, PreflowNode> >& outNodes, vector<pair<int, PreflowEdge> >& outEdges,
                                 vector<pair<int, PreflowNode> >& inNodes, vector<pair<int, PreflowEdge> >& inEdges){
        int minimum = outNodes.front().second.height;
        for (int i=0; i<(int)outNodes.size(); i++){
            if (outEdges[i].second.capacity-outEdges[i].second.flow>0)
                if (outNodes[i].second.height<minimum)
                    minimum = outNodes[i].second.height;
        }
        for (int i=0; i<(int)inNodes.size(); i++){
            if (inEdges[i].second.capacity-inEdges[i].second.flow<0)
                if (inNodes[i].second.height<minimum)
                    minimum = inNodes[i].second.height;
        }
        u->height = 1 + minimum;
    }
    void initialize(Graph<int, PreflowNode, PreflowEdge>& g, int source_id){
        for (auto it = g.begin(); it!=g.end(); it++){
            it->second->getValue().height = 0;
            it->second->getValue().excess = 0;
        }
        for (auto it = g.begin_edge(); it!=g.end_edge(); it++){
            it->second->getValue().flow = 0;
        }
        auto s = g[source_id];
        s.height = g.size();
        auto adjNodes = g.getOutNodes(source_id);
        auto adjEdges = g.getOutEdges(source_id);
        for (int i=0; i<(int)adjNodes.size(); i++){
            auto temp1 = g.accessEdge(source_id, adjNode[i]->getId());
            auto temp2 = g.accessEdge(adjNode[i]->getId(), source_id);
            temp1.flow = temp1.capacity;
            temp2.flow = -temp2.capacity;
            adjEdges[i]->excess = temp1.capacity;
            s.excess-=temp1.capacity;
        }
    }

    void discharge(PreflowNode* u){
        while(u->excess>0){
            a
        }
    }
}
int findMaxFlow(Graph<int, PreflowNode, PreflowEdge>& g, int source_id, int sink_id){
    preflow::initialize(g, source_id);
    list<shared_ptr<typename Graph<int, PreflowNode, PreflowEdge>::Node> > access;
    for (auto it = g.begin(); it!=g.end(); it++)
        if(it->first!=source_id && it->first!=sink_id){
            access.push_back(it->second);
            auto beg = it->second->getValue().neighbours.begin();
            auto out = g.getOutNodes(it->first);
            auto in = g.getInNodes(it->first);
            it->second->getValue().neighbours.insert(beg, out.begin(), out.end());
            it->second->getValue().neighbours.insert(beg, in.begin(), in.end());
            it->second->getValue().current = it->second->getValue().neighbours.front();
        }
    auto current = access.begin();
    while(current!=access.end()){
        int old = (*current)->getValue().height;
        discharge(current);
        if(((*current)->getValue().height)>old){
            auto temp  = *(current);
            access.erase(current);
            access.push_front(temp);
            current = ++access.begin();
        else{
            current++;
        }
    }
}

#endif // PREFLOW_HPP_INCLUDED

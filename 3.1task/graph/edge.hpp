#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED

template <class I, class N, class E>
    Graph<I, N, E>::Edge::Edge(weak_ptr<Node> f, weak_ptr<Node> s) : value(E()), nodes(make_pair(f, s)){}
template <class I, class N, class E>
    Graph<I, N, E>::Edge::Edge(weak_ptr<Node> f, weak_ptr<Node> s, E const & _value) : value(_value), nodes(make_pair(f, s)){}
template <class I, class N, class E>
    Graph<I, N, E>::Edge::Edge(weak_ptr<Node> f, weak_ptr<Node> s, E && _value): value(_value), nodes(make_pair(f, s)){}
template <class I, class N, class E>
    E Graph<I, N, E>::Edge::getValueConst() const { return value; }
template <class I, class N, class E>
    E& Graph<I, N, E>::Edge::getValue() { return value; }
template <class I, class N, class E>
    pair<I, I> Graph<I, N, E>::Edge::getNodes() const {
        return make_pair(nodes.first.lock()->id, nodes.second.lock()->id);
    }

#endif // EDGE_HPP_INCLUDED

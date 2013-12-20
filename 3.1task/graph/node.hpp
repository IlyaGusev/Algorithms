#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

template <class I, class N, class E>
    Graph<I, N, E>::Node::Node(I const& _id, N const& _value) : id(_id), value(_value),children(), parents(){}
template <class I, class N, class E>
    Graph<I, N, E>::Node::Node(I const& _id) : id(_id), value(N()),children(), parents(){}
template <class I, class N, class E>
    Graph<I, N, E>::Node::Node(I const& _id, N&& _value) : id(_id), value(_value), children(), parents(){}
template <class I, class N, class E>
    I Graph<I, N, E>::Node::getId() const {return id;}
template <class I, class N, class E>
    N Graph<I, N, E>::Node::getValueConst() const {return value;}
template <class I, class N, class E>
    N& Graph<I, N, E>::Node::getValue(){return value;}

#endif // NODE_HPP_INCLUDED

#ifndef FORWRD_LIST_H_INCLUDED
#define FORWRD_LIST_H_INCLUDED
#include <cstddef>
using std::ostream;
namespace my{
template <class T> class forward_list;
template <class T> class forward_list_iterator;
template <class T> class forward_list_const_iterator;
template <class T> ostream& operator<< (ostream&, forward_list<T> const &);

template <class T>
struct node{
private:
    node* _next;
    T _data;
public:
    node(T const __value=T()) : _next(NULL), _data(T(__value)) {};
    node(const node& copy) : _next(copy._next), _data(copy._date) {};
    node& operator=(const node& copy){
        if ((*this)==copy) return (*this);
        (*this)._next=copy._next;
        (*this)._data=copy._data;
    }
    bool operator==(const node& right){ return (_next==right._next && _data==right._data); }
    bool operator!=(const node& right){ return (_next!=right._next || _data!=right._data); }
    friend class forward_list<T>;
    friend struct forward_list_iterator<T>;
    friend struct forward_list_const_iterator<T>;
};
template <class T>
class forward_list{
private:
    node<T>* _begin;
public:
    forward_list() : _begin(NULL) {}
    forward_list(int cnt, T const __value=T());
    forward_list_const_iterator<T> begin() const;

    void push_front(const T&);
    void pop_front();
    void clear();
    bool is_empty() const;
    size_t size() const;
    friend ostream& operator<< <>(ostream&, const forward_list<T>&);

    friend struct forward_list_iterator<T>;
};
template<typename T>
struct forward_list_iterator
{
    typedef forward_list_iterator<T>      Self;
    typedef node<T>                       Node;

    typedef ptrdiff_t                     difference_type;
    typedef std::forward_iterator_tag     iterator_category;
    typedef T                             value_type;
    typedef T*                            pointer;
    typedef T&                            reference;

    Node* _node;

    forward_list_iterator() : _node() {}
    explicit forward_list_iterator(Node* __x) : _node(__x) {}

    reference operator*() const { return (_node)->_data; }
    pointer operator->() const { return &(_node->_data); }
    Self& operator++(){
        _node=_node->_next;
        return (*this);
    }
    Self operator++(int){
        Self temp=(*this);
        _node=_node->_next;
        return temp;
    }
    bool operator==(const Self& __x) const { return (_node==__x._node); }
    bool operator!=(const Self& __x) const { return (_node!=__x._node); }
};

template<typename T>
struct forward_list_const_iterator
{
    typedef forward_list_const_iterator<T>  Self;
    typedef node<T>                         Node;

    typedef ptrdiff_t                       difference_type;
    typedef std::forward_iterator_tag       iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;

    Node* _node;

    forward_list_const_iterator() : _node() {}
    explicit forward_list_const_iterator(Node* __x) : _node(__x) {}

    reference operator*() const { return (_node)->_data; }
    pointer operator->() const { return &(_node->_data); }
    Self& operator++(){
        _node=_node->_next;
        return (*this);
    }
    Self operator++(int){
        Self temp=(*this);
        _node=_node->_next;
        return temp;
    }
    bool operator==(const Self& __x) const { return (_node==__x._node); }
    bool operator!=(const Self& __x) const { return (_node!=__x._node); }
};
template<typename T>
    forward_list<T>::forward_list(int cnt, T const __value){
        _begin=NULL;
        for (int i=0; i<cnt; i++)
            push_front(T(__value));
    }
template<typename T>
    forward_list_const_iterator<T> forward_list<T>::begin() const{
        return (forward_list_const_iterator<T>(_begin));
    }
template<typename T>
    void forward_list<T>::push_front(const T& a){
        try{
            node<T>* temp=new node<T>(T(a));
            temp->_next=_begin;
            _begin=temp;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=forward_list(); }
    }
template<typename T>
    void forward_list<T>::pop_front(){
        if (_begin!=NULL){
            node<T>* temp;
            temp=_begin;
            _begin=_begin->_next;
            delete[] temp;
        }
    }
template<typename T>
    void forward_list<T>::clear(){
        size_t s=size();
        for (int i=0; i<s; i++){
            pop_front();
        }
    }
template<typename T>
    bool forward_list<T>::is_empty() const{
        if (_begin==NULL)
            return true;
        else return false;
    }
template<typename T>
    size_t forward_list<T>::size() const{
        size_t res=1;
        if (_begin==NULL) return 0;
        node<T>* current=_begin;
        while(current->_next!=NULL){
            current=current->_next;
            res++;
        }
        return res;
    }
template<typename T>
    ostream& operator<< (ostream& s, const forward_list<T>& obj){
        node<T>* current=obj._begin;
        for (int i=0; i<obj.size(); i++){
            s<<current->_data<<" ";
            current=current->_next;
        }
        return s;
    }
}

#endif // FORWRD_LIST_H_INCLUDED

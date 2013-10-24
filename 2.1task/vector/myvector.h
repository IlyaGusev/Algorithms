#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED
#include <cstdlib>
#include <cstddef>

namespace my{
template <typename T>
class vector{
private:
    char* _head;
    unsigned int _size;
    unsigned int _capacity;
public:
    struct iterator;
    struct const_iterator;

    vector();
    vector(const unsigned int, T const);
    vector(vector const &);
    virtual ~vector();

    iterator begin();
    iterator end();

    unsigned int size() const;
    unsigned int capacity() const;
    void reserve(int);
    void clear();
    bool empty() const;
    void resize(unsigned int, T const);
    void shrink_to_fit();

    void push_back(T const&);
    void pop_back();
    vector<T>& operator= (vector<T> const &);

    T& operator[] (int);
    T operator[] (int) const;
    T& front();
    T& back();

};

template <typename T>
struct vector<T>::iterator{
    typedef iterator                            Self;

    typedef ptrdiff_t                           difference_type;
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;

    pointer _ptr;
    iterator() : _ptr() {}
    explicit iterator(pointer __x) : _ptr(__x) {}

    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }
    reference operator[](int n){ return *(_ptr+n*sizeof(T)); }
    Self& operator++(){
        _ptr=_ptr+1;
        return (*this);
    }
    Self operator++(int){
        Self temp=(*this);
        _ptr=_ptr+1;
        return temp;
    }
    Self& operator--(){
        _ptr=_ptr-1;
        return (*this);
    }
    Self operator--(int){
        Self temp=(*this);
        _ptr=_ptr-sizeof(value_type);
        return temp;
    }
    Self operator+(int n){ return Self(_ptr+n); }
    Self& operator+=(int n){
        _ptr=_ptr+n;
        return (*this);
    }
    Self operator-(int n){ return Self(_ptr-n); }
    difference_type operator-(const Self& __x){ return (_ptr-__x._ptr); }
    Self& operator-=(int n){
        _ptr=_ptr-n;
        return (*this);
    }
    bool operator==(const Self& __x) const { return (_ptr==__x._ptr); }
    bool operator!=(const Self& __x) const { return (_ptr!=__x._ptr); }
    bool operator<(const Self& __x) const { return (_ptr<__x._ptr); }
    bool operator<=(const Self& __x) const { return (_ptr<=__x._ptr); }
    bool operator>(const Self& __x) const { return (_ptr>__x._ptr); }
    bool operator>=(const Self& __x) const { return (_ptr>=__x._ptr); }
};

template <typename T>
struct vector<T>::const_iterator{
    typedef const_iterator                          Self;

    typedef ptrdiff_t                               difference_type;
    typedef std::random_access_iterator_tag         iterator_category;
    typedef const T                                 value_type;
    typedef T*                                      pointer;
    typedef const T&                                reference;

    pointer _ptr;
    const_iterator() : _ptr() {}
    explicit const_iterator(pointer __x) : _ptr(__x) {}

    reference operator*() const { return *_ptr; }
    const pointer operator->() const { return _ptr; }
    reference operator[](int n) { return *(_ptr+n*sizeof(T)); }
    Self& operator++(){
        _ptr=_ptr+1;
        return (*this);
    }
    Self operator++(int){
        Self temp=(*this);
        _ptr=_ptr+1;
        return temp;
    }
    Self& operator--(){
        _ptr=_ptr-1;
        return (*this);
    }
    Self operator--(int){
        Self temp=(*this);
        _ptr=_ptr-sizeof(value_type);
        return temp;
    }
    Self operator+(int n){ return Self(_ptr+n); }
    Self& operator+=(int n){
        _ptr=_ptr+n;
        return (*this);
    }
    Self operator-(int n){ return Self(_ptr-n); }
    difference_type operator-(const Self& __x){ return (_ptr-__x._ptr); }
    Self& operator-=(int n){
        _ptr=_ptr-n;
        return (*this);
    }
    bool operator==(const Self& __x) const { return (_ptr==__x._ptr); }
    bool operator!=(const Self& __x) const { return (_ptr!=__x._ptr); }
    bool operator<(const Self& __x) const { return (_ptr<__x._ptr); }
    bool operator<=(const Self& __x) const { return (_ptr<=__x._ptr); }
    bool operator>(const Self& __x) const { return (_ptr>__x._ptr); }
    bool operator>=(const Self& __x) const { return (_ptr>=__x._ptr); }
};

    ///Con-ors & Des-ors
template <class T>
    vector <T>::vector(vector const & v){
        try{
            _head = new char[sizeof(T)*v._capacity];
            for (int i=0; i<v._size; i++)
                new(_head+i*sizeof(T)) T(*((T*)(v._head+i*sizeof(T))));
            _capacity=v._capacity;
            _size= v._size;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); } //Normal
    }

template <typename T>
    vector <T>::vector(){
        try{
            _head=new char[sizeof(T)*1];
            _size=0;
            _capacity=1;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; throw; } //Really bad
    }

template <typename T>
    vector <T>::vector(const unsigned int n, T const __value=T()){
        try{
            _head=new char[sizeof(T)*n];
            _size=n;
            _capacity=n;
            if (n==0)
                _capacity=1;
            for (int i=0; i<n; i++)
                new(_head+i*sizeof(T)) T(__value);
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector();}
    }

template <typename T>
    vector <T>::~vector(){
        for (int i=0; i<_size; i++)
            ((T*)(_head+i*sizeof(T)))->~T();
        delete [] _head;
    }

    ///Iterators
template <typename T>
    typename vector<T>::iterator vector<T>::begin(){
        return typename vector<T>::iterator(reinterpret_cast<T*>(_head));
    }

template <typename T>
    typename vector<T>::iterator vector<T>::end(){
        return typename vector<T>::iterator(reinterpret_cast<T*>(_head+(_size)*sizeof(T)));
    }

    ///Capacity
template <typename T>
    unsigned int vector <T>::size() const{ return _size; }

template <typename T>
    unsigned int vector <T>::capacity() const{ return _capacity; }

template <typename T>
    void vector <T>::reserve(int __capacity){
            try{
                if (__capacity>_capacity){
                    char* temp=_head;
                    _head=new char[sizeof(T)*__capacity];
                    for (int i=0; i<_size; i++)
                        new(_head+i*sizeof(T)) T(*((T*)(temp+i*sizeof(T))));
                    for (int i=0; i<_size; i++)
                        ((T*)(temp+i*sizeof(T)))->~T();
                    delete [] temp;
                    _capacity=__capacity;
                }
            }
            catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); }
        }

template <typename T>
    void vector <T>::clear(){
            for (int i=0; i<_size; i++)
                ((T*)(_head+i*sizeof(T)))->~T();
            _size=0;
        }

template <typename T>
    bool vector <T>::empty() const{
        if (_size==0) return 1;
        else return 0;
    }

template <typename T>
    void vector <T>::resize(unsigned int __size, T const __value=T()){
        try{
            if (__size>_size){
                reserve(__size);
                for (int i=_size; i<__size; i++)
                    new(_head+i*sizeof(T)) T(__value);
                _size=__size;
            }
            if (__size<_size){
                for (int i=__size; i<_size; i++)
                    ((T*)(_head+i*sizeof(T)))->~T();
                _size=__size;
            }
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); }
    }

template <typename T>
    void vector <T>::shrink_to_fit(){
        try{
            if (_capacity>_size){
                char* temp=_head;
                _head=new char[sizeof(T)*_size];
                for (int i=0; i<_size; i++)
                    new(_head+i*sizeof(T)) T(*((T*)(temp+i*sizeof(T))));
                for (int i=0; i<_size; i++)
                    ((T*)(temp+i*sizeof(T)))->~T();
                delete [] temp;
                _capacity=_size;
            }
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); }
    }

    ///Modifires
template <typename T>
    void vector <T>::push_back(T const& x){
        try{
            if (_size<_capacity){
                new(_head+(_size++)*sizeof(T)) T(x);
            }
            else {
                reserve(_capacity*2);
                new(_head+(_size++)*sizeof(T)) T(x);
            }
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); }
    }

template <typename T>
    void vector <T>::pop_back(){
        if (_size>0){
            ((T*)(_head+(_size-1)*sizeof(T)))->~T();
            _size-=1;
        }
    }

template <typename T>
    vector<T>& vector <T>::operator= (vector<T> const & v){
        try{
            _head = new char [sizeof(T)*v._capacity];
            for (int i=0; i<v._size; i++)
                new(_head+i*sizeof(T)) T(*((T*)(v._head+i*sizeof(T))));
            _capacity=v._capacity;
            _size= v._size;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; (*this)=vector(); }
        return *this;
    }

    ///Element access
template <typename T>
    T& vector <T>::operator[] (int index){
        if (index>=0 && index<_size)
            return *((T*)(_head+index*sizeof(T)));
        return front();
    }

template <typename T>
    T vector <T>::operator[] (int index) const{
        if (index>=0 && index<_size)
            return *((T*)(_head+index*sizeof(T)));
        return T();
    }

template <typename T>
    T& vector <T>::back(){
        if (!empty())
            return *((T*)(_head+(_size-1)*sizeof(T)));
    }

template <typename T>
    T& vector<T>::front(){
        if (!empty())
            return *((T*)(_head));
    }
}


#endif // MYVECTOR_H_INCLUDED

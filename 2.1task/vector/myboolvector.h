#ifndef MYBOOLVECTOR_H_INCLUDED
#define MYBOOLVECTOR_H_INCLUDED
#include <cstdlib>
#include <cstddef>
namespace my{
template<> class vector<bool>;
struct bit
{
    char* _bite_ptr;
    unsigned char _mask;
    bit(char* __bite_ptr, unsigned char __mask) : _bite_ptr(__bite_ptr), _mask(__mask) {}
    bit(const bit & __bit): _bite_ptr(__bit._bite_ptr), _mask(__bit._mask) {}
    bit(): _bite_ptr(0), _mask(0) {}
    operator bool() const{ return (!!(*_bite_ptr&_mask)); }
    bit& operator=(bool __bool){
        if (__bool)
            *_bite_ptr|=_mask;
        else
            *_bite_ptr&= ~_mask;
        return *this;
    }
    bit& operator=(const bit & __bit){ return ((*this)=bool(__bit)); }
    bit& operator++(){ return ((*this)=bool(1)); }
    const bit operator++(int n){
        bit temp=*this;
        ++(*this);
        return temp;
    }
    bool operator!() const{ return !(bool(*this)); }
    bool operator==(const bit & __bit) const{ return (bool(*this)==bool(__bit)); }
    bool operator>(const bit & __bit) const{ return (bool(*this)>bool(__bit)); }
    bool operator<=(const bit & __bit) const{ return !(bool(*this)>bool(__bit)); }
    bool operator>=(const bit & __bit) const{ return !(bool(*this)<bool(__bit)); }
    bool operator<(const bit & __bit) const{ return (bool(*this)<bool(__bit)); }
    bool operator!=(const bit & __bit) const{ return !(bool(*this)==bool(__bit)); }
};
template<>
class vector<bool>
{
private:
    char* _head;
    unsigned int _size;
    unsigned int _capacity;
    static unsigned char mask(bool value, int index){
        unsigned char ch_value;
        if (value)
            ch_value=1;
        else
            ch_value=0;
        return (ch_value<<(7-(index-(index/8)*8)));
    }

public:
    struct iterator{
        typedef iterator                            Self;

        typedef int                                 difference_type;
        typedef std::random_access_iterator_tag     iterator_category;
        typedef bool                                value_type;
        typedef bit                                 pointer;
        typedef bit                                 reference;

        pointer _ptr;
        iterator() : _ptr() {}
        explicit iterator(pointer __x) : _ptr(__x) {}
        Self& operator=(const Self& __x){
            _ptr=__x._ptr;
            return (*this);
        }
        iterator(const Self& __x) : _ptr(__x._ptr) {}
        reference operator*() const { return _ptr; }
        pointer operator->() const { return _ptr; }
        reference operator[](int n){
            bit temp=_ptr;
            while(n>7){
                temp._bite_ptr++;
                n-=8;
            }
            temp._mask=mask(1, n);
            return temp;
        }
        Self& operator++(){
            _ptr._mask=(_ptr._mask>>1);
            if (_ptr._mask==0){
                _ptr._bite_ptr++;
                _ptr._mask=mask(1,0);
            }
            return (*this);
        }
        Self operator++(int){
            Self temp=(*this);
            ++(*this);
            return temp;
        }
        Self& operator--(){
            _ptr._mask=(_ptr._mask<<1);
            if (_ptr._mask==0){
                _ptr._bite_ptr--;
                _ptr._mask=mask(1,7);
            }
            return (*this);
        }
        Self operator--(int){
            Self temp=(*this);
            --(*this);
            return temp;
        }
        Self operator+(int n){
            bit temp=_ptr;
            while(n>7){
                temp._bite_ptr++;
                n-=8;
            }
            temp._mask=mask(1, n);
            return Self(temp);
        }
        Self& operator+=(int n){
            (*this)=(*this)+n;
            return (*this);
        }
        Self operator-(int n){
            bit temp=_ptr;
            while(n>7){
                temp._bite_ptr--;
                n-=8;
            }
            temp._mask=mask(1, 7-n);
            return Self(temp);
        }
        Self& operator-=(int n){
            (*this)=(*this)-n;
            return (*this);
        }
        difference_type operator-(const Self& __x){
            int res=0;
            Self tx(__x);
            Self tt(*this);
            std::cout<<(*tx)<<" "<<(*tt)<<std::endl;
            if (__x>=(*this))
                while (tx>tt){
                    res++;
                    tt++;
                }
            else {
                while (tt>tx){
                    res++;
                    tx++;
                }
            }
            return res;
        }
        bool operator==(const Self& __x) const { return (_ptr._bite_ptr==__x._ptr._bite_ptr && _ptr._mask==__x._ptr._mask); }
        bool operator!=(const Self& __x) const { return !((*this)==(__x)); }
        bool operator<(const Self& __x) const {
            if (_ptr._bite_ptr<__x._ptr._bite_ptr)
            return true;
            if (_ptr._bite_ptr>__x._ptr._bite_ptr)
                return false;
            if (_ptr._bite_ptr==__x._ptr._bite_ptr)
                return (_ptr._mask>__x._ptr._mask);
        }
        bool operator<=(const Self& __x) const { return ((*this)==(__x) || (*this)<(__x)); }
        bool operator>(const Self& __x) const {
            if (_ptr._bite_ptr>__x._ptr._bite_ptr)
            return true;
            if (_ptr._bite_ptr<__x._ptr._bite_ptr)
                return false;
            if (_ptr._bite_ptr==__x._ptr._bite_ptr)
                return (_ptr._mask<__x._ptr._mask);
        }
        bool operator>=(const Self& __x) const { return ((*this)==(__x) || (*this)>(__x)); }
    };
    //Con-ors & Des-ors
    vector(vector const & copy): _head(copy._head), _size(copy._size), _capacity(copy._capacity){};
    vector(){
        try{
            _head=new char[sizeof(char)*1];
            _size=0;
            _capacity=1;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; }
    };
    vector(const unsigned int n){
        try{
            _head=new char[sizeof(char)*(n/8)+sizeof(char)];
            _size=n;
            _capacity=n;
            if (n==0)
                _capacity=1;
            for (int i=0; i<n/8+1; i++)
                *(_head+i*sizeof(char))=0;
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; }
    };
    ~vector(){ delete _head; }
    //Capacity
    unsigned int size() const{ return _size; }
    unsigned int capacity() const{ return _capacity; }
    bool empty() const{
        if (_size==0) return 1;
        else return 0;
    }
    void reserve(int __capacity){
        try{
            if (__capacity>_capacity){
                char* temp=_head;
                _head=new char[sizeof(char)*(__capacity/8)+sizeof(char)];
                for (int i=0; i<_size/8+1; i++)
                    _head[i]=temp[i];
                delete temp;
                _capacity=__capacity;
            }
        }
        catch (std::bad_alloc const & ba){ std::cout<<ba.what()<<std::endl; }
    }
    void clear(){
        for (int i=0; i<_size/8+1; i++)
            *(_head+i)=0;
        _size=0;
    }
    void resize(unsigned int __size){
        if (__size>_size){
            reserve(__size);
            for (int i=_size/8+1; i<__size/8+1; i++)
                *(_head+i)=0;
            _size=__size;
        }
        if (__size<_size){
            for (int i=__size/8+1; i<_size/8+1; i++)
                *(_head+i)=0;
            for (int i=__size-__size/8*8; i<8; i++)
                *(_head+__size/8)=*(_head+__size/8)&~mask(1,__size/8*8+i);
            _size=__size;
        }
    }
    //Modifires
    void push_back(bool value){
        if (_size<_capacity) {
            *(_head+_size/8)=*(_head+_size/8)|mask(value,_size);
            ++_size;
        }
        else {
            reserve(_capacity*2);
            *(_head+_size/8)=*(_head+_size/8)|mask(value,_size);
            ++_size;
        }
    }
    void pop_back(){
        *(_head+_size/8)=*(_head+_size/8)&~mask(1,_size-1);
        _size-=1;
    }
    //Element access
    bit operator[] (int index){
        bit _bit(_head+index/8, mask(1, index));
        return _bit;
    }
    bool operator[] (int index) const{
        if (index>=0 && index<_size)
            if (*(_head+index/8)&mask(1,index))
                return 1;
            else return 0;
    }

    // Iterator access

    iterator begin(){
        return (iterator(bit(_head, mask(1, 0))));
    }

    iterator end(){
        return (iterator(bit(_head+_size/8, mask(1, _size))));
    }

};
}


#endif // MYBOOLVECTOR_H_INCLUDED

#include <iostream>
#include <stdexcept>
namespace my{
    template <class T>
    class unique_ptr{
    public:
        typedef unique_ptr<T> self;
        typedef T* pointer;
        typedef T value_type;

        explicit unique_ptr(pointer ptr) : imp(ptr) {}
        explicit unique_ptr(const unique_ptr& other) noexcept{}
        explicit unique_ptr(unique_ptr&& other) noexcept;
        ~unique_ptr(){ if (imp!=nullptr) {delete imp; imp=nullptr;} }

        value_type& operator*() const;
        pointer get() const noexcept                {return imp;}
        pointer operator->() const noexcept         {return imp;}
        explicit operator bool() const noexcept     {return (imp!=nullptr);}
        void swap (unique_ptr& x) noexcept;
        unique_ptr& operator= (unique_ptr&&) noexcept;

        pointer release() noexcept;
        void reset(pointer=nullptr) noexcept;
    private:
        pointer imp;
    };
    template<class T>
        T& unique_ptr<T>::operator*() const{
            if (imp!=nullptr) return (*imp);
            else throw std::logic_error("Dereference of nullptr.");
        }
    template<class T>
        T* unique_ptr<T>::release() noexcept{
            pointer temp = imp;
            if (imp!=nullptr) {
                imp=nullptr;
            }
            return temp;
        }
    template<class T>
        void unique_ptr<T>::reset(pointer ptr) noexcept{
            if (imp!=nullptr) {
                delete imp;
                imp=ptr;
            }
        }
    template<class T>
        unique_ptr<T>::unique_ptr(unique_ptr&& other) noexcept{
            imp=other.imp;
            other.imp=nullptr;
        }
    template<class T>
        unique_ptr<T>& unique_ptr<T>::operator= (unique_ptr&& other) noexcept{
            imp=other.imp;
            other.imp=nullptr;
            return (*this);
        }
    template<class T>
        void unique_ptr<T>::swap (unique_ptr& other) noexcept{
            pointer temp = other.imp;
            other.imp = imp;
            imp = temp;
        }
}
class A{
    public:
    A(){};
    ~A(){std::cout<<"DDDD"<<std::endl;}
};
int main(){
   // int* m = new int(5);
   // my::unique_ptr<int> p(m);
   // p.reset();
   // std::cout<<(*p);
   my::unique_ptr<A> p (new A());
}

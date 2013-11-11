#include <iostream>
#include "fibheap.h"
using namespace std;

int main(){
    FibHeap<int> heap;
    heap.insert(4);
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    heap.insert(1);
    heap.insert(2);
    heap.insert(9);
    heap.insert(10);
    heap.insert(15);
    heap.insert(20);
    heap.insert(17);
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    /*heap.decrease_key(heap.minimum(), 1);
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;
    cout<<"e: "<<heap.extract_minimum()->first()<<endl;
    heap.print(); cout<<endl;*/
}

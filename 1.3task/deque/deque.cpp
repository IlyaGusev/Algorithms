#include <iostream>
#include "deque.h"
using namespace std;

int main()
{
    deque a;
    char cControl;
    int elem;
    cout<<"push_back=1, push_front=2, pop_back=3, pop_front=4, display head and tail=5"<<endl
    <<"clear=6, size=7, display_all=8, reverse=9."<<endl;
    while(1)
    {
        cin>>cControl;
        switch (cControl)
        {
            case '1':
                cout<<"Enter an element: ";
                cin>>elem;
                a.push_back(elem);
                break;
            case '2':
                cout<<"Enter an element: ";
                cin>>elem;
                a.push_front(elem);
                break;
            case '3':
                if (!a.is_empty())
                    a.pop_back();
                break;
            case '4':
                if (!a.is_empty())
                    a.pop_front();
                break;
            case '5':
                if (!a.is_empty())
                    cout<<"Deck tail and head: "<<a.back()<<" "<<a.front()<<endl;
                else cout<<"Deque is empty."<<endl;
                break;
            case '6':
                a.clear();
                break;
            case '7':
                cout<<"Size: "<<a.size()<<endl;
                break;
            case '8':
                cout<<"Elements: ";
                a.display_all();
                break;
            case '9':
                a.reverse();
                cout<<"Elements: ";
                a.display_all();
                break;
            default:
                cout<<"Sorry, wrong command. Try again."<<endl;
                break;
        }
    }
    return 0;
}

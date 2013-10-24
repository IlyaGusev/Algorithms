#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED
#include <iostream>
struct deque
{
private:
    struct node
    {
        node * next;
        node * prev;
        int value;
    };
    node *begin;
    node *end;
public:
    deque();
    void push_back(int);
    void push_front(int);
    int back();
    int front();
    void pop_back();
    void pop_front();
    void clear();
    bool is_empty();
    size_t size();
    void display_all();
    void reverse();
};

deque::deque()
{
    begin=NULL;
    end=NULL;
}
void deque::push_back(int elem)
{
    node *temp;
    temp=begin;
    begin=new node;
    if (temp!=NULL)
        temp->prev=begin;
    begin->next=temp;
    begin->prev=NULL;
    begin->value=elem;
    if (end==NULL)
        end=begin;
}
void deque::push_front(int elem)
{
    node *temp;
    temp=end;
    end=new node;
    if (temp!=NULL)
        temp->next=end;
    end->prev=temp;
    end->next=NULL;
    end->value=elem;
    if (begin==NULL)
        begin=end;

}
int deque::back()
{
    return (begin->value);
}
int deque::front()
{
    return (end->value);
}
void deque::pop_back()
{
    node *temp;
    temp=begin;
    begin=begin->next;
    delete (temp);
    temp=NULL;
    if (begin==NULL)
        end=NULL;
}
void deque::pop_front()
{
    node *temp;
    temp=end;
    end=end->prev;
    delete (temp);
    temp=NULL;
    if (end==NULL)
        begin=NULL;
}
void deque::clear()
{
    node *temp;
    while (begin!=NULL)
    {
        temp=begin;
        begin=begin->next;
        delete (temp);
    }
    end=begin;
}
bool deque::is_empty()
{
    if (begin==NULL || end==NULL) return 1;
    else return 0;
}
size_t deque::size()
{
    size_t s=0;
    node *temp;
    temp=begin;
    while(temp!=NULL)
    {
        temp=temp->next;
        s++;
    }
    return s;
}

void deque::display_all()
{
    if (!(is_empty()))
    {
        node* flag=begin;
        while(flag!=NULL)
        {
            std::cout<<flag->value<<" ";
            flag=flag->next;
        }
        std::cout<<std::endl;
    }
    else std::cout<<"Deque is empty.";
}

void deque::reverse()
{
    if (!(is_empty()))
    {
        node* flag=begin;
        node* temp;
        while(flag!=NULL)
        {
            temp=flag->next;
            flag->next=flag->prev;
            flag->prev=temp;
            flag=flag->prev;
        }
        temp=begin;
        begin=end;
        end=temp;
    }
    else std::cout<<"Deque is empty.";
}
#endif // DEQUE_H_INCLUDED

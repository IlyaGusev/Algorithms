#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct Stack
{
    struct Node
    {
        Node* prev;
        char* value;
    };
    Node * last;
    Stack();
    void add(char*);
    char* pop();
    void display();
    bool is_empty();
};
Stack::Stack()
{
    last=NULL;
}
bool Stack::is_empty()
{
    if (last==NULL) return 1;
    else return 0;
}
void Stack::add(char* oper)
{
    Node* node=(Node*)malloc(sizeof(Node*));
    node->prev=last;
    node->value=oper;
    last=node;
}
char* Stack::pop()
{
    if (last!=NULL)
    {
        Node* temp=last;
        last=last->prev;
        char* str=(char*)malloc(strlen(temp->value)*sizeof(char));
        for(int i=0; i<strlen(temp->value); i++)
        {
            str[i]=temp->value[i];
        }
        str[strlen(temp->value)]='\0';
        free(temp->value);
        free(temp);
        return str;
    }
    else return 0;
}
void Stack::display()
{
    Node * temp=last;
    while(temp!=NULL)
    {
        cout<<temp->value<<" ";
        temp=temp->prev;
    }
    cout<<endl;
}
int main()
{
    Stack stack;
    char str[1000];
    char out[1000];
    cin>>str;
    int count=0;
    for (int i=0; i<strlen(str);i++)
    {
        if (str[i]>='0' && str[i]<='9')
        {
            if (str[i+1]>='0' && str[i+1]<='9')
            {
                out[count]=str[i];
                count++;
            }
            else
            {
                out[count]=str[i];
                out[count+1]=' ';
                count+=2;
            }
        }else
        if (str[i]=='+' || str[i]=='-')
        {
            if (!stack.is_empty())
            if(stack.last->value[0]=='*' || stack.last->value[0]=='/' || stack.last->value[0]=='-'
               || stack.last->value[0]=='+')
            {
                char*temp=stack.pop();
                for (int i=0; i<strlen(temp); i++)
                {
                    out[count]=temp[i];
                    count++;
                }
                free(temp);
                out[count++]=' ';
            }
            char* temp=(char*)malloc(2*sizeof(char));
            temp[0]=str[i];
            temp[1]='\0';
            stack.add(temp);
        }else
        if (str[i]=='*' || str[i]=='/')
        {
            if (!stack.is_empty())
            if(stack.last->value[0]=='*' || stack.last->value[0]=='/')
            {
                char*temp=stack.pop();
                for (int i=0; i<strlen(temp); i++)
                {
                    out[count]=temp[i];
                    count++;
                }
                free(temp);
                out[count++]=' ';
            }
            char* temp=(char*)malloc(2*sizeof(char));
            temp[0]=str[i];
            temp[1]='\0';
            stack.add(temp);
        }else
        if (str[i]=='(')
        {
            char* temp=(char*)malloc(2*sizeof(char));
            temp[0]=str[i];
            temp[1]='\0';
            stack.add(temp);
        }else
        if (str[i]==')')
        {
            while(stack.last->value[0]!='(')
            {
                char*temp=stack.pop();
                for (int i=0; i<strlen(temp); i++)
                {
                    out[count]=temp[i];
                    count++;
                }
                free(temp);
                out[count++]=' ';
            }
            char*temp=stack.pop();
            free(temp);
            if  (!stack.is_empty())
            if (stack.last->value[0]=='+' || stack.last->value[0]=='-')
            {
                char*temp=stack.pop();
                for (int i=0; i<strlen(temp); i++)
                {
                    out[count]=temp[i];
                    count++;
                }
                free(temp);
                out[count++]=' ';
            }
        }
    }
    while(!stack.is_empty())
    {
        char*temp=stack.pop();
        for (int i=0; i<strlen(temp); i++)
        {
            out[count]=temp[i];
            count++;
        }
        free(temp);
        out[count++]=' ';
    }
    out[count]='\0';
    cout<<out;
}

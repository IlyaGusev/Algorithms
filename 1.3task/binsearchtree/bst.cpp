#include <iostream>
#include <stdlib.h>
using namespace std;
struct bstree
{
    struct node
    {
        int value;
        node * left;
        node * right;
    };
    node * root;
    bstree();
    void add(int);
    void show_in_order(node*);
    bstree::node* search(int key);
    bstree::node* min();
    bstree::node* max();
};
bstree::bstree()
{
    root=NULL;
}
void bstree::add(int n)
{
    node* elem=(node*)malloc(sizeof(node));
    elem->value=n;
    elem->left=NULL;
    elem->right=NULL;
    node* buffer=NULL;
    node* var=root;
    while(var!=NULL)
    {
        buffer=var;
        if (elem->value<var->value)
            var=var->left;
        else
            var=var->right;
    }
    if (buffer==NULL)
        root=elem;
    else
        if(elem->value<buffer->value)
            buffer->left=elem;
        else buffer->right=elem;
}
void bstree::show_in_order(node * var)
{
    if (var!=NULL)
    {
        show_in_order(var->left);
        cout<<var->value<<" ";
        show_in_order(var->right);
    }
}

bstree::node* bstree::search(int key)
{
    node *var=root;
    while(1)
    {
        if (var==NULL || var->value==key)
            return (var);
        if (key<var->value)
            var=var->left;
        else
            var=var->right;
    }
}

bstree::node* bstree::min()
{
    node * var=root;
    while(var->left!=NULL)
        var=var->left;
    return var;
}

bstree::node* bstree::max()
{
    node * var=root;
    while(var->right!=NULL)
        var=var->right;
    return var;
}

int main()
{
    bstree bst;
    bst.add(5);
    bst.add(6);
    bst.add(3);
    bst.add(4);
    bst.add(11);
    cout<<bst.min()->value<<" "<<bst.max()->value;
}

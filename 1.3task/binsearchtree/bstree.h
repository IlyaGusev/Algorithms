#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED

    struct bstree
    {
        struct node
        {
            int value;
            node * left;
            node * right;
        };
        node * root;
    };
    bstree::bstree()
    {
        root=NULL;
    }
    void bstree::add(int n)
    {
        node* elem=(elem*)malloc(sizeof(elem))
    }

#endif // BSTREE_H_INCLUDED

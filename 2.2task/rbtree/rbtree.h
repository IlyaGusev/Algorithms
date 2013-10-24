#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template <class T>
class RBtree{
private:
    struct Node{
        bool color;
        T key;
        Node* left;
        Node* right;
        Node* parent;

        Node() : color(0), key(T()), left(&nil), right(&nil), parent(&nil) {}
        Node(T input) : color(0), key(T(input)), left(&nil), right(&nil), parent(&nil) {}
        bool operator==(const Node* rhs)
            { return (key==rhs->key && left==rhs->left && right==rhs->right && parent==rhs->parent); }
        bool operator!=(const Node* rhs) { return !((*this)==rhs); }
    };
    Node* root;
    void left_rotate(Node *);
    void right_rotate(Node *);
    void insert_fixup(Node *);
    void remove_fixup(Node *);
public:
    static Node nil;
    RBtree() : root(&nil) {}
    Node* getRoot() const { return root; }
    void insert(T);
    void remove(Node*);
    Node* max(Node*);
    Node* min(Node*);
    Node* next(Node*);
    Node* prev(Node*);
    void show(Node*) const;
};

template <class T>
    typename RBtree<T>::Node RBtree<T>::nil=typename RBtree<T>::Node::Node();

template <class T>
    void RBtree<T>::left_rotate(Node* x){
        Node* y=x->right;
        x->right=y->left;

        if (y->left!=&nil)
            y->left->parent=x;

        y->parent=x->parent;
        if (x->parent==&nil)
            root=y;
        else
            if (x==x->parent->left)
                y->parent->left=y;
            else
                y->parent->right=y;

        y->left=x;
        x->parent=y;
    }
template <class T>
    void RBtree<T>::right_rotate(Node* x){
        Node* y=x->left;
        x->left=y->right;

        if (y->right!=&nil)
            y->right->parent=x;

        y->parent=x->parent;
        if (x->parent==&nil)
            root=y;
        else
            if (x==x->parent->left)
                y->parent->left=y;
            else
                y->parent->right=y;

        y->right=x;
        x->parent=y;
    }
template <class T>
    void RBtree<T>::insert_fixup(Node * z){
        while (z->parent->color==1)
            if (z->parent==z->parent->parent->left){
                Node* y=z->parent->parent->right;
                if (y->color==1){
                    z->parent->color=0;
                    y->color=0;
                    z->parent->parent->color=1;
                    z=z->parent->parent;
                }
                else {
                    if (z==z->parent->right){
                        z=z->parent;
                        left_rotate(z);
                    }
                    z->parent->color=0;
                    z->parent->parent->color=1;
                    right_rotate(z->parent->parent);
                }
            }
            else {
                Node* y=z->parent->parent->left;
                if (y->color==1){
                    z->parent->color=0;
                    y->color=0;
                    z->parent->parent->color=1;
                    z=z->parent->parent;
                }
                else {
                    if (z==z->parent->left){
                        z=z->parent;
                        right_rotate(z);
                    }
                    z->parent->color=0;
                    z->parent->parent->color=1;
                    left_rotate(z->parent->parent);
                }
            }
        root->color=0;
    }
template <class T>
    void RBtree<T>::insert(T input){
        Node* z=new Node(input);
        Node* y=&nil;
        Node* x=root;
        while (x!=&nil){
            y=x;
            if (z->key < x->key)
                x=x->left;
            else
                x=x->right;
        }
        z->parent=y;
        if (y==&nil)
            root=z;
        else
            if (z->key < y->key)
                y->left=z;
            else
                y->right=z;
        z->left=&nil;
        z->right=&nil;
        z->color=1;
        insert_fixup(z);
    }

template <class T>
    void RBtree<T>::show(Node * x) const{
        if (x!=&nil){
            show(x->left);
            cout<<x->key<<" "<<x->color<<endl;
            show(x->right);
        }
    }
template <class T>
    typename RBtree<T>::Node* RBtree<T>::min(Node* x){
        while(x->left!=&nil)
            x=x->left;
        return x;
    }
template <class T>
    typename RBtree<T>::Node* RBtree<T>::max(Node* x){
        while(x->right!=&nil)
            x=x->right;
        return x;
    }
template <class T>
    typename RBtree<T>::Node* RBtree<T>::next(Node* x){
        if (x->right!=&nil)
            return min(x->right);
        Node* y=x->parent;
        while(y!=&nil && x==y->right){
            x=y;
            y=y->parent;
        }
        return y;
    }
template <class T>
    typename RBtree<T>::Node* RBtree<T>::prev(Node* x){
        if (x->left!=&nil)
            return max(x->right);
        Node* y=x->parent;
        while(y!=&nil && x==y->left){
            x=y;
            y=y->parent;
        }
        return y;
    }

template <class T>
    void RBtree<T>::remove_fixup(Node * x){
        while (x!=root && x->color==0){
            if (x==x->parent->left){
                Node* w=x->parent->right;
                if (w->color==1){
                    w->color=0;
                    x->parent->color=1;
                    left_rotate(x->parent);
                    w=x->parent->right;
                }
                if (w->left->color==0 && w->right->color==0){
                    w->color=1;
                    x=x->parent;
                }
                else{
                    if (w->right->color==0){
                        w->left->color=0;
                        w->color=1;
                        right_rotate(w);
                        w=x->parent->right;
                    }
                    w->color=x->parent->color;
                    x->parent->color=0;
                    w->right->color=0;
                    left_rotate(x->parent);
                    x=root;
                }
            }
            else{
                Node* w=x->parent->left;
                if (w->color==1){
                    w->color=0;
                    x->parent->color=1;
                    right_rotate(x->parent);
                    w=x->parent->left;
                }
                if (w->right->color==0 && w->left->color==0){
                    w->color=1;
                    x=x->parent;
                }
                else{
                    if (w->left->color==0){
                        w->right->color=0;
                        w->color=1;
                        left_rotate(w);
                        w=x->parent->left;
                    }
                    w->color=x->parent->color;
                    x->parent->color=0;
                    w->left->color=0;
                    right_rotate(x->parent);
                    x=root;
                }
            }
        }
        x->color=0;
    }

template <class T>
    void RBtree<T>::remove(Node* z){
        Node* y;
        Node* x;
        if (z->left==&nil || z->right==&nil)
            y=z;
        else
            y=next(z);
        if (y->left!=&nil)
            x=y->left;
        else
            x=y->right;
        x->parent=y->parent;
        if (y->parent==&nil)
            root=x;
        else
            if (y==y->parent->left)
                y->parent->left=x;
            else
                y->parent->right=x;
        if (y!=z)
            z->key=y->key;
        if (y->color==0)
            remove_fixup(x);
        delete y;
    }
#endif // RBTREE_H_INCLUDED

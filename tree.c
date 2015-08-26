#include<stdlib.h>
#include<string.h>
#include "tree.h"

typedef struct tree
{
    int key;
    int value;
    int count;
    struct tree *left;
    struct tree *right;
}tree;

static tree *root=NULL;

int i1=0;

tree* makeNode(int key,int value)
{
    tree *t=(tree *)malloc(sizeof(tree));
    t->key=key;
    t->value=value;
    t->count=1;
    t->left=NULL;
    t->right=NULL;

    return t;
}

static tree* putNode(tree* x,int key,int value)
{
    if(x==NULL)
        x=makeNode(key,value);

    else if(key < x->key)
    {
        x->left=putNode(x->left,key,value);
        x->count+=1;
    }

    else if(key > x->key)
    {
        x->right=putNode(x->right,key,value);
        x->count+=1;
    }

    else
        x->value=value;

    return x;
}

void put(int key,int value)
{
    root=putNode(root,key,value);
}


static int getNode(tree *x,int key)
{
    int v=-1;

    if(x==NULL)
        return -1;

    else if(key < x->key)
        v=getNode(x->left,key);

    else if(key > x->key)
        v=getNode(x->right,key);

    else
        return x->value;

    return v;
}

int get(int key)
{
    return getNode(root,key);
}

int size(tree *x)
{
    if(x==NULL)
        return 0;

    return x->count;
}
int getRank(tree *x,int key)
{
    if(x == NULL)
        return 0;

    if(x->key == key)
        return size(x->left);

    else if(key <x->key)
        return getRank(x->left,key);

    else
        return 1 + size(x->left) + getRank(x->right,key);
}
int rank(int key)
{
    return getRank(root,key);
}

static int getMin(tree *r)
{
    int v;

    if(r->left==NULL)
        return r->key;
    else
        v=getMin(r->left);

    return v;
}

static int getMax(tree *r)
{
    int v;

    if(r->right==NULL)
        return r->key;
    else
        v=getMax(r->right);

    return v;
}
int Min()
{
    return getMin(root);
}

int Max()
{
    return getMax(root);
}

void getdelMax(tree *r)
{
    if(r==root)
        {
            if(r->right==NULL)
            {
                root=r->left;
                return ;
            }
        }

    if(r->right->right==NULL)
        r->right=NULL;
    else
        getdelMax(r->right);
}

void getdelMin(tree *r)
{

    if(r==root)
    {
        if(r->left==NULL)
        {
            root=r->right;
            return ;
        }
    }

    if(r->left->left==NULL)
       r->left=NULL;

    else
        getdelMin(r->left);
}
void delMax()
{
    getdelMax(root);
}

void delMin()
{
    getdelMin(root);
}

tree* findNode(tree *x,int key)
{
    tree* v=NULL;

    if(x==NULL)
        return v;

    else if(key==x->key)
        v=x;

    else if(key < x->key)
        v=findNode(x->left,key);

    else if(key > x->key)
        v=findNode(x->right,key);

     return v;

}
tree* findPNode(tree *x,int key)
{
    tree *v=NULL;

    if(root->key == key)
        return NULL;

    if(x->left->key == key || x->right->key==key)
        v=x;

    else if(key < x->key)
        v=findPNode(x->left,key);

    else if(key > x->key)
        v=findPNode(x->right,key);

    return v;
}
int findfloor(tree* r)
{
    int v=-1;

    if(r->right==NULL)
        v= r->key;
    else
        findfloor(r->right);

    return v;
}

int findceil(tree *r)
{
    int v=-1;

    if(r->left==NULL)
        v=r->key;
    else
        findceil(r->left);

    return v;
}

int flooring(int key)
{
    tree* r=findNode(root,key);

    if(r==NULL)        //If key is not present in the tree
        return -1;

    tree* parent=findPNode(root,key);

    if(r->left==NULL)  //parent will come in role when r->left is NULL
        {
            if(parent==NULL || parent->left->key==key)
                return -1;
            else if(parent->right->key==key)
                return parent->key;
        }

    return findfloor(r->left);//process left and then all right's
}

int ceiling(int key)
{
    tree* r=findNode(root,key);

    if(r==NULL)         //If key is not present in the tree
        return -1;

    tree* parent=findPNode(root,key);

    if(r->right==NULL)  // parent will come in role when r->right is NULL
        {
            if(parent == NULL || parent->right->key==key)
                return -1;
            else
                return parent->key;
        }

    return findceil(r->right);//process right and then all left's
}


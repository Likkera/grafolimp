#include <stdio.h>
#include <stdlib.h>

#define TREE struct tree


TREE {
    int value;
    TREE* left;
    TREE* right;
};


TREE *create (int value) {
    TREE *node = (TREE*)malloc(sizeof(TREE));

    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;

    return node;
}


// print in the staright order
void preorder (TREE *elem) {
    printf("%d", elem -> value);

    if (elem -> left)
        preorder(elem -> left);

    if (elem -> right)
        preorder(elem -> right);
}


// print in reverse order
void postorder(TREE *elem) {
    if (elem -> left)
        postorder(elem -> left);

    if (elem -> right)
        postorder(elem -> right);

    printf("%d", elem -> value);
}


// print in simmetric order
void inorder(TREE *elem) {
    if (elem -> left) 
        inorder(elem -> left);

    printf("%d ", elem -> value);

    if (elem -> right)
        inorder(elem -> right);
}


int search(TREE *elem, int key) {
    if (key == elem -> value)
        return 1;
    
    if (!elem)
        return 0;
    
    if (key > elem -> value)
        return search(elem -> right, key);
    return search(elem -> left, key);
}


void insert(TREE *elem, TREE *new) {
    if (new -> value > elem -> value)        
        if (!elem -> right)
            elem -> right = new;
        else    
            insert(elem -> right, new);
    else 
        if (!elem -> left)
            elem -> left = new;
        else 
            insert (elem -> left, new);
}


int main() {
    int n, value, key;
    TREE *root;

    scanf("%d", &n);
    scanf("%d", &value);
    root = create(value);

    for (int i = 1; i < n; i++) {
        scanf("%d", &value);
        insert(root, create(value));
    }
    
    preorder(root);

    return 0;
}




#include <stdio.h>
#include <malloc.h>

#define NODE struct node


NODE {
    int key;
    float value;
    NODE* next;
};


// create element 
NODE* create(int key, float value) {
    NODE *term = (NODE*)malloc(sizeof(NODE));

    term -> key = key;
    term -> value = value;
    term -> next = NULL;

    return term;
}


// add element to top of the list
void push(NODE *term, NODE *new) {
    NODE *last = term -> next;

    term -> next = new;
    new -> next = last;
}


//print every node in the list from top to bottom
void printList(NODE *term) {
    NODE *current = term -> next;

    while (current){
        printf("%d - %f\n", current -> key, current -> value);
        current = current -> next;
    }

    printf("End");
}


// delete top element
void del(NODE *term) {
    NODE *toDel = term -> next;
    term -> next = toDel -> next;

    free(toDel);
}


// delete next element
void delNext(NODE *elem) {
    NODE *toDel = elem -> next;
    elem -> next = toDel -> next;

    free(toDel);
}


// like push but in the current place
void insert(NODE *elem, NODE *new) {
    new -> next = elem -> next;
    elem -> next = new;
}


// delete top elem with returning his value
float pop(NODE *term) {
    if (term -> next != NULL) {
        NODE *toPop = term -> next;
        float value = toPop -> value;

        term -> next = toPop -> next;

        free(toPop);
        return value;
    }

    return 0;
}


// delete the whole list with term
void delList(NODE *term) {
    while (term)
        del(term);
    
    free(term);
}


// get the last element of the list
NODE* getLast(NODE *term) {
    while (term -> next)
        term = term -> next;

    return term;
}


// find value of element by key
float find(NODE *term, int findKey) {
    NODE *current = term -> next;

    while (current -> key != findKey)
        current = current -> next;

    return current -> value;
}


int main() {
    NODE *term = create(0, 0);
    int n, key, findKey;
    float value;

    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%d %f", &key, &value);
        NODE *new = create(key, value);
        push(term, new);
    }

    scanf("%d", &findKey);

    printf("%f\n", find(term, findKey));
    delList(term);

    return 0;
}
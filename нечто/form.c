#include <stdio.h>
#include <malloc.h>

#define NODE struct node


NODE {
    int key;
    float value;
    NODE* next;
};


void createNode(int key, float value, NODE **head){
    NODE *node = (NODE*)malloc(sizeof(NODE));

    node -> key = key;
    node -> value = value;
    node -> next = *head;
    *head = node;
}


void printList(NODE *head, int n){
    NODE *current = head;

    for (int i = 0; i < n; i++){
        printf("%d - %f\n", current -> key, current -> value);
        current = current -> next;
    }
}


int main(){
    NODE *head = NULL;
    int n, key;
    float value;

    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%d %f", &key, &value);
        createNode(key, value, &head);
    }

    printList(head, n);
    return 0;
}
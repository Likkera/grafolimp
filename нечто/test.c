#include <stdio.h> 
#include <malloc.h> 
 
#define LIST struct list 
 
LIST { 
    int key; 
    float value; 
    LIST *next; 
}; 
 
LIST* Create(int key, float value) { 
    LIST *elem; 
    elem = (LIST*)malloc(sizeof(LIST)); 
 
    elem -> key = key; 
    elem -> value = value; 
    elem -> next = NULL; 
 
    return elem; 
} 
 
void Push(LIST *list, LIST *elem) { 
    elem -> next = list -> next; 
    list -> next = elem; 
} 
 
int IsEmpty(LIST *L) { 
    if (L -> next) 
        return 0; 
    return 1; 
} 
 
float Pop(LIST *list) { 
    if (!IsEmpty(list)) { 
        LIST *old = list -> next; 
        list -> next = old -> next; 
        float value = old -> value; 
        free(old); 
        return value; 
    } 
 
    return 0; 
} 
 
void Delete(LIST *pre) { 
    LIST *del = pre -> next; 
    if (del) { 
        pre -> next = del -> next; 
        free(del); 
    } 
} 
 
void Insert(LIST *pre, LIST *elem) { 
    elem -> next = pre -> next; 
    pre -> next = elem; 
} 
 
void PrintList(LIST *list) { 
    int key = list -> key; 
    float value = list -> value; 
    LIST *next = list -> next; 
 
    if (key > 0) 
        printf("%d %f\n", key, value); 
 
 
    if (next != NULL) 
        PrintList(next); 
} 
 
LIST* Last(LIST *list) { 
    LIST *last, *end; 
    end = list; 
 
    do { 
        last = end; 
        end = end -> next; 
    } while (end); 
 
    return last; 
} 
 
float GetByKey(LIST *list, int key) { 
    while (list -> key != key && list != NULL) 
        list = list -> next; 
 
    if(list == NULL) 
        return 0; 
 
    return list -> value; 
} 
 
int ListLen(LIST *list) { 
    int cnt = 0; 
 
    while (list -> next != NULL) { 
        list = list -> next; 
        cnt += 1; 
    } 
 
    return cnt; 
} 
 
void DeleteEven(LIST *list) { 
    LIST *pre = list; 
    list = list -> next; 
 
    while (list != NULL) { 
        if (list -> key % 2 == 0) 
            Delete(pre); 
        else 
            pre = list; 
        list = pre -> next; 
    } 
} 
 
void DeleteOdd(LIST *list) { 
    LIST *pre = list; 
    list = list -> next; 
 
    while (list != NULL) { 
        if (list -> key % 2 == 1) 
            Delete(pre); 
        else 
            pre = list; 
        list = pre -> next; 
    } 
} 
 
int main() { 
    LIST *L, *p, *first; 
    int n, key; 
    float value; 
 
    L = Create(0, 0); 
    scanf("%d", &n); 
 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &key); 
        scanf("%f", &value); 
        p = Create(key, value); 
        Push(L, p); 
    } 
 
    first = L -> next; 
    printf("%f\n", GetByKey(L, 3)); 
    printf("%d\n", ListLen(L)); 
    DeleteOdd(L); 
    PrintList(L); 
 
    return 0; 
}







while (exp[ind] != '\n') {
        while (symbType(exp[ind]) == 10)
            num = toToken(exp[ind], num, numLen);
            numLen++;
            ind++;

            if (symbType(exp[ind]) != 10) 
                num = (char*)realloc(num, 2 * sizeof(char));
                num[0] = ' ';
                tokLen++;
                tokens = (char*)realloc(tokens, tokLen * sizeof(char));
                tokens[tokLen] = num;
}

while (exp[ind] != '\n') {
        while (symbType(exp[ind]) == 10) {
            strExp = toToken(exp[ind], strExp, strExpLen);
            strExpLen++;
            ind++;

            if (symbType(exp[ind]) != 10) {
                strExp = toToken(' ', strExp, strExpLen);
                strExpLen++;
            }
        }

        if (symbType(exp[ind]) != 10) {
            strExp = toToken(exp[ind], strExp, strExpLen);
            strExpLen++;
            ind++;
            strExp = toToken(' ', strExp, strExpLen);
            strExpLen++;
        }
    }

    strExp = toToken('\n', strExp, strExpLen);
    strExpLen++;

    for (int i = 0; strExp[i] != '\n'; i++)
        printf("%s", strExp);







for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            char num[MAX_SIZE] = "";
            int num_null = i;
            while (isdigit(str[i])) {
                num[i - num_null] = str[i];
                i++;
            }
            i--;
            insert(&output_stack, atoi(num));
        }

        else if (is_operator(str[i])) {
            while (!is_empty(&operation_stack) && get_priority(peek(&operation_stack)) >= get_priority(str[i])) {
                operators[output_stack.count + 1] = 1;
                insert(&output_stack, (int)pop(&operation_stack));
            }
            insert(&operation_stack, (int)str[i]);
        }

        else if (str[i] == '(') {
            insert(&operation_stack, (int)str[i]);
        }
        
        else if (str[i] == ')') {
            while (peek(&operation_stack) != '(') {
                operators[output_stack.count + 1] = 1;
                insert(&output_stack, (int)pop(&operation_stack));
            }
            pop(&operation_stack);
        }
    }




    


void printList(NUM **head) {
    NUM *current = *head;

    while (current != NULL) {
        printf("%d ", current -> value);
        current = current -> next;
    }
    printf("\n");
}
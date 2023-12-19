#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_INPUT_LEN 1100
#define OPERATORS "+-*/"
#define PLUS 1
#define MINUS 11
#define MULT 21
#define DIV 31
#define OPENBRK 12
#define CLOSEBRK 22

#define STACK struct stack

STACK {
    long long int value;
    STACK *next;
};

//stack functions

STACK* Create(long long int value) {
    STACK *elem;
    elem = (STACK*)malloc(sizeof(STACK));

    elem -> value = value;
    elem -> next = NULL;

    return elem;
}

void Push(STACK *stack, STACK *elem) {
    elem -> next = stack -> next;
    stack -> next = elem;
}

void Add(STACK *stack, STACK *elem) {
    while (stack -> next != NULL)
        stack = stack -> next;
    stack -> next = elem;
}

long long int Take(STACK *pre) {
    long long int res;
    STACK *elem;

    elem = pre -> next;
    pre -> next = elem -> next;
    res = elem -> value;
    free(elem);

    return res;
}

void Union(STACK *stack1, STACK *stack2) {
    while(stack2 -> next != NULL)
        Add(stack1, Create(Take(stack2)));
}

//support functions

long long int OpId(char arg) {
    for (long long int i = 0; i < 4; i++)
        if (OPERATORS[i] == arg)
            return i;

    return -1;
}

long long int Type(char arg) {
    if (arg >= '0' && arg <= '9')
        return 0;
    else if (OpId(arg) != -1)
        return 1;
    else if (arg == '(' || arg == ')')
        return 2;
    else
        return -1;
}

void Error(STACK *stack) {
    STACK *error;
    error = Create(-1);
    Push(stack, error);
}

void AddOp(STACK *opStack, STACK* res, long long int id) {
    STACK *cur, *pre;
    pre = opStack;
    cur = opStack -> next;

    while (cur != NULL && cur -> value != OPENBRK) {

        if (cur -> value == MULT || cur -> value == DIV)
            Add(res, Create(Take(pre)));

        else if (cur -> value <= MINUS && id <= MINUS)
            Add(res, Create(Take(pre)));

        else pre = cur;

        cur = pre -> next;
    }

    Push(opStack, Create(id));
}

void CloseBracket(STACK *stack, STACK *res) {
    while (stack -> next -> value != OPENBRK)
        Add(res, Create(Take(stack)));
    Take(stack);
}

//main functions

STACK* InputToStack(char *input) {
    STACK *res;
    char curS, lastS;
    int curT, lastT = 1, valMod = 1, openBrks = 0;
    long long int curV = 0;

    res = Create(0);

    for (int i = 0; i < strlen(input); i++) {
        curS = input[i];
        curT = Type(curS);

        if(i > 0 && (lastT != curT || lastT == 2)) {
            curV = (curV * 10 + lastT) * valMod;
            Add(res, Create(curV));
            curV = 0;
            valMod = 1;
        }

        switch(curT) {
            case 0:
                curV *= 10;
                curV += curS - '0';

                if (curV == 0 && lastT == 0) {
                    Error(res);
                    return res;
                }
                break;

            case 1:
                if (lastT == 1 || lastS == '(') {
                    if (curS == '-' && valMod == 1)
                        valMod = -1;
                    else {
                        Error(res);
                        return res;
                    }
                } else
                    curV = OpId(curS);
                break;

            case 2:
                if (curS == '(') {
                    if (lastT == 0) {
                        Error(res);
                        return res;
                    }
                    openBrks++;
                    curV = 1;
                }
                else {
                    if (openBrks == 0 || lastS == '(' || lastT == 1) {
                        Error(res);
                        return res;
                    }
                    openBrks--;
                    curV = 2;
                }
                break;

            default:
                Error(res);
                return res;
        }

        lastT = curT;
        lastS = curS;
    }

    if(lastT == 1) {
        Error(res);
        return res;
    }

    curV = (curV * 10 + lastT) * valMod;
    Add(res, Create(curV));

    if(openBrks > 0)
        Error(res);

    return res;
}

STACK* StackToPolish(STACK *input) {
    long long int value, type;
    STACK *res, *opStack;

    res = Create(0);
    opStack = Create(0);
    input = input -> next;

    while (input != NULL) {
        type = input -> value % 10;
        value = (long long int)input -> value / 10;

        switch(type) {
            case 0:
                Add(res, Create(input -> value));
                break;

            case 1:
                AddOp(opStack, res, input -> value);
                break;

            case 2:
                if (value == 1)
                    Push(opStack, Create(input -> value));
                else
                    CloseBracket(opStack, res);

            default:
                break;
        }
        input = input -> next;
    }

    Union(res, opStack);
    return res;
}

long long int Calc(STACK* polish) {
    long long int cur, type, value, num1, num2;
    STACK *calcStack;
    calcStack = Create(0);

    while (polish -> next != NULL) {
        cur = Take(polish);
        type = cur % 10;
        value = (long long int)cur / 10;

        switch(type) {
            case 0:
                Push(calcStack, Create(value));
                break;

            case 1:
                num2 = Take(calcStack);
                num1 = Take(calcStack);
                switch(value) {
                    case 0:
                        Push(calcStack, Create(num1 + num2));
                        break;
                    case 1:
                        Push(calcStack, Create(num1 - num2));
                        break;
                    case 2:
                        Push(calcStack, Create(num1 * num2));
                        break;
                    case 3:
                        if (num2 == 0)
                            return 1;
                        Push(calcStack, Create(num1 / num2));
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    return Take(calcStack) * 10;
}

int main() {
    char input[MAX_INPUT_LEN];
    long long int res;
    STACK *trInput, *polish;

    gets(input);
    trInput = InputToStack(input);

    if (trInput -> next -> value == -1)
        printf("syntax error");
    else {
        polish = StackToPolish(trInput);
        res = Calc(polish);
        if (res == 1)
            printf("division by zero");
        else
            printf("%lld", res / 10);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    int fp, bp, len;
    int* array;
};
typedef struct stack Stack;

void push(Stack* stack) {
    int n;

    scanf("%d", &n);

    stack->array[stack->bp++] = n;
    ++stack->len;
}

void pop(Stack* stack) {
    if (!stack->len) {
        printf("-1 \n");
        return;
    }

    printf("%d \n", stack->array[--stack->bp]);

    --stack->len;
}

void size(Stack* stack) {
    printf("%d \n", stack->len);
}

void empty(Stack* stack) {
    printf("%hhd \n", stack->len == 0);
}

void top(Stack* stack) {
    if (!stack->len) {
        printf("-1 \n");
        return;
    }

    printf("%d \n", stack->array[stack->bp - 1]);
}

void solution(Stack* stack) {
    char cmd[6];

    scanf("%s", cmd);

    if (!strcmp(cmd, "push")) push(stack);
    if (!strcmp(cmd, "pop")) pop(stack);
    if (!strcmp(cmd, "size")) size(stack);
    if (!strcmp(cmd, "empty")) empty(stack);
    if (!strcmp(cmd, "top")) top(stack);
}

int main() {
    short n;
    Stack* stack;

    scanf("%hd", &n);

    stack = (Stack*)calloc(1, sizeof(Stack));
    stack->array = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        solution(stack);
    }

    free(stack->array);
    free(stack);

    return 0;
}
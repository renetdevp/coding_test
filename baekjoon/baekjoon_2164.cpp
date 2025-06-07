#include <stdio.h>
#include <stdlib.h>

struct node {
    int item;
    node* next;
};

int main() {
    int n;
    node* head, * tail, * np, * tHead;

    scanf("%d", &n);

    head = (node*)calloc(1, sizeof(node));
    head->item = 1;
    np = head;
    tHead = head;
    tail = head;

    for (int i = 1; i < n; ++i) {
        np->next = (node*)calloc(1, sizeof(node));
        np->next->item = i + 1;
        np = np->next;
        tail = np;
    }

    while (tHead != tail) {
        tail->next = tHead->next;
        tHead = tHead->next->next;
        tail = tail->next;
    }

    printf("%d \n", tail->item);

    return 0;
}
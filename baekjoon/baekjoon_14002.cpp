#include <stdio.h>
#include <stdlib.h>

struct set {
    struct set *prev, *next;
    int item;
    int sLen;
};
typedef struct set Set;

void initTable(Set *table, int tLen){
    int max = table[0].item;
    Set *prev = &table[0];

    table[0].sLen = 1; table[0].next = NULL;

    for (int i=1; i<tLen; ++i){
        for (int j=i-1; j>=0; --j){
            if (table[j].sLen >= table[i].sLen && table[j].item < table[i].item){
                table[j].next = &table[i];
                table[i].prev = &table[j];
                table[i].sLen = table[j].sLen+1;
            }
        }
        if (!table[i].sLen) ++table[i].sLen;
    }
}

int main(){
    int n;
    Set *table;

    scanf("%d", &n);

    table = (Set*)calloc(n, sizeof(Set));

    for (int i=0; i<n; ++i) scanf("%d", &table[i].item);

    initTable(table, n);

    int max=0;
    Set *p = (Set*)calloc(1, sizeof(Set));
    for (int i=0; i<n; ++i)
        if (table[i].sLen > max){
            max = table[i].sLen;
            p = &table[i];
        }
    printf("%d \n", max);

    while (p->prev != NULL){
        p->prev->next = p;
        p = p->prev;
    }
    while (p != NULL){
        printf("%d ", p->item);
        p = p->next;
    }

    free(table);
    free(p);

    return 0;
}
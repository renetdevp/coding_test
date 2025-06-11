#include <stdio.h>
#include <stdlib.h>

struct set {
    struct set *prev;
    int item;
    int index;
};
typedef struct set Set;

void initTable(Set *table){
    table[0].item = 0; table[0].prev = NULL; table[0].index = 1;
    table[1].item = 1; table[1].prev = &table[0]; table[1].index = 2;
    table[2].item = 1; table[2].prev = &table[0]; table[2].index = 3;

    for (int i=3; i<1000000; ++i){
        table[i].index = i+1;

        if (!table[i].item){
            table[i].item = table[i-1].item + 1;
            table[i].prev = &table[i-1];
        }

        if ((i+1)%3 == 0){
            if (table[i].item > table[i/3].item+1){
                table[i].item = table[i/3].item+1;
                table[i].prev = &table[i/3];
            }
        }
        if ((i+1)%2 == 0){
            if (table[i].item > table[i/2].item+1){
                table[i].item = table[i/2].item+1;
                table[i].prev = &table[i/2];
            }
        }
    }
}

int main(){
    int x;
    int count=0;
    Set *table = (Set*)calloc(1000000, sizeof(Set));

    scanf("%d", &x);

    initTable(table);

    printf("%d \n", table[x-1].item);
    Set *p = &table[x-1];
    while (p != NULL){
        printf("%d ", p->index);
        p = p->prev;
    }

    free(table);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct set {
    int zCount;
    int oCount;
};
typedef struct set Set;

void initTable(Set *table){
    table[0].zCount = 1;
    table[0].oCount = 0;

    table[1].zCount = 0;
    table[1].oCount = 1;

    for (int i=2; i<41; ++i){
        table[i].zCount = table[i-2].zCount + table[i-1].zCount;
        table[i].oCount = table[i-2].oCount + table[i-1].oCount;
    }
}

void fibonacci(Set *table, int n){
    printf("%d %d \n", table[n].zCount, table[n].oCount);
}

int main(){
    int T;

    scanf("%d", &T);

    for (int i=0; i<T; ++i){
        int n;
        Set *table;

        table = (Set*)calloc(41, sizeof(Set));

        scanf("%d", &n);

        initTable(table);

        fibonacci(table, n);

        free(table);
    }

    return 0;
}
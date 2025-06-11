#include <stdio.h>
#include <stdlib.h>

void initTable(int *table){
    table[0] = 0; table[1] = 1; table[2] = 1;

    for (int i=3; i<1000000; ++i){
        if (!table[i]) table[i] = table[i-1]+1;
        
        if ((i+1)%3 == 0) table[i] = table[i] < table[i/3]+1 ? table[i] : table[i/3]+1;
        if ((i+1)%2 == 0) table[i] = table[i] < table[i/2]+1 ? table[i] : table[i/2]+1;
    }
}

int main(){
    int x;
    int count=0;
    int* table = (int*)calloc(1000000, sizeof(int));

    scanf("%d", &x);

    initTable(table);

    printf("%d \n", table[x-1]);

    free(table);

    return 0;
}
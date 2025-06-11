#include <stdio.h>
#include <stdlib.h>

struct set {
    int w;
    int v;
};
typedef struct set Set;

void ms(Set *table, int start, int end){
    int len = end-start;

    if (len <= 1) return;

    int mid = (start+end)/2;

    ms(table, start, mid);
    ms(table, mid, end);

    Set *tmp = (Set*)calloc(len, sizeof(Set));

    int fp=start, bp=mid;
    for (int i=0; i<len; ++i){
        if (fp>=mid){
            for (int j=i; j<len; ++j) tmp[j] = table[bp++];
            break;
        }
        if (bp>=end){
            for (int j=i; j<len; ++j) tmp[j] = table[fp++];
            break;
        }

        if (table[bp].w < table[fp].w) tmp[i] = table[bp++];
        else tmp[i] = table[fp++];
    }

    for (int i=0; i<len; ++i) table[start+i] = tmp[i];

    free(tmp);
}

void initVTable(Set *table, int *vTable, int tLen, int k){
    for (int i=0; i<tLen; ++i){
        if (table[i].w > k) continue;
        
        if (vTable[table[i].w-1] < table[i].v) vTable[table[i].w-1] = table[i].v;
    }
}

int calcVTable(Set *table, int n, int k){
    int result;
    int **tmp;

    tmp = (int**)calloc(n, sizeof(int*));
    for (int i=0; i<n; ++i) tmp[i] = (int*)calloc(k, sizeof(int));

    for (int i=0; i<k; ++i){
        if (i < table[0].w-1) continue;

        tmp[0][i] = table[0].v;
    }

    for (int i=1; i<n; ++i){
        for (int j=0; j<k; ++j){
            if (j < table[i].w-1){
                tmp[i][j] = tmp[i-1][j];
                continue;
            }

            if (j == table[i].w-1){
                tmp[i][j] = tmp[i-1][j] > table[i].v ? tmp[i-1][j] : table[i].v;
                continue;
            }

            int diffMax = table[i].v + tmp[i-1][j-table[i].w];

            if (tmp[i-1][j] > diffMax) tmp[i][j] = tmp[i-1][j];
            else tmp[i][j] = diffMax;
        }
    }

    result = tmp[n-1][k-1];

    for (int i=0; i<n; ++i) free(tmp[i]);
    free(tmp);

    return result;
}

int main(){
    int n, k;
    Set *table;

    scanf("%d %d", &n, &k);

    table = (Set*)calloc(n, sizeof(Set));

    for (int i=0; i<n; ++i) scanf("%d %d", &table[i].w, &table[i].v);

    ms(table, 0, n);

    printf("%d \n", calcVTable(table, n, k));

    free(table);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct set {
    int st;
    int et;
};
typedef struct set Set;

void mergeSortByDuration(Set *table, int start, int end){
    int len = end-start;

    if (len <= 1) return;

    int mid = ((unsigned int)start+(unsigned int)end)/2;

    mergeSortByDuration(table, start, mid);
    mergeSortByDuration(table, mid, end);

    Set *tmp = (Set*)calloc(len, sizeof(Set));

    int fp=start, bp=mid;
    for (int i=0; i<len; ++i){
        if (fp >= mid){
            for (int j=i; j<len; ++j){
                tmp[j].st = table[bp].st;
                tmp[j].et = table[bp++].et;
            }
            break;
        }
        if (bp >= end){
            for (int j=i; j<len; ++j){
                tmp[j].st = table[fp].st;
                tmp[j].et = table[fp++].et;
            }
            break;
        }

        if (table[bp].et-table[bp].st < table[fp].et-table[fp].st){
            tmp[i].st = table[bp].st;
            tmp[i].et = table[bp++].et;
        }else {
            tmp[i].st = table[fp].st;
            tmp[i].et = table[fp++].et;
        }
    }

    for (int i=0; i<len; ++i){
        table[start+i].st = tmp[i].st;
        table[start+i].et = tmp[i].et;
    }

    free(tmp);
}

void mergeSortByEndTime(Set *table, int start, int end){
    int len = end-start;

    if (len <= 1) return;

    int mid = ((unsigned int)start+(unsigned int)end)/2;

    mergeSortByEndTime(table, start, mid);
    mergeSortByEndTime(table, mid, end);

    Set *tmp = (Set*)calloc(len, sizeof(Set));

    int fp=start, bp=mid;
    for (int i=0; i<len; ++i){
        if (fp >= mid){
            for (int j=i; j<len; ++j){
                tmp[j].st = table[bp].st;
                tmp[j].et = table[bp++].et;
            }
            break;
        }
        if (bp >= end){
            for (int j=i; j<len; ++j){
                tmp[j].st = table[fp].st;
                tmp[j].et = table[fp++].et;
            }
            break;
        }

        if (table[bp].et < table[fp].et){
            tmp[i].st = table[bp].st;
            tmp[i].et = table[bp++].et;
        }else if (table[bp].et == table[fp].et){
            if (table[bp].st < table[fp].st){
                tmp[i].st = table[bp].st;
                tmp[i].et = table[bp++].et;
            }else {
                tmp[i].st = table[fp].st;
                tmp[i].et = table[fp++].et;
            }
        }else {
            tmp[i].st = table[fp].st;
            tmp[i].et = table[fp++].et;
        }
    }

    for (int i=0; i<len; ++i){
        table[start+i].st = tmp[i].st;
        table[start+i].et = tmp[i].et;
    }

    free(tmp);
}

int main(){
    int n;
    int count=0, tmp=0;
    Set *table;
    
    scanf("%d", &n);

    table = (Set*)calloc(n, sizeof(Set));

    for (int i=0; i<n; ++i) scanf("%d %d", &table[i].st, &table[i].et);

    mergeSortByEndTime(table, 0, n);

    for (int i=0; i<n; ++i){
        if (table[i].st>=tmp){
            ++count;
            tmp = table[i].et;
        }
    }

    printf("%d \n", count);

    free(table);

    return 0;
}
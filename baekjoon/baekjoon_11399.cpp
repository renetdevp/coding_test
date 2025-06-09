#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *array, int start, int end){
    int len = end-start;

    if (len <= 1) return;

    int mid = (start+end)/2;

    mergeSort(array, start, mid);
    mergeSort(array, mid, end);

    int *tmp;

    tmp = (int*)calloc(len, sizeof(int));

    int fp=start, bp=mid;
    for (int i=0; i<len; ++i){
        if (fp >= mid){
            for (int j=i; j<len; ++j) tmp[j] = array[bp++];
            break;
        }
        if (bp >= end){
            for (int j=i; j<len; ++j) tmp[j] = array[fp++];
            break;
        }

        if (array[bp] < array[fp]) tmp[i] = array[bp++];
        else tmp[i] = array[fp++];
    }

    for (int i=0; i<len; ++i) array[start+i] = tmp[i];

    free(tmp);
}

int main(){
    int n;
    int sum=0, result=0;
    int *array;

    scanf("%d", &n);

    array = (int*)calloc(n, sizeof(int));

    for (int i=0; i<n; ++i) scanf("%d", &array[i]);

    mergeSort(array, 0, n);

    for (int i=0; i<n; ++i){
        sum += array[i];
        result += sum;
    }

    printf("%d \n", result);

    free(array);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void mergeSortByItem(int *arr, int start, int end, char isReverse){
    int len = end-start;

    if (len <= 1) return;

    int mid = (start+end)/2;

    mergeSortByItem(arr, start, mid, isReverse);
    mergeSortByItem(arr, mid, end, isReverse);

    int *tmp = (int*)calloc(len, sizeof(int));

    int fp=start, bp=mid;
    for (int i=0; i<len; ++i){
        if (fp>=mid){
            for (int j=i; j<len; ++j) tmp[j] = arr[bp++];
            break;
        }
        if (bp>=end){
            for (int j=i; j<len; ++j) tmp[j] = arr[fp++];
            break;
        }

        if (isReverse){
            if (arr[bp] > arr[fp]) tmp[i] = arr[bp++];
            else tmp[i] = arr[fp++];
        }else {
            if (arr[bp] < arr[fp]) tmp[i] = arr[bp++];
            else tmp[i] = arr[fp++];
        }
    }

    for (int i=0; i<len; ++i) arr[start+i] = tmp[i];

    free(tmp);
}

int main(){
    int n;
    int sum=0;
    int *a, *b;

    scanf("%d", &n);

    a = (int*)calloc(n, sizeof(int));
    b = (int*)calloc(n, sizeof(int));

    for (int i=0; i<n; ++i) scanf("%d", &a[i]);
    for (int i=0; i<n; ++i) scanf("%d", &b[i]);

    mergeSortByItem(a, 0, n, 0);
    mergeSortByItem(b, 0, n, 1);

    for (int i=0; i<n; ++i) sum += a[i] * b[i];

    printf("%d \n", sum);

    free(a);
    free(b);

    return 0;
}
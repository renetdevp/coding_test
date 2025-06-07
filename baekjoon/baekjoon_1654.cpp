#include <stdio.h>
#include <stdlib.h>

int solution(int *list, int k, int n, int start, int end){
    int count=0;
    int mid = ((unsigned int)start+(unsigned int)end)/2;
//printf("s,e %d %d \n", start, end);
    if (start == mid){
        for (int i=0; i<k; ++i) count += list[i]/end;
        if (count>=n) return end;
        return start;
    }

    for (int i=0; i<k; ++i) count += list[i]/mid;

    if (count<n) return solution(list, k, n, start, mid);
    else return solution(list, k, n, mid, end);
}

int main(){
    int k, n;
    int *list;
    int max = -1;

    scanf("%d %d", &k, &n);

    list = (int*)calloc(k, sizeof(int));

    for (int i=0; i<k; ++i){
        scanf("%d", &list[i]);
        max = max>list[i] ? max : list[i];
    }

    printf("%d", solution(list, k, n, 0, max));

    free(list);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input(char **s1, int s1Len, char **s2, int s2Len){
    for (int i=0; i<s1Len; ++i) scanf("%s", s1[i]);
    for (int i=0; i<s2Len; ++i) scanf("%s", s2[i]);
}

void mergeSort(char **s, int start, int end){
    int len = end-start;

    if (len <= 1) return;

    int mid = (start+end)/2;

    mergeSort(s, start, mid);
    mergeSort(s, mid, end);

    char **tmp;

    tmp = (char**)calloc(len, sizeof(char*));
    for (int i=0; i<len; ++i) tmp[i] = (char*)calloc(21, sizeof(char));

    int fp = start, bp = mid;
    for (int i=0; i<len; ++i){
        if (fp>=mid){
            for (int j=i; j<len; ++j) tmp[j] = s[bp++];
            break;
        }
        if (bp>=end){
            for (int j=i; j<len; ++j) tmp[j] = s[fp++];
            break;
        }

        if (strcmp(s[fp], s[bp])>0){
            tmp[i] = s[bp++];
        }else {
            tmp[i] = s[fp++];
        }
    }

    for (int i=0; i<len; ++i) s[start+i] = tmp[i];

    free(tmp);
}

int binSearch(char *s, char **list, int start, int end){
    int mid = (start+end)/2;
    int result = strcmp(s, list[mid]);
    
    if (start == mid && result) return -1;

    if (!result) return mid;

    if (result<0) return binSearch(s, list, start, mid);
    if (result>0) return binSearch(s, list, mid, end);
}

void solution(char **s1, int s1Len, char **s2, int s2Len){
    int count=0;
    int *result;

    result = (int*)calloc(s1Len>s2Len ? s1Len : s2Len, sizeof(int));

    for (int i=0; i<s1Len; ++i){
        int tmp = binSearch(s1[i], s2, 0, s2Len);

        if (tmp != -1) result[count++] = tmp;
    }

    printf("%d \n", count);
    for (int i=0; i<count; ++i) printf("%s \n", s2[result[i]]);

    free(result);
}

int main(){
    int n, m;
    char **s1, **s2;

    scanf("%d %d", &n, &m);

    s1 = (char**)calloc(n, sizeof(char*));
    for (int i=0; i<n; ++i) s1[i] = (char*)calloc(21, sizeof(char));
    s2 = (char**)calloc(m, sizeof(char*));
    for (int i=0; i<m; ++i) s2[i] = (char*)calloc(21, sizeof(char));

    input(s1, n, s2, m);

    mergeSort(s1, 0, n);
    mergeSort(s2, 0, m);

    solution(s1, n, s2, m);

    return 0;
}
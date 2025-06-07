#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeTable(char **table, int n){
    for (int i=0; i<n; ++i) free(table[i]);
    free(table);
}

void bfs(char **table, char **visited, short *result, int u, int v, int len, int rCount){
    char dy[] = { -1, 0, 1, 0 };
    char dx[] = { 0, 1, 0, -1 };
    short *queue;
    short front=0, back=0;
    short count=0, n;

    queue = (short*)calloc(len*len, sizeof(short));

    queue[back++] = u*len + v;
    visited[u][v] = 1;
    ++count;

    while (front<back){
        n = queue[front++];
        short ty = n/len, tx = n%len;

        for (char i=0; i<4; ++i){
            int yp = ty+dy[i], xp = tx+dx[i];
            
            if (yp<0 || xp<0) continue;
            if (yp>=len || xp>=len) continue;

            if (table[yp][xp]-'0'==1 && visited[yp][xp] == 0) {
                queue[back++] = yp*len+xp;
                visited[yp][xp] = 1;
                ++count;
            }
        }
    }

    result[rCount] = count;

    free(queue);
}

void mergeSort(short *result, short start, short end){
    short len = end-start;

    if (len<=1) return;

    short mid = (start+end)/2;

    mergeSort(result, start, mid);
    mergeSort(result, mid, end);

    short *temp = (short*)calloc(len, sizeof(short));

    short tp=0;
    short fp=start, bp=mid;
    for (short i=0; i<len; ++i){
        if (fp >= mid){
            for (int j=i; j<len; ++j) temp[j] = result[bp++];
            break;
        }
        if (bp >= end){
            for (int j=i; j<len; ++j) temp[j] = result[fp++];
            break;
        }

        if (result[bp]<result[fp]) temp[i] = result[bp++];
        else temp[i] = result[fp++];
    }

    for (short i=0; i<len; ++i) result[start+i] = temp[i];

    free(temp);
}

int main(){
    short n, count=0;
    short *result;
    char **table, **visited;

    scanf("%hd", &n);

    table = (char**)calloc(n, sizeof(char*));
    for (char i=0; i<n; ++i) table[i] = (char*)calloc(n+1, sizeof(char));
    visited = (char**)calloc(n, sizeof(char*));
    for (char i=0; i<n; ++i) visited[i] = (char*)calloc(n, sizeof(char));
    result = (short*)calloc(n*n, sizeof(short));

    for (char i=0; i<n; ++i){
        scanf("%s", table[i]);
    }

    for (char i=0; i<n; ++i){
        for (char j=0; j<n; ++j){
            if (table[i][j]-'0' == 1 && visited[i][j] == 0){
                bfs(table, visited, result, i, j, n, count++);
            }
        }
    }

    freeTable(table, n);
    freeTable(visited, n);

    mergeSort(result, 0, count);

    printf("%d \n", count);
    for (short i=0; i<count; ++i) printf("%d \n", result[i]);

    //freeTable(table, n);
    //freeTable(visited, n);
    free(result);

    return 0;
}
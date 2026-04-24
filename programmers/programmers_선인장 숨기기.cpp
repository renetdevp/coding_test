#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int M, N, H, W;

int** initTable(){
    int **table = (int**)calloc(M+1, sizeof(int*));
    for (int i=0; i<=M; ++i) table[i] = (int*)calloc(N+1, sizeof(int));
    
    return table;
}

void freeTable(int **table){
    for (int i=0; i<=M; ++i) free(table[i]);
    free(table);
}

char prefixSum(int **table, int *answer){
    if (!table[0][0]){
        answer[0] = 0; answer[1] = 0;
        return 1;
    }

    for (int i=1; i<=N-W; ++i){
        table[0][i] += table[0][i-1];
        if (!table[0][i]){
            answer[0] = 0; answer[1] = i;
            return 1;
        }
    }

    for (int i=1; i<=M-H; ++i){
        for (int j=0; j<=N-W; ++j){
            if (!j) table[i][j] += table[i-1][j];
            else table[i][j] += table[i-1][j] + table[i][j-1] - table[i-1][j-1];
            
            if (!table[i][j]){
                answer[0] = i; answer[1] = j;
                return 1;
            }
        }
    }
    
    return 0;
}

void imos(int **table, int **drops, int r){
    for (int i=0; i<r; ++i){
        int dy = drops[i][0], dx = drops[i][1];
        int y = dy > M-H ? M-H : dy;
        int x = dx > N-W ? N-W : dx;
        int sy = dy-H < -1 ? 0 : dy-H+1;
        int sx = dx-W < -1 ? 0 : dx-W+1;

        ++table[sy][sx];
        --table[sy][x+1];
        --table[y+1][sx];
        ++table[y+1][x+1];
    }
}

void binSearch(int **table, int **drops, int *answer, int start, int end){
    if (start > end) return;

    for (int i=0; i<M+1; ++i) memset(table[i], 0, (N+1) * sizeof(int));

    int mid = start/2 + end/2 + (start%2 && end%2);
    
    imos(table, drops, mid);

    if (prefixSum(table, answer)) binSearch(table, drops, answer, mid+1, end);
    else binSearch(table, drops, answer, start, mid-1);
}

int* solution(int m, int n, int h, int w, int** drops, size_t drops_rows, size_t drops_cols) {
    M = m; N = n; H = h; W = w;

    int* answer = (int*)calloc(2, sizeof(int));
    int **table = initTable();
    
    binSearch(table, drops, answer, 0, drops_rows);
    
    freeTable(table);
    
    return answer;
}
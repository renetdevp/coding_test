#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeTable(char** table, int n) {
    for (int i = 0; i < n; ++i) free(table[i]);
    free(table);
}

void bfs(char** table, char** visited, short u, short v, short yLen, short xLen) {
    char dy[] = { -1, 0, 1, 0 };
    char dx[] = { 0, 1, 0, -1 };
    short* queue;
    short front = 0, back = 0;
    short n;

    queue = (short*)calloc(yLen * xLen, sizeof(short));

    queue[back++] = u * xLen + v;
    visited[u][v] = 1;

    while (front < back) {
        n = queue[front++];
        short ty = n / xLen, tx = n % xLen;

        for (char i = 0; i < 4; ++i) {
            int yp = ty + dy[i], xp = tx + dx[i];

            if (yp < 0 || xp < 0) continue;
            if (yp >= yLen || xp >= xLen) continue;

            if (table[yp][xp] == 1 && visited[yp][xp] == 0) {
                queue[back++] = yp * xLen + xp;
                visited[yp][xp] = 1;
            }
        }
    }

    free(queue);
}

int main() {
    int T;
    short n, m, k, count;
    char** table, ** visited;

    scanf("%d", &T);

    for (int e = 0; e < T; ++e) {
        short x, y;
        count = 0;

        scanf("%hd %hd %hd", &m, &n, &k);

        table = (char**)calloc(n, sizeof(char*));
        visited = (char**)calloc(n, sizeof(char*));
        if (table == nullptr || visited == nullptr) {
            printf("error occurred while init \n");
            return -1;
        }
        for (short i = 0; i < n; ++i) {
            table[i] = (char*)calloc(m, sizeof(char));
            visited[i] = (char*)calloc(m, sizeof(char));

            if (table[i] == nullptr || visited[i] == nullptr) {
                printf("error occurred while init \n");
                return -1;
            }
        }

        for (short i = 0; i < k; ++i) {
            scanf("%hd %hd", &x, &y);

            table[y][x] = 1;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (table[i][j] && !visited[i][j]) {
                    bfs(table, visited, i, j, n, m);
                    ++count;
                }
            }
        }

        freeTable(table, n);
        freeTable(visited, n);

        printf("%d \n", count);
    }

    return 0;
}
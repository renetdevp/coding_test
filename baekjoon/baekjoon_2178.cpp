#include <stdio.h>
#include <stdlib.h>

int bfs(char** table, int n, int m) {
    int* queue;
    int** distance;
    int fp = 0, bp = 0, result;
    char dy[] = { -1, 0, 1, 0 };
    char dx[] = { 0, 1, 0, -1 };

    queue = (int*)calloc(n * m, sizeof(int));
    distance = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i) distance[i] = (int*)calloc(m, sizeof(int));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            distance[i][j] = n * m + 1;

    queue[bp++] = 0;
    distance[0][0] = 1;

    while (fp < bp) {
        int p = queue[fp++];
        int selfDistance = distance[p / m][p % m];

        for (char i = 0; i < 4; ++i) {
            int yp = p / m + dy[i], xp = p % m + dx[i];

            if (yp < 0 || xp < 0) continue;
            if (yp >= n || xp >= m) continue;

            if (table[yp][xp] - '0' && distance[yp][xp] == n * m + 1) {
                queue[bp++] = yp * m + xp;
                distance[yp][xp] = selfDistance + 1;
            }
        }
    }

    result = distance[n - 1][m - 1];

    free(queue);
    for (int i = 0; i < n; ++i) free(distance[i]);
    free(distance);

    return result;
}

int main() {
    int n, m;
    char** table;

    scanf("%d %d", &n, &m);

    table = (char**)calloc(n, sizeof(char*));
    for (int i = 0; i < n; ++i) {
        table[i] = (char*)calloc(m + 1, sizeof(char));
        scanf("%s", table[i]);
    }

    printf("%d", bfs(table, n, m));

    for (int i = 0; i < n; ++i) free(table[i]);
    free(table);

    return 0;
}
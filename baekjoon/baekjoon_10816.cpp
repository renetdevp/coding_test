#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    int* hash;
    int max = -1;

    scanf("%d", &n);

    hash = (int*)calloc(20000001, sizeof(int));

    for (int i = 0; i < n; ++i) {
        int tmp;

        scanf("%d", &tmp);

        ++hash[10000000 + tmp];
    }

    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        int tmp;

        scanf("%d", &tmp);

        printf("%d ", hash[10000000 + tmp]);
    }

    free(hash);

    return 0;
}
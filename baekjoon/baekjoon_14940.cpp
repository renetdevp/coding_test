#include <stdio.h>
#include <stdlib.h>

void solution(int **map, int n, int m, int p){
	char dy[] = { -1, 0, 1, 0 };
	char dx[] = { 0, 1, 0, -1 };
	int fp=0, bp=0, count=1;
	int *queue;

	queue = (int*)calloc(n*m, sizeof(int));

	queue[bp++] = p;
	while (fp<bp){
		int tmp = queue[fp++];

		for (int i=0; i<4; ++i){
			int sy = tmp/m+dy[i], sx = tmp%m+dx[i];

			if (sy<0 || sx<0) continue;
			if (sy>=n || sx>=m) continue;

			if (map[sy][sx] == -1){
				map[sy][sx] = map[tmp/m][tmp%m]+1;
				queue[bp++] = sy*m+sx;
			}
		}
	}

	free(queue);
}

int main(){
	int n, m;
	int p = -1;
	int **map;

	scanf("%d %d", &n, &m);

	map = (int**)calloc(n, sizeof(int*));
	for (int i=0; i<n; ++i) map[i] = (int*)calloc(m, sizeof(int));

	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j){
			char tmp;
			scanf("%hhd", &tmp);

			if (tmp == 2) p = i*m+j;
			else if (tmp == 1) map[i][j] = -1;
		}
	}

	solution(map, n, m, p);

	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j) printf("%d ", map[i][j]);
		printf("\n");
	}

	for (int i=0; i<n; ++i) free(map[i]);
	free(map);

	return 0;
}
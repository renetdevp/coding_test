#include <stdio.h>
#include <stdlib.h>

void freeAll(char **visited, int n, int *queue){
	free(queue);
	for (int i=0; i<n; ++i) free(visited[i]);
	free(visited);
}

void solution(char **box, int n, int m){
	int *queue;
	char **visited;
	int fp=0, bp=0, count=-1;
	char dy[] = { -1, 0, 1, 0 };
	char dx[] = { 0, 1, 0, -1 };

	queue = (int*)calloc(n*m, sizeof(int));
	visited = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) visited[i] = (char*)calloc(m, sizeof(char));

	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j){
			if (box[i][j]==1){
				queue[bp++] = i*m+j;
				visited[i][j] = 1;
			}
		}
	}

	while (fp<bp){
		int tmp = bp;

		for (int i=fp; i<tmp; ++i){
			int y=queue[i]/m, x=queue[i]%m;

			++fp;

			for (int j=0; j<4; ++j){
				int sy = y+dy[j], sx=x+dx[j];
				if (sy<0 || sx<0) continue;
				if (sy>=n || sx>=m) continue;

				if (!box[sy][sx]){
					queue[bp++] = sy*m+sx;
					box[sy][sx] = 1;
				}
			}
		}
		++count;
	}

	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j){
			if (!box[i][j] && !visited[i][j]){
				printf("-1 \n");
				freeAll(visited, n, queue);
				return;
			}
		}
	}

	printf("%d \n", count);

	freeAll(visited, n, queue);
}

int main(){
	int n, m;
	char **box;

	scanf("%d %d", &m, &n);

	box = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) box[i] = (char*)calloc(m, sizeof(char));

	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			scanf("%hhd", &box[i][j]);

	solution(box, n, m);

	for (int i=0; i<n; ++i) free(box[i]);
	free(box);

	return 0;
}
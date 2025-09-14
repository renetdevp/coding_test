#include <stdio.h>
#include <stdlib.h>

struct Queue {
	int length;
	int *arr;
};

void bfs(char **table, char **visited, int n, int position, char mode){
	Queue *queue = (Queue*)calloc(1, sizeof(Queue));
	queue->arr = (int*)calloc(n*n, sizeof(int));
	char target = table[position/n][position%n];
	char dy[4] = { -1, 0, 1, 0 };
	char dx[4] = { 0, 1, 0, -1 };

	queue->arr[(queue->length)++] = position;
	visited[position/n][position%n] = 1;

	while (queue->length > 0){
		int tp = queue->arr[--(queue->length)];
		int y = tp/n, x = tp%n;

		for (int i=0; i<4; ++i){
			int ty = y+dy[i], tx = x+dx[i];
			if (ty<0 || ty>=n) continue;
			if (tx<0 || tx>=n) continue;

			if (visited[ty][tx]) continue;

			if (table[ty][tx] == target) {
				queue->arr[(queue->length)++] = ty*n + tx;
				visited[ty][tx] = 1;
				continue;
			}

			if (mode && (target=='R' || target=='G') && table[ty][tx]!='B'){
				queue->arr[(queue->length)++] = ty*n + tx;
				visited[ty][tx] = 1;
			}
		}
	}

	free(queue->arr);
	free(queue);
}

void printRegion(char **table, int n, char mode){
	char **visited = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) visited[i] = (char*)calloc(n, sizeof(char));
	int count = 0;

	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			if (visited[i][j]) continue;

			bfs(table, visited, n, i*n+j, mode);
			++count;
		}
	}

	printf("%d ", count);

	for (int i=0; i<n; ++i) free(visited[i]);
	free(visited);
}

void solution(int n){
	char **table = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) table[i] = (char*)calloc(n+1, sizeof(char));

	for (int i=0; i<n; ++i) scanf("%s", table[i]);

	printRegion(table, n, 0);
	printRegion(table, n, 1);

	for (int i=0; i<n; ++i) free(table[i]);
	free(table);
}

int main(){
	int n;

	scanf("%d", &n);

	solution(n);

	return 0;
}
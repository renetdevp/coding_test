#include <stdio.h>
#include <stdlib.h>

struct Set {
	int dest;
	int cost;
};

struct Path {
	int length;
	int capacity;
	Set *arr;
};

struct PQueue {
	int length;
	Set *queue;
};

void insert(Path *path, int src, int dest, int cost){
	Path *target = &(path[src-1]);

	if (target->length == target->capacity){
		target->capacity = !target->capacity ? 4 : 2*target->capacity;
		target->arr = (Set*)realloc(target->arr, target->capacity * sizeof(Set));

		if (target->arr == NULL) exit(-1);
	}

	target->arr[target->length].dest = dest;
	target->arr[(target->length)++].cost = cost;
}

void insert(PQueue *pq, int node, int distance){
	Set tmp;

	tmp.dest = node;
	tmp.cost = distance;

	pq->queue[++(pq->length)] = tmp;

	int p = pq->length;
	while (p/2 >= 1){
		if (pq->queue[p/2].cost <= pq->queue[p].cost) break;

		Set tmp1 = pq->queue[p/2];
		pq->queue[p/2] = pq->queue[p];
		pq->queue[p] = tmp1;

		p /= 2;
	}
}

Set pop(PQueue *pq){
	if (pq->length <= 0){
		printf("pq is empty \n");
		return { -1, -1 };
	}

	Set result = pq->queue[1];

	pq->queue[1] = pq->queue[(pq->length)--];

	int p = 1;
	while (p*2 <= pq->length){
		Set *min = &(pq->queue[p*2]);
		int tp = p*2;

		if (p*2+1 <= pq->length && pq->queue[p*2].cost > pq->queue[p*2+1].cost){
			min = &(pq->queue[p*2+1]);
			tp = p*2+1;
		}

		if (pq->queue[p].cost <= min->cost) break;

		Set tmp = pq->queue[p];
		pq->queue[p] = *min;
		*min = tmp;

		p = tp;
	}

	return result;
}

void freeAll(Path *path, int *distance, char *visited, PQueue *pq, int n){
	//free(pq->queue);
	free(pq);
	free(visited);
	free(distance);
	for (int i=0; i<n; ++i)
		if (path[i].length > 0) free(path[i].arr);
	free(path);
}

void solution(int n, int m){
	Path *path = (Path*)calloc(n, sizeof(Path));
	int *distance = (int*)calloc(n, sizeof(int));
	char *visited = (char*)calloc(n, sizeof(char));
	PQueue *pq = (PQueue*)calloc(1, sizeof(PQueue));

	if (pq == NULL) exit(-1);

	pq->queue = (Set*)calloc(m+1, sizeof(Set));

	if (path==NULL || distance==NULL || visited==NULL || pq->queue==NULL) exit(-1);

	for (int i=0; i<n; ++i) distance[i] = ~(1<<31);

	// input
	for (int i=0; i<m; ++i){
		int src, dest, cost;

		scanf("%d %d %d", &src, &dest, &cost);

		insert(path, src, dest, cost);
	}

	int src, dest;

	scanf("%d %d", &src, &dest);

	// main op
	distance[src-1] = 0;
	insert(pq, src, 0);

	while (pq->length > 0){
		Set tmp = pop(pq);

		if (visited[tmp.dest-1]) continue;

		Path *target = &(path[tmp.dest-1]);
		for (int i=0; i<target->length; ++i){
			if (distance[target->arr[i].dest-1] > (distance[tmp.dest-1] + target->arr[i].cost)){
				distance[target->arr[i].dest-1] = distance[tmp.dest-1] + target->arr[i].cost;
				insert(pq, target->arr[i].dest, distance[target->arr[i].dest-1]);
			}
		}

		visited[tmp.dest-1] = 1;
	}

	printf("%d \n", distance[dest-1]);

	// free
	freeAll(path, distance, visited, pq, n);
}

int main(){
	int n, m;

	scanf("%d", &n);
	scanf("%d", &m);

	solution(n, m);

	return 0;
}
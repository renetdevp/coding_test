#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20000
#define MAX_EDGES 300000

struct Set {
	int dest;
	int weight;
};

struct PQueue {
	int length;
	Set *queue;
};

struct Path {
	int capacity;
	int length;
	Set *arr;
};

void insert(PQueue *pq, int v, int w){
	if (pq->length >= MAX_EDGES){
		printf("pq overflow \n");
		exit(-1);
	}

	Set tmp;

	tmp.dest = v;
	tmp.weight = w;

	pq->queue[++(pq->length)] = tmp;

	int p = pq->length;
	while (p/2 >= 1){
		if (pq->queue[p/2].weight <= pq->queue[p].weight) break;

		Set tmp1 = pq->queue[p/2];

		pq->queue[p/2] = pq->queue[p];
		pq->queue[p] = tmp1;

		p /= 2;
	}
}

Set pop(PQueue *pq){
	if (pq->length <= 0){
		printf("pq is empty \n");
		exit(-1);
	}

	Set result = pq->queue[1];

	pq->queue[1] = pq->queue[(pq->length)--];

	int p = 1;
	while (p*2 <= pq->length){
		Set min = pq->queue[p*2];
		int tp = p*2;

		if (p*2+1 <= pq->length && min.weight >= pq->queue[p*2+1].weight){
			min = pq->queue[p*2+1];
			tp = p*2+1;
		}

		if (min.weight >= pq->queue[p].weight) break;

		Set tmp = pq->queue[p];

		pq->queue[p] = pq->queue[tp];
		pq->queue[tp] = tmp;

		p = tp;
	}

	return result;
}

void insertPath(Path *path, int u, int v, int w){
	if (path[u-1].length == path[u-1].capacity){
		path[u-1].capacity = !path[u-1].capacity ? 4 : path[u-1].capacity*2;
		//path[u-1].arr = (Set*)realloc(path[u-1].arr, path[u-1].capacity);
		Set *tAddr = (Set*)realloc(path[u-1].arr, path[u-1].capacity * sizeof(Set));
		if (tAddr == NULL){
			printf("failed to realloc in insertPath() \n");
			exit(-1);
		}
		path[u-1].arr = tAddr;
	}

	Set tmp;

	tmp.dest = v;
	tmp.weight = w;

	path[u-1].arr[(path[u-1].length)++] = tmp;
}

void solution(int vertex, int edge){
	Path *path = (Path*)calloc(vertex, sizeof(Path));
	PQueue *pq = (PQueue*)calloc(1, sizeof(PQueue));
	pq->queue = (Set*)calloc(edge+1, sizeof(Set));
	int *distance = (int*)calloc(vertex, sizeof(int));
	char *visited = (char*)calloc(vertex, sizeof(char));
	int k;

	for (int i=0; i<vertex; ++i) distance[i] = ~(1<<31);

	scanf("%d", &k);

	for (int i=0; i<edge; ++i){
		int u, v, w;

		scanf("%d %d %d", &u, &v, &w);

		insertPath(path, u, v, w);
	}

	distance[k-1] = 0;
	insert(pq, k, 0);

	while (pq->length > 0){
		Set tmp = pop(pq);

		if (visited[tmp.dest-1] == 1) continue;

		for (int i=0; i<path[tmp.dest-1].length; ++i){
			Set *target = &(path[tmp.dest-1].arr[i]);

			if (tmp.weight+target->weight >= distance[target->dest-1]) continue;

			distance[target->dest-1] = tmp.weight+target->weight;
			insert(pq, target->dest, distance[target->dest-1]);
		}

		visited[tmp.dest-1] = 1;
	}

	for (int i=0; i<vertex; ++i){
		if (distance[i] == ~(1<<31)) printf("INF \n");
		else printf("%d \n", distance[i]);
	}

	free(visited);
	free(distance);
	free(pq->queue);
	free(pq);
	for (int i=0; i<vertex; ++i){
		if (path[i].length > 0) free(path[i].arr);
	}
	free(path);
}

int main(){
	int v, e;

	scanf("%d %d", &v, &e);

	solution(v, e);

	return 0;
}
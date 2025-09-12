#include <stdio.h>
#include <stdlib.h>

struct Set {
	int n;
	int cost;
};

struct PQueue {
	int length;
	Set *queue;
};

void insert(PQueue *pq, int n, int cost){
	if (pq->length >= 100000){
		printf("pq overflow \n");
		exit(-1);
	}

	Set *target = &(pq->queue[++(pq->length)]);

	target->n = n;
	target->cost = cost;

	int p = pq->length;
	while (p/2 >= 1){
		if (pq->queue[p/2].cost <= pq->queue[p].cost) break;

		Set tmp = pq->queue[p/2];

		pq->queue[p/2] = pq->queue[p];
		pq->queue[p] = tmp;

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
		Set min = pq->queue[p*2];
		int tp = p*2;

		if (p*2+1 <= pq->length && pq->queue[p*2].cost >= pq->queue[p*2+1].cost){
			min = pq->queue[p*2+1];
			tp = p*2+1;
		}

		if (pq->queue[p].cost <= min.cost) break;

		Set tmp = pq->queue[p];

		pq->queue[p] = min;
		pq->queue[tp] = tmp;

		p = tp;
	}

	return result;
}

void solution(int n, int k){
	if (n == k){
		printf("0 \n");
		return;
	}

	if (n > k){
		printf("%d \n", n-k);
		return;
	}

	PQueue *pq = (PQueue*)calloc(1, sizeof(PQueue));
	pq->queue = (Set*)calloc(100001, sizeof(Set));
	int *distance = (int*)calloc(100001, sizeof(int));

	for (int i=0; i<100000; ++i) distance[i] = ~(1<<31);
	insert(pq, n, 0);

	int p = n;
	while (pq->length > 0){
		Set target = pop(pq);
		//printf("target: %d,%d \n", target.n, target.cost);
		if (target.n == -1 && target.cost == -1) break;

		if (target.n == k){
			distance[k] = target.cost;
			break;
		}

		if (target.cost >= (n>k ? n-k : k-n)) continue;
		if (target.cost >= distance[target.n]) continue;

		distance[target.n] = target.cost;

		if (target.n >= 1) insert(pq, target.n-1, target.cost+1);
		if (target.n < 100000) insert(pq, target.n+1, target.cost+1);
		if (target.n <= 50000) insert(pq, target.n*2, target.cost);

		//printf("pq: "); for (int i=1; i<=pq->length; ++i) printf("%d,%d ", pq->queue[i].n, pq->queue[i].cost); printf("\n");
	}

	printf("%d \n", distance[k]);

	free(distance);
	free(pq->queue);
	free(pq);
}

int main(){
	int n, k;

	scanf("%d %d", &n, &k);

	solution(n, k);

	return 0;
}
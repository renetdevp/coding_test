#include <stdio.h>
#include <stdlib.h>

struct Edge {
	int pl;
	int cl, cc;
	int delay;
	int *child;
};

void insert2edge(Edge *edge, int src, int dst){
	Edge *target = &edge[dst-1];
	Edge *pEdge = &edge[src-1];
	
	if (!pEdge->cc){
		pEdge->cc = 4;
		pEdge->child = (int*)calloc(4, sizeof(int));
	}

	if (pEdge->cl == pEdge->cc){
		pEdge->cc *= 2;
		pEdge->child = (int*)realloc(pEdge->child, pEdge->cc*sizeof(int));
	}

	++target->pl;
	pEdge->child[pEdge->cl++] = dst;
}

Edge* initBuild(int n, int k){
	Edge *build = (Edge*)calloc(n, sizeof(Edge));
	int src, dst;
	
	for (int i=0; i<n; ++i) scanf("%d", &build[i].delay);

	for (int i=0; i<k; ++i){
		scanf("%d %d", &src, &dst);
		insert2edge(build, src, dst);
	}

	return build;
}

void freeBuild(Edge *build, int n){
	for (int i=0; i<n; ++i){
		if (build[i].child != NULL) free(build[i].child);
	}
	free(build);
}

void tsort(Edge *build, int n, int w){
	int qp = 0, ql = 0;
	int *queue = (int*)calloc(n, sizeof(int));
	int *delay = (int*)calloc(n, sizeof(int));

	for (int i=0; i<n; ++i){
		if (!build[i].pl){
			queue[ql++] = i;
			delay[i] = build[i].delay;
		}
	}

	while (qp<ql){
		int tmp = queue[qp++];

		for (int i=0; i<build[tmp].cl; ++i){
			int cn = build[tmp].child[i]-1;
			Edge *child = &build[cn];

			delay[cn] = delay[tmp]+child->delay > delay[cn] ? delay[tmp]+child->delay : delay[cn];

			if (--child->pl == 0) queue[ql++] = cn;
		}
	}

	printf("%d \n", delay[w-1]);

	free(delay);
	free(queue);
}

void solution(){
	int n, k, w;
	int rl = 0;
	Edge *build;

	scanf("%d %d", &n, &k);

	build = initBuild(n, k);

	scanf("%d", &w);

	tsort(build, n, w);
	
	freeBuild(build, n);
}

int main(){
	int T;

	scanf("%d", &T);

	for (int i=0; i<T; ++i) solution();

	return 0;
}
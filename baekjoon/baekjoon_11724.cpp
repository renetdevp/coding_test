#include <stdio.h>
#include <stdlib.h>

struct node {
	int len;
	int capacity;
	int *adj;
};
typedef struct node Node;

struct graph {
	Node *nodes;
};
typedef struct graph Graph;

void addEdge(Graph *graph, int u, int v){
	Node *node = &graph->nodes[u-1];

	if (!node->len){
		node->adj = (int*)calloc(4, sizeof(int));
		node->adj[node->len++] = v;
		node->capacity = 4;
		return;
	}

	if (node->len == node->capacity){
		node->adj = (int*)realloc(node->adj, 2*node->capacity*sizeof(int));
		node->capacity *= 2;
	}

	node->adj[node->len++] = v;
}

void freeAll(Graph *graph, int n, char *visited, int *queue){
	for (int i=0; i<n; ++i)
		if (graph->nodes[i].len) free(graph->nodes[i].adj);
	free(graph->nodes);
	free(graph);
	free(visited);
	free(queue);
}

int main(){
	int n, m;
	int p=0, fp=0, bp=0;
	int count=1;
	int *queue;
	char *visited;
	Graph *graph = (Graph*)calloc(1, sizeof(graph));

	scanf("%d %d", &n, &m);

	graph->nodes = (Node*)calloc(n, sizeof(Node));
	visited = (char*)calloc(n, sizeof(char));
	queue = (int*)calloc(n, sizeof(int));

	for (int i=0; i<m; ++i){
		int u, v;

		scanf("%d %d", &u, &v);

		addEdge(graph, u, v);
		addEdge(graph, v, u);
	}

	queue[bp++] = 1;
	visited[0] = 1;
	while (p<n){
		if (fp<bp){
			int point = queue[fp++];
			Node *node = &graph->nodes[point-1];

			for (int i=0; i<node->len; ++i){
				if (!visited[node->adj[i]-1]){
					queue[bp++] = node->adj[i];
					visited[node->adj[i]-1] = 1;
				}
			}

			continue;
		}

		if (visited[p]){
			++p;
			continue;
		}

		// queue도 비어있고 visited[p]=0인 경우 p+1를 queue에 넣어야 함. ++count도 해야하고
		queue[bp++] = p+1;
		visited[p] = 1;
		++count;
	}

	printf("%d \n", count);

	freeAll(graph, n, visited, queue);

	return 0;
}
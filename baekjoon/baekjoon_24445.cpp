#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>

struct adjNodeList {
    int len;
    int capacity;
    int* array;
};

struct adjGraph {
    adjNodeList* adjNodeArr;
    int nodeCount;
};

adjGraph* initAdjGraph(int n) {
    adjGraph* graph;

    graph = (adjGraph*)malloc(sizeof(adjGraph));
    graph->adjNodeArr = (adjNodeList*)calloc(n, sizeof(adjNodeList));
    graph->nodeCount = n;

    return graph;
}

void addEdge(adjGraph* graph, int u, int v) {
    adjNodeList* list = &graph->adjNodeArr[u];

    if (list->len == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
    }
    list->array[list->len++] = v;
}

void freeGraph(adjGraph* graph) {
    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->adjNodeArr[i].len == 0) continue;

        free(graph->adjNodeArr[i].array);
    }
    free(graph->adjNodeArr);
    free(graph);
}

int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

void sortGraph(adjGraph* graph) {
    for (int i = 0; i < graph->nodeCount; ++i) {
        if (graph->adjNodeArr[i].len > 1) {
            qsort(graph->adjNodeArr[i].array, graph->adjNodeArr[i].len, sizeof(int), cmp);
        }
    }
}

int* bfs(adjGraph* graph, int root, int len, int mLen) {
    char* visited;
    int* queue, * result;
    int front = 0, back = 0, count = 0;

    visited = (char*)calloc(len, sizeof(char));
    result = (int*)calloc(len, sizeof(int));

    queue = (int*)malloc(mLen * sizeof(int));

    queue[back++] = root;
    visited[root - 1] = 1;

    while (front < back) {
        int n = queue[front++];
        result[n - 1] = ++count;

        int nLen = graph->adjNodeArr[n - 1].len;

        if (nLen == 0) continue;

        for (int i = 0; i < graph->adjNodeArr[n - 1].len; ++i) {
            int item = graph->adjNodeArr[n - 1].array[i];

            if (visited[item - 1] != 1) {
                queue[back++] = item;
                visited[item - 1] = 1;
            }
        }
    }

    free(visited);
    free(queue);

    return result;
}

int main() {
    int n, m, r;
    int* result;
    adjGraph* graph;

    scanf("%d %d %d", &n, &m, &r);
    //n = 100000;
    //m = 200000;
    //r = 1;

    graph = initAdjGraph(n);

    //srand(time(NULL));

    for (int i = 0; i < m; ++i) {
        int src, dest;

        scanf("%d %d", &src, &dest);
        //src = rand()%100000+1;
        //dest = rand()%100000+1;

        addEdge(graph, src - 1, dest);
        addEdge(graph, dest - 1, src);
    }

    sortGraph(graph);

    result = bfs(graph, r, n, n > m + 1 ? n : m + 1);
    for (int i = 0; i < n; ++i) printf("%d \n", result[i]);

    //bfs(graph, r, n, n>m+1 ? n : m+1);

    //freeGraph(graph, n);
    free(result);

    return 0;
}
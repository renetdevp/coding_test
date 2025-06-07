#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// dfs()는 90%, 91%에서 시간 초과 문제가 발생했음
int* dfs(adjGraph* graph, int root, int mLen) {
    char* visited;
    int* stack, * result;
    int sp = 0, count = 0;
    int len = graph->nodeCount;

    visited = (char*)calloc(len, sizeof(char));
    stack = (int*)calloc(mLen, sizeof(int));
    result = (int*)calloc(len, sizeof(int));

    stack[sp++] = root;
    visited[root - 1] = 1;
    result[root - 1] = ++count;

    while (sp > 0) {
        int n = stack[sp - 1];
        int nLen = graph->adjNodeArr[n - 1].len;
        char flag = 0;

        // 인접 노드들을 순회하다가 visted != 1인 노드를 찾으면 stack에 추가하고 visited=1
        for (int i = 0; i < nLen; ++i) {
            int item = graph->adjNodeArr[n - 1].array[i];
            //printf("item: %d \n", item);
            if (visited[item - 1] != 1) {
                stack[sp++] = item;
                visited[item - 1] = 1;
                result[item - 1] = ++count;
                flag = 1;
                break;
            }
        }

        if (!flag) --sp;
    }

    free(visited);
    free(stack);

    return result;
}

void dfs2(adjGraph* graph, char* visited, int* result, int n, int* count) {
    int len = graph->adjNodeArr[n - 1].len;

    visited[n - 1] = 1;
    result[n - 1] = ++(*count);

    for (int i = 0; i < len; ++i) {
        int item = graph->adjNodeArr[n - 1].array[i];

        if (!visited[item - 1]) {
            dfs2(graph, visited, result, item, count);
        }
    }
}

int main() {
    int n, m, r;
    int* result, * count;
    char* visited;
    adjGraph* graph;

    scanf("%d %d %d", &n, &m, &r);

    graph = initAdjGraph(n);

    visited = (char*)calloc(n, sizeof(char));
    result = (int*)calloc(n, sizeof(int));
    count = (int*)calloc(1, sizeof(int));

    for (int i = 0; i < m; ++i) {
        int src, dest;

        scanf("%d %d", &src, &dest);

        addEdge(graph, src - 1, dest);
        addEdge(graph, dest - 1, src);
    }

    sortGraph(graph);

    dfs2(graph, visited, result, r, count);
    for (int i = 0; i < n; ++i) printf("%d \n", result[i]);

    //freeGraph(graph);
    free(result);
    free(count);

    return 0;
}
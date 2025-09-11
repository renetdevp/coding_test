#include <stdio.h>
#include <stdlib.h>

struct Set {
    int dst;
    int cost;
};

struct MinHeap {
    int length;
    int capacity;
    Set *heap;
};

struct PQueue {
    int length;
    Set *queue;
};

void insert(PQueue *pq, int n, int dist){
    Set *target = &(pq->queue[++(pq->length)]);

    target->dst = n;
    target->cost = dist;

    int p = pq->length;

    while (p/2>=1){
        if (pq->queue[p/2].cost <= pq->queue[p].cost) break;

        Set tmp = pq->queue[p/2];

        pq->queue[p/2] = pq->queue[p];
        pq->queue[p] = tmp;

        p /= 2;
    }
}

Set pop(PQueue* pq) {
    Set result = pq->queue[1];

    if (pq->length <= 0){
        Set errorSet;

        errorSet.dst = -1;
        errorSet.cost = -1;

        return errorSet;
    }

    pq->queue[1] = pq->queue[(pq->length)--];

    int p = 1;
    int len = pq->length;

    while (p*2<=len){
        if (p*2+1 <= len && pq->queue[p*2].cost >= pq->queue[p*2+1].cost) {
            if (pq->queue[p].cost <= pq->queue[p*2+1].cost) break;

            Set tmp = pq->queue[p];

            pq->queue[p] = pq->queue[p*2+1];
            pq->queue[p*2+1] = tmp;

            p = p*2+1;
        }else {
            if (pq->queue[p].cost <= pq->queue[p*2].cost) break;

            Set tmp = pq->queue[p];

            pq->queue[p] = pq->queue[p*2];
            pq->queue[p*2] = tmp;

            p *= 2;
        }
    }

    return result;
}

void hos(MinHeap *path, int n, int m, int src, int dst){
    PQueue *pq = (PQueue*)calloc(1, sizeof(PQueue));
    pq->queue = (Set*)calloc(m, sizeof(Set));
    Set *distance = (Set*)calloc(n, sizeof(Set));
    char *visited = (char*)calloc(n, sizeof(char));

    for (int i=0; i<n; ++i){
        distance[i].cost = ~(1<<31);
        distance[i].dst = -1;   // use Set.dst as before
    }

    distance[src-1].cost = 0;
    insert(pq, src, 0);

    while (pq->length > 0){
        Set tmp = pop(pq);

        if (tmp.dst == -1 && tmp.cost == -1) return;

        if (visited[tmp.dst-1]) continue;

        // tmp의 값이 쓰레기 값이나 null이 아니면 tmp.dst에 연결된 모든 노드의 distance를 최신화
        MinHeap *target = &(path[tmp.dst-1]);

        if (target->length <= 0) continue;

        for (int i=1; i<=target->length; ++i){
            if (distance[target->heap[i].dst-1].cost > (distance[tmp.dst-1].cost + target->heap[i].cost)){
                distance[target->heap[i].dst-1].cost = distance[tmp.dst-1].cost + target->heap[i].cost;
                distance[target->heap[i].dst-1].dst = tmp.dst;
                insert(pq, target->heap[i].dst, distance[target->heap[i].dst-1].cost);
            }
        }

        visited[tmp.dst-1] = 1;
    }

    printf("%d \n", distance[dst-1].cost);

    int p = dst, count=0;
    int *result = (int*)calloc(n, sizeof(int));
    while (p != -1){
        result[count++] = p;
        p = distance[p-1].dst;
    }

    printf("%d \n", count);
    for (int i=count-1; i>=0; --i) printf("%d ", result[i]);

    free(result);
    free(visited);
    free(distance);
    free(pq->queue);
    free(pq);
}

void insert(MinHeap *path, int n, int m, int cost){
    int *len = &path[n-1].length;
    int *cap = &path[n-1].capacity;

    if (++(*len) >= *cap) *cap = !(*cap) ? 4 : (*cap)*2;
    path[n-1].heap = (Set*)realloc(path[n-1].heap, *cap * sizeof(Set));
    
    Set *heap = path[n-1].heap;

    int p = *len;

    heap[*len].dst = m;
    heap[*len].cost = cost;

    while (p/2>=1){
        if (heap[p].cost >= heap[p/2].cost) break;

        Set tmp = { heap[p].dst, heap[p].cost };
        
        heap[p].dst = heap[p/2].dst;
        heap[p].cost = heap[p/2].cost;
        heap[p/2].dst = tmp.dst;
        heap[p/2].cost = tmp.cost;

        p /= 2;
    }
}

Set pop(MinHeap *path, int n){
    int *len = &path[n-1].length;
    Set *heap = path[n-1].heap;

    if (!(*len)){
        Set errorSet;

        errorSet.dst = -1;
        errorSet.cost = -1;

        return errorSet;
    }

    Set result = heap[1];

    heap[1].dst = heap[*len].dst;
    heap[1].cost = heap[(*len)--].cost;

    int p = 1;
    while (p*2<=*len){
        Set *fc = &heap[p*2];
        Set *sc = &heap[p*2+1];
        Set *minChildSet = fc;

        if (p*2+1 <= *len && fc->cost > sc->cost) minChildSet = sc;

        if (minChildSet->cost >= heap[p].cost) break;

        Set tmp = heap[p];

        heap[p] = *minChildSet;
        *minChildSet = tmp;

        p = fc->cost<sc->cost ? p*2 : p*2+1;
    }

    return result;
}

void printPath(MinHeap *path, int n){
    for (int i = 0; i < n; ++i) {
        if (!(path[i].length)) continue;

        printf("%d \n", i + 1);
        for (int j=0; j<path[i].length; ++j) {
            Set *tmp = &path[i].heap[j+1];
            printf("%d %d \n", tmp->dst, tmp->cost);
        }
        printf("\n");
    }
}

void solution(int n, int m){
    int src, dest;
    char *visited = (char*)calloc(n, sizeof(char));
    int *distance = (int*)calloc(n, sizeof(int));
    MinHeap *path = (MinHeap*)calloc(n, sizeof(MinHeap));

    for (int i=0; i<m; ++i){
        int s, d, c;

        scanf("%d %d %d", &s, &d, &c);

        insert(path, s, d, c);
    }

    scanf("%d %d", &src, &dest);

    hos(path, n, m, src, dest);

    free(visited);
    free(distance);
    for (int i=0; i<n; ++i)
        if (!(path[i].length))
            free(path[i].heap);
    free(path);
}

int main(){
    int n, m;

    scanf("%d", &n);
    scanf("%d", &m);

    solution(n, m);

    return 0;
}
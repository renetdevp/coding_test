#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct set {
    int item;
    int level;
};
typedef set Set;

int main(){
    int n, k;
    int fp=0, bp=0;
    Set *queue;
    char *visited;

    scanf("%d %d", &n, &k);

    queue = (Set*)calloc(200000, sizeof(Set));
    visited = (char*)calloc(200000, sizeof(char));

    queue[bp].item = n;
    queue[bp++].level = 0;
    visited[n] = 1;

    while (fp<bp){
        Set node = queue[fp++];

        if (node.item == k){
            printf("%d \n", node.level);
            break;
        }

        if (node.item-1==k || node.item+1==k || node.item*2==k){
            printf("%d \n", node.level+1);
            break;
        }
        
        if (!node.item && !visited[node.item+1]) {
            queue[bp].item = node.item+1;
            queue[bp++].level = node.level+1;
            visited[node.item+1] = 1;
            continue;
        }

        if (k<node.item && !visited[node.item-1]){
            queue[bp].item = node.item-1;
            queue[bp++].level = node.level+1;
            visited[node.item-1] = 1;
            continue;
        }

        if (node.item>-1 && !visited[node.item-1]){
            queue[bp].item = node.item-1;
            queue[bp++].level = node.level+1;
            visited[node.item-1] = 1;
        }
        if (node.item+1<200000 && !visited[node.item+1]){
            queue[bp].item = node.item+1;
            queue[bp++].level = node.level+1;
            visited[node.item+1] = 1;
        }
        if (node.item*2<200000 && !visited[node.item*2]){
            queue[bp].item = node.item*2;
            queue[bp++].level = node.level+1;
            visited[node.item*2] = 1;
        }
    }

    free(queue);
    free(visited);

    return 0;
}
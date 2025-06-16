#include <stdio.h>
#include <stdlib.h>

void solution(int *trees, int start, int end, int m, int len){
	int mid = ((unsigned int)start+(unsigned int)end)/2;
	unsigned long long sum=0;

	for (int i=0; i<len; ++i)
		if (trees[i]>mid) sum += trees[i]-mid;

	if (start == mid){
		printf("%d \n", sum<m ? end : start);
		return;
	}

	if (sum<m) solution(trees, start, mid, m, len);
	else solution(trees, mid, end, m, len);
}

int main(){
	int n, m;
	int max = (1<<31);
	int *trees;

	scanf("%d %d", &n, &m);

	trees = (int*)calloc(n, sizeof(int));

	for (int i=0; i<n; ++i){
		scanf("%d", &trees[i]);
		max = max>trees[i] ? max : trees[i];
	}

	solution(trees, 0, max, m, n);

	free(trees);

	return 0;
}
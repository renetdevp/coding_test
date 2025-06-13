#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, m;
	int *table, *sum;

	scanf("%d %d", &n, &m);

	table = (int*)calloc(n, sizeof(int));
	sum = (int*)calloc(n+1, sizeof(int));

	for (int i=0; i<n; ++i) scanf("%d", &table[i]);

	for (int i=0; i<n; ++i) sum[i+1] = sum[i]+table[i];

	for (int i=0; i<m; ++i){
		int n1, n2;

		scanf("%d %d", &n1, &n2);

		printf("%d \n", sum[n2]-sum[n1-1]);
	}

	free(table);
	free(sum);

	return 0;
}
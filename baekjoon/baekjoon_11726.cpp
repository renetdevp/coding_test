#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	int *table;

	scanf("%d", &n);

	table = (int*)calloc(n, sizeof(int));

	// table[2]=3, table[3]=5, table[4]=
	table[0] = 1; table[1] = 2;
	for (int i=2; i<n; ++i) table[i] = (table[i-1]+table[i-2])%10007;

	printf("%d \n", table[n-1]);

	free(table);

	return 0;
}
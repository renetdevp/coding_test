#include <stdio.h>
#include <stdlib.h>

void solution(char **table, int *bc, int *wc, int sX, int sY, int len){
	if (len<=1){
		table[sY][sX] ? ++(*bc) : ++(*wc);
		return;
	}

	char painted = 1;
	char flag=table[sY][sX];
	for (int i=0; i<len; ++i){
		for (int j=0; j<len; ++j){
			if (table[sY+i][sX+j] != flag){
				painted = 0;
				break;
			}
		}
	}

	if (!painted){
		solution(table, bc, wc, sX, sY, len/2);
		solution(table, bc, wc, sX+len/2, sY, len/2);
		solution(table, bc, wc, sX, sY+len/2, len/2);
		solution(table, bc, wc, sX+len/2, sY+len/2, len/2);
	}else flag ? ++(*bc) : ++(*wc);
}

int main(){
	int n;
	int *bc = (int*)calloc(1, sizeof(int));
	int *wc = (int*)calloc(1, sizeof(int));
	char **table;

	scanf("%d", &n);

	table = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) table[i] = (char*)calloc(n, sizeof(char));

	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			scanf("%hhd", &table[i][j]);

	solution(table, bc, wc, 0, 0, n);

	printf("%d\n%d", *wc, *bc);

	free(bc);
	free(wc);
	for (int i=0; i<n; ++i) free(table[i]);
	free(table);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned short u16;

int **table;
char ***dpTable;
char n;

void initTable(){
	table = (int**)calloc(n, sizeof(int*));
	
	for (char i=0; i<n; ++i){
		char tmp;
		table[i] = (int*)calloc(n, sizeof(int));

		for (char j=0; j<n; ++j){
			scanf("%c", &tmp);

			if (tmp == '\n'){
				--j;
				continue;
			}

			table[i][j] = tmp - '0';
		}
	}
}

void freeTable(){
	for (char i=0; i<n; ++i) free(table[i]);
	free(table);
}

void initDPTable(){
	dpTable = (char***)calloc(pow(2, n), sizeof(char**));

	for (int i=0; i<pow(2, n); ++i){
		dpTable[i] = (char**)calloc(n, sizeof(char*));

		for (char j=0; j<n; ++j){
			dpTable[i][j] = (char*)calloc(n, sizeof(char));
		}
	}
}

void freeDPTable(){
	for (int i=0; i<pow(2, n); ++i){
		for (char j=0; j<n; ++j) free(dpTable[i][j]);
		free(dpTable[i]);
	}
	free(dpTable);
}

char max(char a, char b){
	return a>b ? a : b;
}

char dfs(u16 flag, char result, char p, char price){
	if (dpTable[flag][p][price]) return dpTable[flag][p][price];

	char cnt = result;

	for (char i=0; i<n; ++i){
		if ((flag & (1 << i)) != 0) continue;

		if (table[p][i] < price) continue;

		cnt = max(cnt, dfs((flag | (1 << i)), result+1, i, table[p][i]));
	}

	dpTable[flag][p][price] = cnt;

	return cnt;
}

// price와 파는 사람 p가 주어졌을 때 해당 가격으로 살 수 있는 사람을 flag로 표시?
// -> flag로 표시했던 살 수 있는 사람 중에 '이미 구매했던' 사람이 있는지 어떻게 확인할건가?

void solution(){
	char result;

	scanf("%hhd", &n);

	initTable();
	initDPTable();

	result = dfs(1, 1, 0, 0);

	printf("%hhd \n", result);

	freeDPTable();
	freeTable();
}

int main(){
	solution();

	return 0;
}
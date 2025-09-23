#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b){
	return a>b ? a : b;
}

void printTable(int **table, int n){
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j) printf("%d ", table[i][j]);
		printf("\n");
	}
}

char verticalCondition(char rollTo, int y, int n){
	if (!rollTo) return y < n;
	if (rollTo == 2) return y >= 0;

	printf("wrong invoke of verticalCondition() \n");
	exit(-2);
}

int rollVertical(int **table, int **newTable, int n, char rollTo){
	int max = 1<<31;
	int sp, sy, dy;

	if (!rollTo){
		sp = 0;
		sy = 0;
		dy = 1;
	}else {
		sp = n-1;
		sy = n-1;
		dy = -1;
	}

	for (int x=0; x<n; ++x){
		int p = sp;
		for (int y=sy; verticalCondition(rollTo, y, n); y+=dy){
			if (!table[y][x]) continue;

			if (!newTable[p][x]){
				newTable[p][x] = table[y][x];
				max = getMax(max, newTable[p][x]);
				continue;
			}

			if (table[y][x] == newTable[p][x]){
				newTable[p][x] *= 2;
				max = getMax(max, newTable[p][x]);
				p += dy;
				continue;
			}

			p += dy;
			newTable[p][x] = table[y][x];
			max = getMax(max, newTable[p][x]);
		}
	}

	return max;
}

char horizontalCondition(char rollTo, int x, int n){
	if (rollTo == 1) return x >= 0;
	if (rollTo == 3) return x < n;

	printf("wrong invoke of horizontalCondition() \n");
	exit(-2);
}

int rollHorizontal(int **table, int **newTable, int n, char rollTo){
	int max = 1<<31;
	int sp, sx, dx;

	if (rollTo == 1){
		sp = n-1;
		sx = n-1;
		dx = -1;
	}else {
		sp = 0;
		sx = 0;
		dx = 1;
	}

	for (int y=0; y<n; ++y){
		int p = sp;
		for (int x=sx; horizontalCondition(rollTo, x, n); x+=dx){
			if (!table[y][x]) continue;

			if (!newTable[y][p]){
				newTable[y][p] = table[y][x];
				max = getMax(max, newTable[y][p]);
				continue;
			}

			if (table[y][x] == newTable[y][p]){
				newTable[y][p] *= 2;
				max = getMax(max, newTable[y][p]);
				p += dx;
				continue;
			}

			p += dx;
			newTable[y][p] = table[y][x];
			max = getMax(max, newTable[y][p]);
		}
	}

	return max;
}

// rollTo: 0-top, 1-right, 2-bottom, 3-left
int roll(int **table, int n, int count, char rollTo){
	if (count >= 5) return -1;

	int **newTable = (int**)calloc(n, sizeof(int*));
	for (int i=0; i<n; ++i) newTable[i] = (int*)calloc(n, sizeof(int));
	int max = 1<<31;
	int rollMax;

	if (rollTo%2) rollMax = rollHorizontal(table, newTable, n, rollTo);
	else rollMax = rollVertical(table, newTable, n, rollTo);
	max = getMax(max, rollMax);

	max = getMax(max, roll(newTable, n, count+1, 0));
	max = getMax(max, roll(newTable, n, count+1, 1));
	max = getMax(max, roll(newTable, n, count+1, 2));
	max = getMax(max, roll(newTable, n, count+1, 3));

	for (int i=0; i<n; ++i) free(newTable[i]);
	free(newTable);

	return max;
}

void solution(int n){
	int **table = (int**)calloc(n, sizeof(int*));
	for (int i=0; i<n; ++i){
		table[i] = (int*)calloc(n, sizeof(int));
		for (int j=0; j<n; ++j) scanf("%d", &table[i][j]);
	}
	int max = 1<<31;

	max = getMax(max, roll(table, n, 0, 0));
	max = getMax(max, roll(table, n, 0, 1));
	max = getMax(max, roll(table, n, 0, 2));
	max = getMax(max, roll(table, n, 0, 3));

	printf("%d \n", max);
}

int main(){
	int n;

	scanf("%d", &n);

	solution(n);

	return 0;
}
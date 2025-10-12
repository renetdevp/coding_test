#include <stdio.h>
#include <stdlib.h>

int** initCoord(short n){
	int **coords = (int**)calloc(n, sizeof(int*));
	for (short i=0; i<n; ++i){
		coords[i] = (int*)calloc(2, sizeof(int));
		scanf("%d %d", &coords[i][0], &coords[i][1]);
	}

	return coords;
}

void freeCoord(int **coords, short n){
	for (short i=0; i<n; ++i) free(coords[i]);
	free(coords);
}

void solution(short n){
	long long sum = 0;
	int **coords = initCoord(n);

	for (short i=0; i<n; ++i){
		sum += (long long)coords[i][0]*(long long)coords[(i+1)%n][1];
		sum -= (long long)coords[i][1]*(long long)coords[(i+1)%n][0];
	}

	long double result = sum / 2.0;
	result = result<0 ? -result : result;

	printf("%.1Lf \n", result);

	freeCoord(coords, n);
}

int main(){
	short n;

	scanf("%hd", &n);

	solution(n);

	return 0;
}
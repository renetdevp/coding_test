#include <stdio.h>
#include <stdlib.h>

int** initSpiral(short r1, short c1, short r2, short c2){
	int **spiral;

	spiral = (int**)calloc(r2-r1+1, sizeof(int*));
	for (int i=0; i<=r2-r1; ++i) spiral[i] = (int*)calloc(c2-c1+1, sizeof(int));

	return spiral;
}

int getSpiralNum(int y, int x){
	int ay = abs(y), ax = abs(x);
	int n = ay>ax? ay : ax;

	if (!n) return 1;

	int result = (4*n)*(n-1) + 1;	// square(2*n - 1)

	if (x == n){
		if (y == n) result += 8*n;
		else result += n-y;
	}else if (y == -n){
		result += n-x + 2*n;
	}else if (x == -n){
		result += y+n + 4*n;
	}else {
		result += x+n + 6*n;
	}

	return result;
}

int fillSpiral(int **spiral, short r1, short c1, short r2, short c2){
	int max = 1<<31;

	for (int i=r1; i<=r2; ++i){
		for (int j=c1; j<=c2; ++j){
			spiral[i-r1][j-c1] = getSpiralNum(i, j);
			max = max>spiral[i-r1][j-c1] ? max : spiral[i-r1][j-c1];
		}
	}

	return max;
}

int getDigit(int n){
	if (!n) return 0;

	int result = 0;

	while (n){
		n /= 10;
		++result;
	}

	return result;
}

void prettyPrint(int **spiral, int height, int width, int ml){
	for (int i=0; i<height; ++i){
		for (int j=0; j<width; ++j){
			int l = ml - getDigit(spiral[i][j]);

			for (int k=0; k<l; ++k) printf(" ");

			printf("%d ", spiral[i][j]);
		}

		printf("\n");
	}
}

void solution(){
	short r1, r2, c1, c2;
	int ml;
	int max;
	int **spiral;

	scanf("%hd %hd %hd %hd", &r1, &c1, &r2, &c2);

	spiral = initSpiral(r1, c1, r2, c2);

	max = fillSpiral(spiral, r1, c1, r2, c2);

	ml = getDigit(max);

	prettyPrint(spiral, r2-r1+1, c2-c1+1, ml);

	for (int i=0; i<r2-r1; ++i) free(spiral[i]);
	free(spiral);
}

int main(){
	solution();

	return 0;
}
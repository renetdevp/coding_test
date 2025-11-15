#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int square(int a){
	return a*a;
}

double getDistance(int x1, int y1, int x2, int y2){
	return sqrt((double)square(x2-x1) + square(y2-y1));
}

void solution(){
	int T;
	int x1, y1, x2, y2;
	int cx, cy, r;
	int count;
	char n;

	scanf("%d", &T);

	for (int i=0; i<T; ++i){
		count = 0;

		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		scanf("%hhd", &n);

		for (char j=0; j<n; ++j){
			scanf("%d %d %d", &cx, &cy, &r);

			if (getDistance(x1, y1, cx, cy)<r != getDistance(x2, y2, cx, cy)<r) ++count;
		}

		printf("%d \n", count);
	}
}

int main(){
	solution();

	return 0;
}
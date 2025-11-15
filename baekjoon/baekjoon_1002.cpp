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
	int r1, r2;
	double d;
	char result;

	scanf("%d", &T);

	for (int i=0; i<T; ++i){
		scanf("%d %d %d", &x1, &y1, &r1);
		scanf("%d %d %d", &x2, &y2, &r2);

		d = getDistance(x1, y1, x2, y2);

		if (x1==x2 && y1==y2 && r1==r2) result = -1;
		else if (d==r1+r2 || d==abs(r2-r1)) result = 1;
		else if (d > r1+r2) result = 0;
		else if (d < abs(r2-r1)) result = 0;
		else result = 2;

		printf("%hhd \n", result);
	}
}

int main(){
	solution();

	return 0;
}
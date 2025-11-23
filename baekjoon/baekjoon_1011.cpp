#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getMinMovement(int x, int y){
	int distance = y-x;
	double tmp = sqrt((double)distance);
	int hos = floor(tmp);

	if (hos == tmp) return 2*hos-1;
	if (distance <= hos*hos + hos) return 2*hos;
	return 2*hos+1;
}

void solution(){
	int x, y;

	scanf("%d %d", &x, &y);

	printf("%d \n", getMinMovement(x, y));
}

int main(){
	int T;

	scanf("%d", &T);

	for (int i=0; i<T; ++i) solution();

	return 0;
}
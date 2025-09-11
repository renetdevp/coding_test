#include <stdio.h>
#include <stdlib.h>

void init(int *arr){
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 4;

	for (int i=3; i<10; ++i) arr[i] = arr[i-3]+arr[i-2]+arr[i-1];
}

int main(){
	int T;
	int *arr = (int*)calloc(10, sizeof(int));

	scanf("%d", &T);

	init(arr);

	for (int i=0; i<T; ++i){
		int n;

		scanf("%d", &n);

		printf("%d \n", arr[n-1]);
	}

	free(arr);

	return 0;
}
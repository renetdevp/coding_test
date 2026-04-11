#include <stdio.h>
#include <stdlib.h>

int i = 0;
long long arr[1024] = { 0L, };

void getDN(int n, int limit, long long base){
	for (int j=n; j<limit; ++j){
		if (!n) arr[i++] = base*10 + (long long)j;
		else getDN(n-1, j, base*10 + (long long)j);
	}
}

void solution(){
	int n;

	for (char j=0; j<10; ++j) getDN(j, 10, 0);

	scanf("%d", &n);

	if (n >= i) printf("-1 \n");
	else printf("%lld \n", arr[n]);
}

int main(){
	solution();

	return 0;
}
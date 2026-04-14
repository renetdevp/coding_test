#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, max = -1;
char digit = 0;
char flag[1000000][10] = { 0, };

void getDigit(){
	if (N <= 0) return;

	int n = N;

	while (n>0){
		++digit;
		n /= 10;
	}
}

int exchange(int n, char i, char j){
	int result = 0;
	char s[10] = { 0, };

	sprintf(s, "%d", n);

	char tmp = s[i-1];

	s[i-1] = s[j-1];
	s[j-1] = tmp;

	if (s[0] == '0') return -1;

	return atoi(s);
}

void next(int n, char k){
	if (n == -1) return;

	if (k <= 0){
		max = max > n ? max : n;
		return;
	}

	if (flag[n-1][k-1]) return;

	flag[n-1][k-1] = 1;

	for (char i=1; i<digit; ++i){
		for (char j=i+1; j<=digit; ++j){
			next(exchange(n, i, j), k-1);
		}
	}
}

void solution(){
	char K;

	scanf("%d %hhd", &N, &K);

	getDigit();

	next(N, K);

	printf("%d \n", max);
}

int main(){
	solution();

	return 0;
}
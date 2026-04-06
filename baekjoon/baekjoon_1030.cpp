#include <stdio.h>
#include <stdlib.h>

char N, K;

char getColor(char s, int r, int c){
	if (!s) return 0;

	char edge = (N-K) / 2;
	int rp = r%N;
	int cp = c%N;

	// 흰 정사각형의 테두리에 속한다면 (가운데의 K*K에 속하지 않는다면) 그 전 시간(s-1)에서의 색을 계산
	if (rp < edge || rp >= edge+K) return getColor(s-1, r/N, c/N);
	if (cp < edge || cp >= edge+K) return getColor(s-1, r/N, c/N);

	// 가운데의 k*k에 속한다면 1(검은색) 반환
	return 1;
}

void solution(){
	char s;
	int r1, r2, c1, c2;

	scanf("%hhd %hhd %hhd %d %d %d %d", &s, &N, &K, &r1, &r2, &c1, &c2);

	for (int i=r1; i<=r2; ++i){
		for (int j=c1; j<=c2; ++j){
			printf("%hhd", getColor(s, i, j));
		}
		printf("\n");
	}
}

int main(){
	solution();

	return 0;
}
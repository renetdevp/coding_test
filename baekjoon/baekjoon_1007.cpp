#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double result;

struct Coord {
	int y;
	int x;
};

Coord* initCoords(char n){
	Coord *P = (Coord*)calloc(n, sizeof(Coord));

	for (char i=0; i<n; ++i)
		scanf("%d %d", &P[i].y, &P[i].x);

	return P;
}

double hos(int dx, int dy){
	return sqrt((double)dx*dx + (double)dy*dy);
}

void hhos(Coord *P, char n, char *isEnd, char en, char pi){
	if (en >= n/2){
		int sumXEnd = 0;
		int sumYEnd = 0;
		double tmp = DBL_MAX;

		for (char i=0; i<n; ++i){
			if (isEnd[i]){
				sumXEnd += P[i].x;
				sumYEnd += P[i].y;
			}
			else {
				sumXEnd -= P[i].x;
				sumYEnd -= P[i].y;
			}
		}

		tmp = hos(sumXEnd, sumYEnd);

		result = result>tmp ? tmp : result;

		return;
	}

	if (n/2-en >= n-pi) return;
	
	isEnd[pi] = 1;
	hhos(P, n, isEnd, en+1, pi+1);
	isEnd[pi] = 0;
	hhos(P, n, isEnd, en, pi+1);
}

void solution(){
	char n;
	char *isEnd;
	Coord *P;

	scanf("%hhd", &n);

	result = DBL_MAX;
	isEnd = (char*)calloc(n, sizeof(char));
	P = initCoords(n);

	// 벡터의 합 > 순서가 상관 있는 두 점의 집합
	// 결국 (dx, dy)로 나타낼 수 있고, 벡터의 합이니 (sum(all dx), sum(all dy))의 길이를 구해서 해결
	// 위 값이 최소가 되게끔
	// dx := x_end - x_start, dy := y_end - y_start
	// for (int i=0; i<n/2; ++i){ dx += x_end[i]-x_start[i]; dy += y_end[i]-y_start[i]; } result = hos(dx, dy);
	// dx == sum(all x_end) - sum(all x_start), dy == sum(all y_end) - sum(all y_start)
	hhos(P, n, isEnd, 0, 0);

	printf("%lf \n", result);

	free(P);
	free(isEnd);
}

int main(){
	int T;

	scanf("%d", &T);

	for (int i=0; i<T; ++i) solution();

	return 0;
}
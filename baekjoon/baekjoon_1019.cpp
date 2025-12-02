#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char getNumberOfDigit(double n){
	char result = 0;

	while (n >= 1){
		++result;
		n = floor(n / 10);
	}

	return result;
}

char getNumberByDigit(double n, char digit){
	if (n < pow(10, digit-1)) return 0;

	double result = floor(n / pow(10, digit-1));
	result -= floor(n / pow(10, digit)) * 10;

	return (char)result;
}

double mod(double n, double m){
	double tmp = m;

	while (tmp <= n) tmp += m;

	return n + m - tmp;
}

void solution(){
	double n;
	char nOfDigit;
	int result[10] = { 0, };

	scanf("%lf", &n);

	nOfDigit = getNumberOfDigit(n);

	for (char i=1; i<= nOfDigit; ++i){
		double beforeN = floor(n / pow(10, i)) * pow(10, i-1);	// 지금 세고 있는 자릿수보다 위의 수 * 현재 자릿수의 크기. ex) n := 12345이고, i=3일 때 1200 (= 12 * pow(10, 3))
		double afterN = mod(n, pow(10, i-1));	// 지금 세고 있는 자릿수보다 아래의 수. ex) n := 12345이고, i=3일 때 afterN=45 (= n % pow(10, 2))
		char nByDigit = getNumberByDigit(n, i);

		// 0은 별도로 계산해야 함
		for (char j=1; j<10; ++j){
			result[j] += beforeN;

			if (nByDigit > j) result[j] += pow(10, i-1);
			if (nByDigit == j) result[j] += afterN + 1;
		}

		if (!beforeN) continue;

		if (!nByDigit) result[0] += beforeN-pow(10, i-1) + afterN + 1;
		else result[0] += beforeN;
	}

	for (char i=0; i<10; ++i) printf("%d ", result[i]);
}

int main(){
	solution();

	return 0;
}
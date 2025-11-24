#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0: invalid, 1: valid
char startsWith(char s[], int len, int *p){
	if (len-*p < 2) return 0;

	if (!strncmp(s + *p, "01", 2)){
		*p += 2;
		return 1;
	}

	if (!strncmp(s + *p, "10", 2)){
		int tmp = 0;

		*p += 2;

		if (s[*p] != '0') return 0;
		while (!strncmp(s + ++(*p), "0", 1)){}

		if (s[*p] != '1') return 0;
		while (!strncmp(s + ++(*p), "1", 1)){
			++tmp;
		}

		// 위의 100+1+ 패턴의 마지막 '1'이 '10'의 시작이었을 경우
		if ((tmp>0) && !strncmp(s + *p, "00", 2)) --(*p);

		return 1;
	}

	return 0;
}

void solution(){
	char s[201] = { 0, };
	int len, p = 0;
	char result = 1;

	scanf("%s", s);

	len = strlen(s);

	while (p<len){
		if (!startsWith(s, len, &p)){
			result = 0;
			break;
		}
	}

	printf("%s \n", result ? "YES" : "NO");
}

int main(){
	int T;

	scanf("%d", &T);

	for (int i=0; i<T; ++i) solution();

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

int po2(int n){
	int result = 1;

	for (int i=0; i<n; ++i) result *= 2;

	return result;
}

void solution(int r, int c, int sx, int sy, int len, int *count){
	if (len>2){
		if (r < sy+len/2){
			if (c < sx+len/2){
				solution(r, c, sx, sy, len/2, count);
			}else {
				*count += (len/2)*(len/2);
				solution(r, c, sx+len/2, sy, len/2, count);
			}
		}else {
			if (c < sx+len/2){
				*count += len/2*len;
				solution(r, c, sx, sy+len/2, len/2, count);
			}else {
				*count += len/4*len*3;
				solution(r, c, sx+len/2, sy+len/2, len/2, count);
			}
		}
	}else {
		for (int i=0; i<len; ++i){
			for (int j=0; j<len; ++j){
				if (r == sy+i && c == sx+j) return;
				(*count)++;
			}
		}
	}
}

int main(){
	int n, r, c;
	int *count;

	scanf("%d %d %d", &n, &r, &c);

	count = (int*)calloc(1, sizeof(int));

	int tmp = po2(n);

	solution(r, c, 0, 0, tmp, count);

	printf("%d \n", *count);

	free(count);

	return 0;
}
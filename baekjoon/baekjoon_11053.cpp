#include <stdio.h>
#include <stdlib.h>

short* initSeq(short n){
	short *seq = (short*)calloc(n, sizeof(short));

	for (short i=0; i<n; ++i) scanf("%hd", &seq[i]);

	return seq;
}

short binSearch(short *vTable, short value, short start, short end){
	short mid = (start+end)/2;

	if (vTable[mid] == value) return mid;

	if (end-start <= 1) return start;

	if (vTable[mid] > value) return binSearch(vTable, value, start, mid);

	return binSearch(vTable, value, mid, end);
}

void solution(short n){
	short *a = initSeq(n);
	short *lTable = (short*)calloc(n, sizeof(short));
	short *vTable = (short*)calloc(n, sizeof(short));
	short len = 0;

	lTable[0] = 1;
	vTable[len++] = a[0];

	for (short i=1; i<n; ++i){
		if (a[i] > vTable[len-1]){
			vTable[len++] = a[i];
			lTable[i] = len;
			continue;
		}

		short p = binSearch(vTable, a[i], 0, len);

		if (vTable[p] < a[i]){
			vTable[p+1] = a[i];
			lTable[i] = p+2;
			continue;
		}

		lTable[i] = p+1;

		if (vTable[p] > a[i]) vTable[p] = a[i];
	}

	printf("%hd \n", len);

	free(vTable);
	free(lTable);
	free(a);
}

int main(){
	short n;

	scanf("%hd", &n);

	solution(n);

	return 0;
}
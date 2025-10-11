#include <stdio.h>
#include <stdlib.h>

int* initCoins(short n){
	int *coins = (int*)calloc(n, sizeof(int));

	for (short i=0; i<n; ++i) scanf("%d", &coins[i]);

	return coins;
}

void printCoins(int *coins, short n){
	for (short i=0; i<n; ++i) printf("%d ", coins[i]);
	printf("\n");
}

void mergeSort(int *coins, short start, short end, short n){
	short len = end-start;

	if (len <= 1) return;

	short mid = (end+start)/2;

	mergeSort(coins, start, mid, n);
	mergeSort(coins, mid, end, n);

	int *tmp = (int*)calloc(len, sizeof(int));

	int fp=start, bp=mid;
	for (int i=0; i<len; ++i){
		if (fp>=mid){
			for (int j=i; j<len; ++j) tmp[j] = coins[bp++];
			break;
		}
		if (bp>=end){
			for (int j=i; j<len; ++j) tmp[j] = coins[fp++];
			break;
		}

		if (coins[bp]<coins[fp]) tmp[i] = coins[bp++];
		else tmp[i] = coins[fp++];
	}

	for (int i=0; i<end-start; ++i) coins[start+i] = tmp[i];

	free(tmp);
}

void solution(short n, short k){
	int *coins = initCoins(n);
	int *table = (int*)calloc(k, sizeof(int));

	mergeSort(coins, 0, n, n);

	for (short i=0; i<n; ++i){
		if (i>k) break;

		++table[coins[i]-1];

		for (short j=coins[i]; j<k; ++j){
			table[j] += table[j-coins[i]];
		}
	}

	printf("%d \n", table[k-1]);

	free(table);
	free(coins);
}

int main(){
	short n, k;

	scanf("%hd %hd", &n, &k);

	solution(n, k);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lamp {
	char pattern[51];
	char needson;
	char len;
};

char n, m, lampLen = 0;

Lamp* getLamp(){
	Lamp *lamps = (Lamp*)calloc(n, sizeof(Lamp));
	char tmp[51] = { 0, };

	for (char i=0; i<n; ++i){
		scanf("%s", tmp);

		char flag = -1;

		for (char j=0; j<lampLen; ++j){
			if (!strcmp(lamps[j].pattern, tmp)){
				flag = j;
				break;
			}
		}

		if (flag != -1){
			++lamps[flag].len;
		}else {
			strcpy(lamps[lampLen].pattern, tmp);
			for (char j=0; j<m; ++j){
				if (tmp[j] == '0') ++lamps[lampLen].needson;
			}
			++lamps[lampLen++].len;
		}
	}

	return lamps;
}

void solution(){
	short k;
	char max = 0;

	scanf("%hhd %hhd", &n, &m);

	Lamp *lamps = getLamp();

	scanf("%hd", &k);

	for (char i=0; i<lampLen; ++i){
		if (lamps[i].needson > k) continue;
		if ((k - lamps[i].needson) % 2) continue;

		max = max > lamps[i].len ? max : lamps[i].len;
	}

	printf("%hhd \n", max);

	free(lamps);
}

int main(){
	solution();

	return 0;
}
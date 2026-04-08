#include <stdio.h>
#include <stdlib.h>

short r, c;

struct Set {
	short ld;
	short rd;
};

char** getTable(){
	char **table = (char**)calloc(r, sizeof(char*));

	for (short i=0; i<r; ++i){
		table[i] = (char*)calloc(c+1, sizeof(char));
		scanf("%s", table[i]);
	}

	return table;
}

void freeTable(char **table){
	for (short i=0; i<r; ++i) free(table[i]);
	free(table);
}

Set** getDownInfo(char **table){
	Set **dt = (Set**)calloc(r, sizeof(Set*));
	for (short i=0; i<r; ++i) dt[i] = (Set*)calloc(c, sizeof(Set));

	for (short i=r-1; i>=0; --i){
		for (short j=0; j<c; ++j){
			if (table[i][j] == '0') continue;

			short ti = i, tj = j, count = 1;

			if (!dt[i][j].ld){
				while (ti >= 0 && tj < c){
					if (table[ti][tj] == '0') break;

					dt[ti--][tj++].ld = count++;
				}
			}
			if (!dt[i][j].rd){
				ti = i; tj = j; count = 1;
				while (ti >= 0 && tj >= 0){
					if (table[ti][tj] == '0') break;

					dt[ti--][tj--].rd = count++;
				}
			}
		}
	}

	return dt;
}

void freeDownInfo(Set **dt){
	for (short i = 0; i < r; ++i) free(dt[i]);
	free(dt);
}

void solution(){
	char **table;

	scanf("%hd %hd", &r, &c);

	table = getTable();

	Set **dt = getDownInfo(table);

	short max = 0;
	for (short i=0; i<r; ++i){
		for (short j=0; j<c; ++j){
			if (table[i][j] == '0') continue;

			Set *p = &dt[i][j];
			short min = p->ld < p->rd ? p->ld : p->rd;

			if (min <= max) continue;

			for (short k=min; k>max; --k){
				if (dt[i+k-1][j-k+1].rd < k) continue;
				if (dt[i+k-1][j+k-1].ld < k) continue;

				max = k;
				break;
			}
		}
	}

	printf("%hd \n", max);

	freeTable(table);
}

int main(){
	solution();

	return 0;
}
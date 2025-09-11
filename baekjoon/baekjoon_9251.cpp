#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solution(char *s1, char *s2){
	int s1Len = strlen(s1);
	int s2Len = strlen(s2);
	int **table = (int**)calloc(s1Len+1, sizeof(int*));
	for (int i=0; i<=s1Len; ++i) table[i] = (int*)calloc(s2Len+1, sizeof(int));

	for (int i=1; i<=s1Len; ++i){
		for (int j=1; j<=s2Len; ++j){
			if (s1[i-1] == s2[j-1]) {
				table[i][j] = table[i-1][j-1]+1;
				continue;
			}
			table[i][j] = (table[i-1][j] > table[i][j-1]) ? table[i-1][j] : table[i][j-1];
		}
	}

	printf("%d \n", table[s1Len][s2Len]);

	for (int i=0; i<=s1Len; ++i) free(table[i]);
	free(table);
}

int main(){
	char *s1 = (char*)calloc(1001, sizeof(char));
	char *s2 = (char*)calloc(1001, sizeof(char));

	scanf("%s", s1);
	scanf("%s", s2);

	solution(s1, s2);

	free(s2);
	free(s1);

	return 0;
}
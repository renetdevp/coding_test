#include <stdio.h>
#include <stdlib.h>

void initBox(char ***box, char m, char n, char h){
	for (char i=0; i<h; ++i){
		box[i] = (char**)calloc(n, sizeof(char*));
		for (char j=0; j<n; ++j) box[i][j] = (char*)calloc(m, sizeof(char));
	}
}

void inputBox(char ***box, char m, char n, char h){
	for (char i=0; i<h; ++i)
		for (char j=0; j<n; ++j)
			for (char k=0; k<m; ++k)
				scanf("%hhd", &box[i][j][k]);
}

void freeBox(char ***box, char m, char n, char h){
	for (char i=0; i<h; ++i){
		for (char j=0; j<n; ++j)
			free(box[i][j]);
		free(box[i]);
	}
	free(box);
}

void printBox(char ***box, char m, char n, char h){
	for (int i=0; i<h; ++i){
		for (int j=0; j<n; ++j){
			for (int k=0; k<m; ++k) printf("%hhd ", box[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
}

void solution(char ***box, char m, char n, char h){
	int *queue;
	char ***visited;
	char dx[] = { 0, 0, 0, 1, 0, -1 };
	char dy[] = { 0, 0, -1, 0, 1, 0 };
	char dz[] = { -1, 1, 0, 0, 0, 0 };
	int fp=0, bp=0, count=-1;

	queue = (int*)calloc(h*n*m, sizeof(int));

	for (char i=0; i<h; ++i)
		for (char j=0; j<n; ++j)
			for (char k=0; k<m; ++k)
				if (box[i][j][k] == 1)
					queue[bp++] = i*n*m + j*m + k;

	while (fp<bp){
		int tmp = bp;

		for (int i=fp; i<tmp; ++i){
			char sz = queue[i]/(m*n);
			char sy = (queue[i]%(m*n))/m;
			char sx = queue[i]%m;

			++fp;

			for (char j=0; j<6; ++j){
				char zp = sz+dz[j];
				char yp = sy+dy[j];
				char xp = sx+dx[j];

				if (zp<0 || zp>=h) continue;
				if (yp<0 || yp>=n) continue;
				if (xp<0 || xp>=m) continue;

				if (!box[zp][yp][xp]){
					queue[bp++] = zp*n*m + yp*m + xp;
					box[zp][yp][xp] = 1;
				}
			}
		}

		++count;
	}

	for (char i=0; i<h; ++i){
		for (char j=0; j<n; ++j){
			for (char k=0; k<m; ++k){
				if (!box[i][j][k]){
					printf("-1");

					free(queue);

					return;
				}
			}
		}
	}

	printf("%d \n", count);

	free(queue);
}

int main(){
	char ***box;
	char m, n, h;

	scanf("%hhd %hhd %hhd", &m, &n, &h);

	box = (char***)calloc(h, sizeof(char**));
	initBox(box, m, n, h);

	inputBox(box, m, n, h);

	solution(box, m, n, h);

	freeBox(box, m, n, h);

	return 0;
}
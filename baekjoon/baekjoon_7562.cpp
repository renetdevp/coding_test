#include <stdio.h>
#include <stdlib.h>

void freeAll(int **table, int l, int *queue){
	for (int i=0; i<l; ++i) free(table[i]);
	free(table);
	free(queue);
}

void solution(short l, short sy, short sx, short dy, short dx){
	char ty[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
	char tx[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int fp=0, bp=0, count=0;
	int **table = (int**)calloc(l, sizeof(int*));
	int *queue = (int*)calloc(l*l, sizeof(int));

	for (int i=0; i<l; ++i) table[i] = (int*)calloc(l, sizeof(int));

	queue[bp++] = sy*l+sx;
	table[sy][sx] = 0;
	while (fp<bp){
		int tmp = queue[fp++];

		if (tmp == dy*l+dx) break;

		for (int i=0; i<8; ++i){
			int ay=tmp/l+ty[i], ax=tmp%l+tx[i];

			if (ay<0 || ax<0) continue;
			if (ay>=l || ax>=l) continue;

			if (ay==dy && ax==dx){
				table[ay][ax] = table[tmp/l][tmp%l]+1;
				printf("%d \n", table[tmp/l][tmp%l]+1);
				freeAll(table, l, queue);
				return;
			}

			if (!table[ay][ax] && (ay!=sy || ax!=sx)){
				queue[bp++] = ay*l+ax;
				table[ay][ax] = table[tmp/l][tmp%l]+1;
			}
		}
	}

	printf("%d \n", table[dy][dx]);

	freeAll(table, l, queue);
}

int main(){
	int T;

	scanf("%d", &T);

	for (int i=0; i<T; ++i){
		short l, sy, sx, dy, dx;

		scanf("%hd", &l);
		scanf("%hd %hd", &sy, &sx);
		scanf("%hd %hd", &dy, &dx);

		solution(l, sy, sx, dy, dx);
	}

	return 0;
}
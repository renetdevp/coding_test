#include <stdio.h>
#include <stdlib.h>

struct Node {
	char n;
	char from;
	short sum;
	short y;
	short x;
};

struct Tetromino {
	char width;
	char height;
	char dy[3];
	char dx[3];
};

short** initPaper(short n, short m){
	short **paper = (short**)calloc(n, sizeof(short*));
	for (short i=0; i<n; ++i) paper[i] = (short*)calloc(m, sizeof(short));

	for (short i=0; i<n; ++i)
		for (short j=0; j<m; ++j)
			scanf("%hd", &paper[i][j]);

	return paper;
}

void freePaper(short **paper, short n){
	for (short i=0; i<n; ++i) free(paper[i]);
	free(paper);
}

Tetromino flipHorizontal(Tetromino tet){
	Tetromino result;

	result.width = -tet.width;
	result.height = tet.height;

	for (char i=0; i<3; ++i){
		result.dy[i] = tet.dy[i];
		result.dx[i] = -tet.dx[i];
	}

	return result;
}

Tetromino flipVertical(Tetromino tet){
	Tetromino result;

	result.width = tet.width;
	result.height = -tet.height;
	
	for (char i=0; i<3; ++i){
		result.dy[i] = -tet.dy[i];
		result.dx[i] = tet.dx[i];
	}

	return result;
}

Tetromino rotate(Tetromino tet){
	Tetromino result;

	result.width = -tet.height;
	result.height = tet.width;

	for (int i=0; i<3; ++i){
		result.dy[i] = tet.dx[i];
		result.dx[i] = -tet.dy[i];
	}

	return result;
}

Tetromino* initTetromino(){
	Tetromino *tet = (Tetromino*)calloc(27, sizeof(Tetromino));

	tet[0] = { 3, 0, {0, 0, 0}, {1, 2, 3} };
	tet[1] = { 0, 3, {1, 2, 3}, {0, 0, 0} };

	tet[2] = { 1, 1, {0, 1, 1}, {1, 0, 1} };

	tet[3] = { 1, 2, {1, 2, 2}, {0, 0, 1} };
	//tet[4] = { -2, 1, {0, 0, 1}, {-2, -1, -2} };
	//tet[5] = { -1, -2, {-2, -2, -1}, {-1, 0, 0} };
	//tet[6] = { 2, -1, {-1, 0, 0}, {2, 1, 2} };
	for (char i=0; i<3; ++i) tet[4+i] = rotate(tet[3+i]);
	tet[7] = flipHorizontal(tet[3]);
	for (char i=0; i<3; ++i) tet[8+i] = rotate(tet[7+i]);

	tet[11] = { 1, 2, {1, 1, 2}, {0, 1, 1} };
	for (char i=0; i<3; ++i) tet[12+i] = rotate(tet[11+i]);
	tet[15] = flipHorizontal(tet[11]);
	for (char i=0; i<3; ++i) tet[16+i] = rotate(tet[15+i]);

	tet[19] = { 2, 1, {0, 0, 1}, {1, 2, 1} };
	for (char i=0; i<3; ++i) tet[20+i] = rotate(tet[19+i]);
	tet[23] = flipHorizontal(tet[19]);
	for (char i=0; i<3; ++i) tet[24+i] = rotate(tet[23+i]);

	return tet;
}

short getMax(short **paper, Tetromino *tet, short n, short m, short y, short x){
	short max = 1<<15;

	for (char i=0; i<27; ++i){
		short yp = y+tet[i].height;
		short xp = x+tet[i].width;

		if (yp<0 || yp>=n) continue;
		if (xp<0 || xp>=m) continue;

		short tmp = paper[y][x];
		for (char j=0; j<3; ++j) tmp += paper[y+tet[i].dy[j]][x + tet[i].dx[j]];

		max = max>tmp ? max : tmp;
	}

	return max;
}

void solution(short n, short m){
	short **paper = initPaper(n, m);
	Tetromino *tet = initTetromino();
	short max = 1<<15;

	for (int i=0; i<n; ++i)
		for (short j=0; j<m; ++j){
			short result = getMax(paper, tet, n, m, i, j);
			max = max>result ? max : result;
		}

	printf("%hd \n", max);

	free(tet);
	freePaper(paper, n);
}

int main(){
	short n, m;

	scanf("%hd %hd", &n, &m);

	solution(n, m);

	return 0;
}
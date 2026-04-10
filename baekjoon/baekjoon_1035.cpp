// 내가 사용한 알고리즘은 조각을 한 칸씩 이동하며 구현한 방식이었지만,
// 아래의 링크에서 사용한 알고리즘은 '보드 위에 조각이 n개 놓인 경우의 수'에서 모든 조각이 이어지지 않은 경우를 제외하고
// 모든 조각이 이어진 경우를 대상으로 '현재 조각 n개'가 '보드 위에 놓인 조각 n개'에 이동할 수 있는 모든 경우의 수에 대한 멘헤튼 거리를 계산하고
// 그 최솟값을 저장하는 알고리즘임.
// 내가 구현한 코드는 296MB 정도를 사용하는 아주 비효율적인 코드였지만, 아래 링크의 솔루션은 2MB를 사용하는 보다 효율적인 알고리즘이라 눈에 띄었음
// https://www.acmicpc.net/source/104880087

#include <stdio.h>
#include <stdlib.h>

struct BoardInfo {
	int board;
	int depth;
};

char pieceLen = 0;

char** initBoard(){
	char **board = (char**)calloc(5, sizeof(char*));

	for (char i=0; i<5; ++i){
		board[i] = (char*)calloc(6, sizeof(char));
		scanf("%s", board[i]);
	}

	return board;
}

void freeBoard(char **board){
	for (char i=0; i<5; ++i) free(board[i]);
	free(board);
}

char bfs(int board){
	int position;
	for (char i=0; i<25; ++i){
		if (board & (1 << i)) {
			position = i;
			break;
		}
	}
	int visited = 1 << position;
	int pq[5] = { 0, };
	char qp = 0, ql = 0;
	char ny[4] = { -1, 0, 1, 0 };
	char nx[4] = { 0, 1, 0, -1 };

	pq[ql++] = position;

	while (qp < ql){
		position = pq[qp++];
		int y = position / 5;
		int x = position % 5;

		for (char i=0; i<4; ++i){
			if (y+ny[i] < 0 || y+ny[i] >= 5) continue;
			if (x+nx[i] < 0 || x+nx[i] >= 5) continue;

			int np = position + ny[i]*5 + nx[i];

			if (!(board & (1 << np))) continue;
			if (visited & (1 << np)) continue;

			pq[ql++] = np;
			visited |= 1 << np;
		}
	}

	return pieceLen == ql;
}

char checkTop(int position){ return position >= 5;}
char checkRight(int position){ return position%5 != 4; }
char checkBottom(int position){ return position < 20; }
char checkLeft(int position){ return position % 5; }

void solution(){
	char **board = initBoard();
	int qp = 0, ql = 0;
	char *visited = (char*)calloc(1<<25, sizeof(char));
	BoardInfo *queue = (BoardInfo*)calloc(1<<25, sizeof(BoardInfo));

	char (*checkFuncs[4])(int) = { checkTop, checkRight, checkBottom, checkLeft };
	char np[4] = { -5, 1, 5, -1 };

	int map = 0;
	for (char i=0; i<25; ++i){
		if (board[i/5][i%5] != '*') continue;
		
		queue[ql].board |= 1 << i;
		++pieceLen;
	}

	queue[ql++].depth = 0;

	while (qp < ql){
		BoardInfo p = queue[qp];

		if (bfs(p.board)) break;

		for (char i=0; i<25; ++i){
			if (!(p.board & (1 << i))) continue;

			for (char j=0; j<4; ++j){
				int nextPosition = i + np[j];

				if (checkFuncs[j](i) && !(p.board & (1 << nextPosition))){
					int nextBoard = (p.board & ~(1 << i)) | (1 << nextPosition);

					if (visited[nextBoard]) continue;
					
					queue[ql++] = {
						nextBoard,
						p.depth+1
					};

					visited[nextBoard] = 1;
				}
			}
		}

		++qp;
	}

	printf("%d \n", queue[qp].depth);

	free(queue);
	free(visited);
	freeBoard(board);
}

int main(){
	solution();

	return 0;
}
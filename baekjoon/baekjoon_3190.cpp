#include <stdio.h>
#include <stdlib.h>

struct Set {
	int x;
	char c;
};

struct Queue {
	int head;
	Set *arr;
};

struct Snake {
	int position;
	char direction;
	int length;
	int count;
};

void printBoard(int **board, int n){
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j) printf("%d ", board[i][j]);
		printf("\n");
	}
}

void move(int **board, Queue *queue, int l, Snake *snake, int n){
	int y = snake->position/n;
	int x = snake->position%n;

	char dy[4] = { -1, 0, 1, 0 };
	char dx[4] = { 0, 1, 0, -1 };

	while (1){
		y += dy[snake->direction];
		x += dx[snake->direction];

		if (y<0 || y>=n || x<0 || x>=n){
			//printf("collision \n");
			//printBoard(board, n);
			break;
		}

		if (board[y][x] == -1) ++(snake->length);
		
		if (board[y][x]>0 && snake->count - board[y][x] < snake->length) {
			//printf("self collision \n");
			//printBoard(board, n);
			break;
		}

		board[y][x] = ++(snake->count);
		snake->position = y*n+x;

		Set tmp = queue->arr[queue->head];
		if (tmp.x == snake->count){
			if (tmp.c == 'L') snake->direction = !snake->direction ? 3 : snake->direction-1;
			else if (tmp.c == 'D') snake->direction = (snake->direction+1)%4;

			++(queue->head);
		}
	}
}

void initQueue(Queue *queue, int l){
	queue->arr = (Set*)calloc(l, sizeof(Set));

	for (int i=0; i<l; ++i){
		Set tmp;

		scanf("%d %c", &tmp.x, &tmp.c);

		queue->arr[(queue->head)++] = tmp;
	}

	queue->head = 0;
}

void initSnake(int **board, Snake *snake){
	board[0][0] = 1;
	snake->position = 0;
	snake->direction = 1;
	snake->length = 1;
	snake->count = 0;
}

void initApple(int **board, int k){
	for (int i=0; i<k; ++i){
		int r, c;

		scanf("%d %d", &r, &c);

		board[r-1][c-1] = -1;
	}
}

// board: (-1)-apple, 0-nothing
// direction: 0-top, 1-right, 2-bottom, 3-left
void solution(int n){
	Queue *queue = (Queue*)calloc(1, sizeof(Queue));
	int **board = (int**)calloc(n, sizeof(int*));
	for (int i=0; i<n; ++i) board[i] = (int*)calloc(n, sizeof(int));
	Snake *snake = (Snake*)calloc(1, sizeof(Snake));
	int k, l;

	scanf("%d", &k);

	initApple(board, k);
	initSnake(board, snake);

	scanf("%d", &l);

	initQueue(queue, l);

	move(board, queue, l, snake, n);

	printf("%d \n", snake->count+1);

	free(snake);
	for (int i=0; i<n; ++i) free(board[i]);
	free(board);
	free(queue->arr);
	free(queue);
}

int main(){
	int n;

	scanf("%d", &n);

	solution(n);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Set {
	int rb;
	int bb;
};

struct Node {
	int rb;
	int bb;
	char rollTo;
	int n;
};

struct Queue {
	int head;
	int length;
	Node *arr;
};

struct Table {
	int rows;
	int columns;
	char **data;
};

void initTable(Table *table, int n, int m){
	table->rows = n;
	table->columns = m;
	table->data = (char**)calloc(n, sizeof(char*));
	for (int i=0; i<n; ++i) table->data[i] = (char*)calloc(m+1, sizeof(char));
}

void insert(Queue *queue, int rb, int bb, char rollTo, int n){
	Node newNode = { rb, bb, rollTo, n };

	queue->arr[(queue->length)++] = newNode;
}

Node pop(Queue *queue){
	if (queue->head >= queue->length){
		printf("queue empty \n");
		exit(-1);
	}

	return queue->arr[(queue->head)++];
}

// rollTo: 0-Top, 1-Right, 2-Bottom, 3-Left
Set roll(Table *table, int rb, int bb, char rollTo, int ob){
	char dy[4] = { -1, 0, 1, 0 };
	char dx[4] = { 0, 1, 0, -1 };

	int dxy = dy[rollTo]*table->columns + dx[rollTo];

	int rbp = rb;
	int bbp = bb;

	while (1){
		char done = 1;

		char rbValue = table->data[rbp/table->columns][rbp%table->columns];
		char bbValue = table->data[bbp/table->columns][bbp%table->columns];

		int nextRbp = rbp+dxy;
		int nextBbp = bbp+dxy;
	

		if (nextRbp<0 || nextRbp>=table->rows*table->columns){
			printf("newRbp overflow while roll() \n");
			exit(-2);
		}
		if (nextBbp<0 || nextBbp>=table->rows*table->columns){
			printf("newBbp overflow while roll() \n");
			exit(-2);
		}

		char nextRbValue = table->data[nextRbp/table->columns][nextRbp%table->columns];
		char nextBbValue = table->data[nextBbp/table->columns][nextBbp%table->columns];

		if (nextRbValue != '#' && rbValue != 'O'){
			rbp = nextRbp;
			done = 0;
		}
		if (nextBbValue != '#' && bbValue != 'O'){
			bbp = nextBbp;
			done = 0;
		}

		if (done) break;
	}

	if (rbp!=bbp || rbp==ob) return { rbp, bbp };

	// if roll-direction is right or bottom
	if (rollTo%3){
		if (rb<bb) rbp -= dxy;
		else bbp -= dxy;
	}else {
		if (rb>bb) rbp -= dxy;
		else bbp -= dxy;
	}

	return { rbp, bbp };
}

void bfs(Table *table, Set positions, int ob){
	Queue *queue = (Queue*)calloc(1, sizeof(Queue));
	queue->arr = (Node*)calloc(2<<11+1, sizeof(Node));

	for (char i=0; i<4; ++i) insert(queue, positions.rb, positions.bb, i, 0);

	while (queue->head < queue->length){
		Node data = pop(queue);

		Set newSet = roll(table, data.rb, data.bb, data.rollTo, ob);

		if (newSet.bb == ob) continue;

		if (newSet.rb == ob){
			printf("%d \n", data.n+1);

			free(queue->arr);
			free(queue);

			return;
		}

		if (data.n < 9)
			for (int i=0; i<4; ++i)
				if (i%2 != data.rollTo%2)
					insert(queue, newSet.rb, newSet.bb, i, data.n+1);
	}

	printf("-1 \n");

	free(queue->arr);
	free(queue);
}

void freeAll(Table *table){
	for (int i=0; i<table->rows; ++i) free(table->data[i]);
	free(table->data);
	free(table);
}

void solution(int n, int m){
	Table *table = (Table*)calloc(1, sizeof(Table));
	initTable(table, n, m);
	Set positions = { -1, -1 };
	int ob = -1;

	for (int i=0; i<n; ++i) scanf("%s", table->data[i]);

	for (int i=m; i<(n-1)*m; ++i){
		if (positions.rb!=-1 && positions.bb!=-1 && ob!=-1) break;

		char tmp = table->data[i/m][i%m];
		if (tmp == 'R') positions.rb = i;
		else if (tmp == 'B') positions.bb = i;
		else if (tmp == 'O') ob = i;
	}

	bfs(table, positions, ob);

	freeAll(table);
}

int main(){
	int n, m;

	scanf("%d %d", &n, &m);

	solution(n, m);

	return 0;
}
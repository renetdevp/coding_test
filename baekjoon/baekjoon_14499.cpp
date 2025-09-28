#include <stdio.h>
#include <stdlib.h>

struct Map {
	int n;
	int m;
	int **data;
};

struct Dice {
	int y;
	int x;

	int top;
	int bottom;
	int north;
	int east;
	int south;
	int west;
};

Map* initMap(int n, int m){
	Map *map = (Map*)calloc(1, sizeof(Map));

	map->n = n;
	map->m = m;
	map->data = (int**)calloc(n, sizeof(int*));
	for (int i=0; i<n; ++i) map->data[i] = (int*)calloc(m, sizeof(int));

	return map;
}

void freeMap(Map *map){
	for (int i=0; i<map->n; ++i) free(map->data[i]);
	free(map->data);
	free(map);
}

Dice* initDice(int x, int y){
	Dice *dice = (Dice*)calloc(1, sizeof(Dice));

	dice->x = x;
	dice->y = y;

	return dice;
}

void swapNum(Map *map, Dice *dice){
	if (map->data[dice->y][dice->x]){
		dice->bottom = map->data[dice->y][dice->x];
		map->data[dice->y][dice->x] = 0;
	}else map->data[dice->y][dice->x] = dice->bottom;
}

void roll2East(Map *map, Dice *dice){
	int tmp = dice->top;

	dice->top = dice->west;
	dice->west = dice->bottom;
	dice->bottom = dice->east;
	dice->east = tmp;
}

void roll2West(Map *map, Dice *dice){
	int tmp = dice->top;

	dice->top = dice->east;
	dice->east = dice->bottom;
	dice->bottom = dice->west;
	dice->west = tmp;
}

void roll2North(Map *map, Dice *dice){
	int tmp = dice->top;

	dice->top = dice->south;
	dice->south = dice->bottom;
	dice->bottom = dice->north;
	dice->north = tmp;
}

void roll2South(Map *map, Dice *dice){
	int tmp = dice->top;

	dice->top = dice->north;
	dice->north = dice->bottom;
	dice->bottom = dice->south;
	dice->south = tmp;
}

// rollTo: 1-right, 2-left, 3-north, 4-south
void roll(Map *map, Dice *dice, int rollTo){
	int dy[4] = { 0, 0, -1, 1 };
	int dx[4] = { 1, -1, 0, 0 };

	int y = dice->y + dy[rollTo-1];
	int x = dice->x + dx[rollTo-1];

	if (y<0 || y>=map->n) return;
	if (x<0 || x>=map->m) return;

	dice->y = y;
	dice->x = x;

	if (rollTo == 1) roll2East(map, dice);
	else if (rollTo == 2) roll2West(map, dice);
	else if (rollTo == 3) roll2North(map, dice);
	else if (rollTo == 4) roll2South(map, dice);
	else {
		printf("invalid rollTo in roll(): rollTo is %d \n", rollTo);
		exit(-2);
	}

	swapNum(map, dice);

	printf("%d \n", dice->top);
}

void solution(int n, int m, int x, int y, int k){
	Map *map = initMap(n, m);
	Dice *dice = initDice(x, y);
	int *queue = (int*)calloc(k, sizeof(int));

	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			scanf("%d", &map->data[i][j]);

	for (int i=0; i<k; ++i) scanf("%d", &queue[i]);

	int p = 0;
	while (p<k) roll(map, dice, queue[p++]);

	free(queue);
	free(dice);
	freeMap(map);
}

int main(){
	int n, m, x, y, k;

	scanf("%d %d %d %d %d", &n, &m, &y, &x, &k);

	solution(n, m, x, y, k);

	return 0;
}
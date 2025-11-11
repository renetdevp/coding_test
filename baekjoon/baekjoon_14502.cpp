#include <stdio.h>
#include <stdlib.h>

struct Map {
	char width;
	char height;
	char **data;
	char en;
	char *eQueue;
	char vn;
	char *vQueue;
};

Map* initMap(){
	Map *map = (Map*)calloc(1, sizeof(Map));
	char n, m;

	scanf("%hhd %hhd", &n, &m);

	map->width = m;
	map->height = n;
	map->data = (char**)calloc(n, sizeof(char*));
	map->eQueue = (char*)calloc(n*m, sizeof(char));
	map->vQueue = (char*)calloc(n*m, sizeof(char));

	for (char i=0; i<n; ++i){
		map->data[i] = (char*)calloc(m, sizeof(char));

		for (char j=0; j<m; ++j){
			scanf("%hhd", &map->data[i][j]);

			if (!map->data[i][j]) map->eQueue[map->en++] = i*map->width+j;
			else if (map->data[i][j] == 2) map->vQueue[map->vn++] = i*map->width+j;
		}
	}

	return map;
}

void freeMap(Map *map){
	free(map->eQueue);
	free(map->vQueue);
	for (char i=0; i<map->height; ++i) free(map->data[i]);
	free(map->data);
	free(map);
}

short bfs(Map *map, char i, char j, char k){
	char **visited = (char**)calloc(map->height, sizeof(char*));
	for (char i=0; i<map->height; ++i) visited[i] = (char*)calloc(map->width, sizeof(char));
	char *queue = (char*)calloc(map->height*map->width, sizeof(char));
	char ql = 0, qp = 0;

	for (char i=0; i<map->vn; ++i){
		char vp = map->vQueue[i];
		visited[vp/map->width][vp%map->width] = 1;
		queue[ql++] = vp;
	}
	visited[i/map->width][i%map->width] = 1;
	visited[j/map->width][j%map->width] = 1;
	visited[k/map->width][k%map->width] = 1;

	while (qp<ql){
		char dy[4] = { -1, 0, 1, 0 };
		char dx[4] = { 0, 1, 0, -1 };

		char vp = queue[qp++];

		for (char i=0; i<4; ++i){
			char vy = vp/map->width + dy[i];
			char vx = vp%map->width + dx[i];

			if (vy<0 || vy>=map->height) continue;
			if (vx<0 || vx>=map->width) continue;

			if (map->data[vy][vx]) continue;

			if (visited[vy][vx]) continue;

			visited[vy][vx] = 1;
			queue[ql++] = vy*map->width+vx;
		}
	}

	char result = 0;
	for (char i=0; i<map->height; ++i)
		for (char j=0; j<map->width; ++j)
			if (!visited[i][j] && !map->data[i][j]) ++result;

	free(queue);
	for (char i=0; i<map->height; ++i) free(visited[i]);
	free(visited);

	return result;
}

void solution(){
	Map *map = initMap();
	char max = -1;

	for (char i=0; i<map->en-2; ++i){
		for (char j=i+1; j<map->en-1; ++j){
			for (char k=j+1; k<map->en; ++k){
				// virus 전파 후 안전 영역 크기 계산
				short result = bfs(map, map->eQueue[i], map->eQueue[j], map->eQueue[k]);
				max = max>result ? max : result;
			}
		}
	}

	printf("%hhd \n", max);
}

int main(){
	solution();

	return 0;
}
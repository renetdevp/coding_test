#include <stdio.h>
#include <stdlib.h>

struct Robot {
	char y;
	char x;
	char direction;
};

struct Room {
	char height;
	char width;
	char **data;
};

char dy[4] = { -1, 0, 1, 0 };
char dx[4] = { 0, 1, 0, -1 };

Robot* initRobot(){
	Robot *robot = (Robot*)calloc(1, sizeof(Robot));

	scanf("%hhd %hhd %hhd", &robot->y, &robot->x, &robot->direction);

	return robot;
}

Room* initRoom(char height, char width){
	Room *room = (Room*)calloc(1, sizeof(Room));

	room->height = height;
	room->width = width;


	room->data = (char**)calloc(room->height, sizeof(char*));
	for (char i=0; i<room->height; ++i){
		room->data[i] = (char*)calloc(room->width, sizeof(char));
		for (char j=0; j<room->width; ++j) scanf("%hhd", &room->data[i][j]);
	}

	return room;
}

void freeRoom(Room *room){
	for (char i=0; i<room->height; ++i) free(room->data[i]);
	free(room->data);
	free(room);
}

void clean(Room *room, Robot *robot){
	room->data[robot->y][robot->x] = 2;
}

// 0: 주변 4칸에 청소할 곳이 없음, 1: 주변 4칸에 청소할 곳이 있음
char check(Room *room, Robot *robot){
	for (char i=0; i<4; ++i){
		char yp = robot->y + dy[i];
		char xp = robot->x + dx[i];

		if (yp<0 || yp>=room->height) continue;
		if (xp<0 || xp>=room->width) continue;

		if (room->data[yp][xp]) continue;

		return 1;
	}

	return 0;
}

// 0: 후진 불가, 1: 성공적으로 후진
char goBack(Room *room, Robot *robot){
	char yp = robot->y + dy[(robot->direction+2) % 4];
	char xp = robot->x + dx[(robot->direction+2) % 4];

	if (yp<0 || yp>=room->height) return 0;
	if (xp<0 || xp>=room->width) return 0;

	if (room->data[yp][xp] == 1) return 0;

	robot->y = yp;
	robot->x = xp;

	return 1;
}

void move(Room *room, Robot *robot){
	for (char i=0; i<4; ++i){
		robot->direction = (robot->direction+3)%4;

		char yp = robot->y + dy[robot->direction];
		char xp = robot->x + dx[robot->direction];

		if (yp<0 || yp>=room->height) continue;
		if (xp<0 || xp>=room->width) continue;

		if (!room->data[yp][xp]){
			robot->y = yp;
			robot->x = xp;
			break;
		}
	}
}

void solution(){
	char n, m;
	short result = 0;

	scanf("%hhd %hhd", &n, &m);

	Robot *robot = initRobot();
	Room *room = initRoom(n, m);

	while (1){
		if (!room->data[robot->y][robot->x]){
			clean(room, robot);
			++result;
		}

		if (!check(room, robot)){
			if (!goBack(room, robot)) break;
		}else move(room, robot);
	}

	printf("%hd \n", result);

	freeRoom(room);
	free(robot);
}

int main(){
	solution();

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Coord {
	short y;
	short x;
};

char crossProduct(Coord *coords){
	Coord v1 = { coords[1].y-coords[0].y, coords[1].x-coords[0].x };
	Coord v2 = { coords[2].y-coords[0].y, coords[2].x-coords[0].x };

	int z = (int)v1.x*v2.y - (int)v1.y*v2.x;

	if (z>0) return 1;
	else if (z<0) return -1;
	return 0;
}

void solution(){
	Coord *coords = (Coord*)calloc(3, sizeof(Coord));

	for (char i=0; i<3; ++i) scanf("%hd %hd", &coords[i].x, &coords[i].y);

	printf("%hd \n", crossProduct(coords));

	free(coords);
}

int main(){
	solution();

	return 0;
}
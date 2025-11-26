#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solution(){
	double min, max;
	int count = 0;

	scanf("%lf %lf", &min, &max);

	char *yesSquare = (char*)calloc(max-min+1, sizeof(char));

	for (double i=2; i*i <= max; ++i){
		double si = i*i;
		double quo = floor(min / si);

		for (double j = si * (quo == min/si ? quo : quo+1); j<=max; j+=si){
			yesSquare[(int)(j-min)] = 1;
		}
	}

	for (int i=0; i<=(max-min); ++i){
		if (!yesSquare[i]) ++count;
	}

	printf("%d \n", count);

	free(yesSquare);
}

int main(){
	solution();

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Set {
	char t;
	short p;
};

Set* initSchedule(char n){
	Set *schedule = (Set*)calloc(n, sizeof(Set));

	for (char i=0; i<n; ++i) scanf("%hhd %hd", &schedule[i].t, &schedule[i].p);

	return schedule;
}

//short getMax(Set *schedule, char p, char n){
//	if (p >= n) return 0;
//
//	if (p+schedule[p].t > n) return 0;
//
//	short max = schedule[p].p + getMax(schedule, p+schedule[p].t, n);
//	short result = getMax(schedule, p+1, n);
//
//	max = max>result ? max : result;
//
//	return max;
//}

short getMax(Set *schedule, char n){
	short *arr = (short*)calloc(n, sizeof(short));
	short result = -1;
	
	arr[n-1] = schedule[n-1].t>1 ? 0 : schedule[n-1].p;

	for (char i=n-2; i>=0; --i){
		if (i+schedule[i].t > n){
			arr[i] = arr[i+1];
			continue;
		}

		short tmp = schedule[i].p;
		if (i+schedule[i].t < n) tmp += arr[i+schedule[i].t];

		arr[i] = arr[i+1]>tmp ? arr[i+1] : tmp;
	}

	result = arr[0];
	free(arr);

	return result;
}

void solution(char n){
	Set *schedule = initSchedule(n);
	//short result = getMax(schedule, 0, n);
	short result = getMax(schedule, n);

	printf("%hd \n", result);

	free(schedule);
}

int main(){
	char n;

	scanf("%hhd", &n);

	solution(n);

	return 0;
}
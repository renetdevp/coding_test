#include <stdio.h>
#include <stdlib.h>

struct Set {
	int num;
	char l;
	char ops[4];
};

char* initNums(char n){
	char *nums = (char*)calloc(n, sizeof(char));

	for (char i=0; i<n; ++i) scanf("%hhd", &nums[i]);

	return nums;
}

char* initOps(){
	char *ops = (char*)calloc(4, sizeof(char));

	for (char i=0; i<4; ++i) scanf("%hhd", &ops[i]);

	return ops;
}

void enqueue(Set *queue, int ql, char l, int num, char *ops){
	queue[ql] = {
		num,
		l,
		{ ops[0], ops[1], ops[2], ops[3] }
	};
}

void solution(){
	char n;

	scanf("%hhd", &n);

	char *nums = initNums(n);
	char *ops = initOps();
	Set *queue = (Set*)calloc((4<<(2*n-2))+1, sizeof(Set));
	int qp=0, ql=0;

	enqueue(queue, ql++, 1, nums[0], ops);

	int max = 1<<31, min = ~(1<<31);
	while (qp<ql){
		Set tmp = queue[qp++];

		if (tmp.l >= n){
			max = max>tmp.num ? max : tmp.num;
			min = min<tmp.num ? min : tmp.num;
			continue;
		}

		for (char i=0; i<4; ++i){
			if (!tmp.ops[i]) continue;

			int result;

			if (!i) result = tmp.num+nums[tmp.l];
			else if (i == 1) result = tmp.num-nums[tmp.l];
			else if (i == 2) result = tmp.num*nums[tmp.l];
			else result = tmp.num/nums[tmp.l];

			// tmp.ops[i]를 소모한 값을 queue에 넣고, 이후 원래대로 되돌리는 동작
			--tmp.ops[i];
			enqueue(queue, ql++, tmp.l+1, result, tmp.ops);
			++tmp.ops[i];
		}
	}

	printf("%d \n%d \n", max, min);

	free(queue);
	free(ops);
	free(nums);
}

int main(){
	solution();

	return 0;
}
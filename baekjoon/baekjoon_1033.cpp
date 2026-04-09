#include <stdio.h>
#include <stdlib.h>

struct Data {
	char a, b, p, q;
};

struct Node {
	int len;
	int edges[10];
};

Node *nodes;
long long *result;

void insert(char a, char b){
	Node *pt = &nodes[a];

	pt->edges[pt->len++] = b;

	pt = &nodes[b];

	pt->edges[pt->len++] = a;
}

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a < b ? a : b;
}

int gcd(int a, int b){
	int maxp = max(a, b);
	int minp = min(a, b);

	while (minp){
		int p = maxp % minp;

		if (!p) break;

		maxp = minp;
		minp = p;
	}

	return minp;
}

long long lcm(int a, int b){
	return ((long long)a * (long long)b) / gcd(a, b);
}

void dfs(char p, int m, short affected){
	int len = nodes[p].len;
	int *edges = nodes[p].edges;

	for (int i=0; i<len; ++i){
		if (affected & (1 << edges[i])) continue;

		result[edges[i]] *= m;
		affected = affected | (1 << edges[i]);
		dfs(edges[i], m, affected);
	}
}

void solution(){
	char n;
	Data *table;
	
	scanf("%hhd", &n);

	result = (long long*)calloc(n, sizeof(long long));
	nodes = (Node*)calloc(n, sizeof(Node));
	table = (Data*)calloc(n-1, sizeof(table));

	for (char i=0; i<n-1; ++i){
		scanf("%hhd %hhd %hhd %hhd", &table[i].a, &table[i].b, &table[i].p, &table[i].q);

		int t = gcd(table[i].p, table[i].q);
		if (t != 1){
			table[i].p /= t;
			table[i].q /= t;
		}

		insert(table[i].a, table[i].b);
	}

	for (char i=0; i<n-1; ++i){
		char a = table[i].a;
		char b = table[i].b;
		char p = table[i].p;
		char q = table[i].q;

		// 둘 다 0일 경우 p와 q를 각각 대입
		if (!result[a] && !result[b]){
			result[a] = p;
			result[b] = q;

			continue;
		}

		// 둘 다 0이 아닌 경우
		if (result[a] && result[b]) {
			long long t = lcm(result[a], result[b]);

			dfs(a, p * t / result[a], 1<<a | 1<<b);
			result[a] = t * p;
			dfs(b, q * t / result[b], 1<<a | 1<<b);
			result[b] = t * q;

			continue;
		}

		// result[a] && !result[b]인 경우
		if (result[a]){
			long long t1 = lcm(result[a], p);

			dfs(a, t1/result[a], 1<<a | 1<<b);
			result[b] = t1/p * q;
			result[a] = t1;

			continue;
		}

		// !result[a] && result[b]인 경우
		long long t1 = lcm(result[b], q);

		dfs(b, t1/result[b], 1<<a | 1<<b);
		result[a] = t1/q * p;
		result[b] = t1;
	}

	// result의 최대공약수가 1이 아니라면 최대공약수로 나눈 값으로 result를 출력
	int tmp = result[0];
	for (char i=1; i<n; ++i){
		tmp = gcd(tmp, result[i]);
	}

	for (char i=0; i<n; ++i){
		if (tmp != 1) result[i] /= tmp;
		printf("%lld ", result[i]);
	}

	free(table);
	free(nodes);
	free(result);
}

int main(){
	solution();

	return 0;
}
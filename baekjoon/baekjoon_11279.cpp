#include <stdio.h>
#include <stdlib.h>

// 1-index
struct maxHeap {
	int *heap;
	int len;
};
typedef struct maxHeap MaxHeap;

void addElement(MaxHeap *mh, int elem){
	int i = ++mh->len;

	while (i>1 && (mh->heap[i/2] < elem)){
		mh->heap[i] = mh->heap[i/2];
		i /= 2;
	}

	mh->heap[i] = elem;
}

int delElement(MaxHeap *mh){
	if (mh->len < 1) return 0;

	int result = mh->heap[1];

	mh->heap[1] = mh->heap[mh->len--];

	int i=1;

	while (i<mh->len){
		int tmp = mh->heap[i];
		int max = mh->heap[i*2]>mh->heap[i*2+1] ? i*2 : i*2+1;
		max = i*2==mh->len ? i*2 : max;

		if (max <= mh->len && mh->heap[max] > tmp){
			mh->heap[i] = mh->heap[max];
			mh->heap[max] = tmp;
			i = max;
		}else break;
	}

	return result;
}

int main(){
	int n;
	MaxHeap *mh = (MaxHeap*)calloc(1, sizeof(MaxHeap));

	scanf("%d", &n);

	mh->heap = (int*)calloc(n+1, sizeof(int));

	for (int i=0; i<n; ++i){
		int tmp;

		scanf("%d", &tmp);

		if (tmp) addElement(mh, tmp);
		else printf("%d \n", delElement(mh));
	}

	free(mh->heap);
	free(mh);
}
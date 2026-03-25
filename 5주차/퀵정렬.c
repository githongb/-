#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
struct set {
	int a;
	int b;
};
int randpivot(int *p, int l, int r) {	// 중앙값 반환
	int a = rand() % (r - l + 1) + l;	// [l, r] 범위, rand() % (구간길이) + 시작점
	int b = rand() % (r - l + 1) + l;
	int c = rand() % (r - l + 1) + l;

	int x = p[a];
	int y = p[b];
	int z = p[c];

	if (x >= y && x <= z || x >= z && x <= y) return a;
	else if (y >= z && y <= x || y >= x && y <= z) return b;
	else return c;

}
void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}
struct set partition(int* p, int pivotindex, int l, int r) {
// a, b : 중복 범위		l, r : 시작과 끝 삽입 위치		j : 탐색 위치 
	int a = l;
	int b = r;
	int pivot = p[pivotindex];
	for (int j = l; j <= r; j++) {
		if (pivot > p[j]) {
			swap(&p[l], &p[j]);
			l++;
			a++;
		}
		else if (pivot < p[j]) {
			swap(&p[r], &p[j]);
			r--;
			j--;	// 제자리 다시 탐색
			b--;
		}
	}
	struct set set;
	set.a = a - 1;	// 경계값 조정
	set.b = b + 1;
	return set;
}
void inplacequicksort(int *p, int l, int r) {
	if (l >= r) {
		return;
	}
	int pivotindex = randpivot(p, l, r);
	struct set set = partition(p, pivotindex, l, r);
	inplacequicksort(p, l, set.a);
	inplacequicksort(p, set.b, r);
}
int main() {
	int n;
	int* p;
	scanf("%d", &n);
	p = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", p+i);
	}
	srand(time(NULL));	// 랜덤 난수 지정
	inplacequicksort(p, 0, n-1);
	
	for (int i = 0; i < n; i++) {
		printf(" %d", *(p + i));
	}

	return 0;
}

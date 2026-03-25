#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct graph {
	int vertices;
	int adj[100][100];
	int* visit;
} graph;

int n, m;
graph* g;

void setgraph() {
	g = malloc(sizeof(graph));
	g->vertices = n;
	g->visit = malloc(sizeof(int) * (n + 1));
	for (int i = 1; i < n + 1; i++) {
		g->visit[i] = 0;
		for (int j = 1; j < n + 1; j++) {
			g->adj[i][j] = 0;
		}
	}
}
void addedge(int start, int end, int k) {
	g->adj[start][end] = k;
	g->adj[end][start] = k;
}
void print() {
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			printf("%d ", g->adj[i][j]);
		}
		printf("\n");
	}
}
// 인접행렬 기반 O(n^2)
void prim() {
	int weight = 0;	// 가중치 합
	g->visit[1] = 1;	// 정점 1 방문 처리
	int min, index = 1, count = 0;
	printf(" %d", index);	// 정점출력

	while (count < n - 1) {	// 선택되는 간선 수 만큼 반복
		min = 100;
		for (int i = 1; i < n + 1; i++) {
			if (g->visit[i] == 1) {	// 방문한 노드 중에서
				for (int j = 1; j < n + 1; j++) {
					if (g->visit[j] == 0 && g->adj[i][j] != 0 && g->adj[i][j] < min) {	// 방문 하지 않고 가중치가 존재
						min = g->adj[i][j];	// 최소 가중치 저장
						index = j;	// 정점 인덱스 저장
					}
				}
			}
		}
		printf(" %d", index);	// 정점출력
		g->visit[index] = 1;	// 방문처리
		weight += min;	// 가중치 합
		count++;
	}
	printf("\n%d", weight);	// 총 가중치 출력
}
int main() {
	int k, start, end;
	scanf("%d %d", &n, &m);
	setgraph();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &k);
		addedge(start, end, k);
	}
	prim();


	return 0;
}

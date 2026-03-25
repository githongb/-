#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* next;
	int vertex;
} node;
typedef struct graph {
	int vertices;
	node** adj;
} graph;
int queue[100];	// 큐
int front = 0; int rear = 0;

graph* g;
int n, m;
int index_count = 0;
int char_to_index[256];	// 문자 -> 인덱스로 저장
char index_to_char[256];	// 인덱스에 해당하는 문자 저장
int in[100];


int getindex(char c) {	// 정점 문자 -> 숫자 변환
	if (char_to_index[c] == -1) {
		char_to_index[c] = index_count;
		index_to_char[index_count] = c;
		index_count++;
	}
	return char_to_index[c];
}
graph* setgraph() {	// 그래프 초기화
	graph* g = malloc(sizeof(graph));
	g->vertices = n;
	g->adj = malloc(sizeof(node*) * n);
	for (int i = 0; i < n; i++) {
		g->adj[i] = NULL;
		in[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		char_to_index[i] = -1;
	}
	return g;
}
node* getnode(char c) {	// 노드 생성
	node* newnode = malloc(sizeof(node));
	newnode->next = NULL;
	newnode->vertex = getindex(c);	// 정점을 숫자로 저장
	return newnode;
}
void addedge(char s, char e) {	// 간선 추가
	int start = getindex(s);
	int end = getindex(e);
	
	node* newnode = getnode(e);	// start 정점에 end 추가
	newnode->next = g->adj[start];
	g->adj[start] = newnode;

	in[end]++;	// 진입차수 갱신
}
void print() {	// 그래프 구조 출력
	for (int i = 0; i < n; i++) {
		node* p = g->adj[i];
		printf("\n");
			while (p != NULL) {
				printf("%d ", p->vertex);
				p = p->next;
		}

	}
}
// 큐 //
void enqueue(int k) {
	queue[rear++] = k;
}
int dequeue() {
	return queue[front++];
}
void topologicalsort() {	// 위상 정렬
	int count = 0;
	char result[100];	// 정렬값 저장

	for (int i = 0; i < n; i++) {	// 첫 0값 저장
		if (in[i] == 0) {
			enqueue(i);
		}
	}

	while (front != rear) {
		int k = dequeue();	// 큐 반환
		result[count++] = index_to_char[k];	// 결과로 저장

		node* p = g->adj[k];
		while (p != NULL) {	// 위상 갱신 후 0값 큐에 저장
			in[p->vertex]--;
			if (in[p->vertex] == 0) {
				enqueue(p->vertex);
			}
			p = p->next;
		}
	}

	if (count == n) {	// DAG면 출력
		for (int i = 0; i < n; i++) {
			printf("%c ", result[i]);
		}
	}
	else printf("0");	// 방향 싸이클 존재
}
int main() {
	char c, start, end;

	scanf("%d", &n);
	g = setgraph();
	for (int i = 0; i < n; i++) {
		scanf(" %c", &c);
		getindex(c);
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf(" %c %c", &start, &end);
		addedge(start, end);
	}

	topologicalsort();

	return 0;
}

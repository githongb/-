#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node{
	struct node* next;
	int key;
} node;
int m;

node* getnode(int key) {
	node* newnode = malloc(sizeof(node));
	newnode->key = key;
	newnode->next = NULL;
	return newnode;
}
int hash(int key) {	// 해쉬값
	return key % m;
}
void insertkey(node **table, int key) {
	int h = hash(key);
	node* newnode = getnode(key);
	newnode->next = table[h];
	table[h] = newnode;
}
int search(node** table, int key) {
	int h = hash(key);
	int k = 0;
	node* p = table[h];
	while (p != NULL) {
		k++;
		if (p->key == key) {
			return k;
		}
		p = p->next;
	}
	return 0;
}
int delkey(node **table, int key) {
	int h = hash(key);
	int k = 0;
	node* p = table[h];
	node* q = NULL;
	while (p != NULL) {
		k++;
		if (p->key == key) {
			if (q == NULL) {
				table[h] = p->next;
			}
			else {
				q->next = p->next;
			}
			free(p);
			return k;
		}
		q = p;
		p = p->next;
	}
	return 0;
}
void printkey(node **table) {
	node** p = table;
	for (int i = 0; i < m; i++) {
		if (p[i] != NULL) {
			node* q = p[i];
			while (q != NULL) {
				printf(" %d", q->key);
				q = q->next;
			}
		}
	}
	printf("\n");
}
int main() {
	int key;
	scanf("%d", &m);
	node** table = malloc(sizeof(node*) * m);	// 이중포인터 선언
	for (int i = 0; i < m; i++) {
		table[i] = NULL;  // 초기화
	}
	char c;
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertkey(table, key);
		}
		else if (c == 's') {
			scanf("%d", &key);
			printf("%d\n", search(table, key));
		}
		else if (c == 'd') {
			scanf("%d", &key);
			printf("%d\n", delkey(table, key));
		}
		else if (c == 'p') {
			printkey(table);
		}
		else if (c == 'e') {
			exit(0);
		}
	}
	
	return 0;
}

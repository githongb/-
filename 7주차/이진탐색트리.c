#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
typedef struct node {
	struct node* left;
	struct node* right;
	struct node* parent;
	int key;
} node;
node* getnode(int key, node* parent) {
	node* newnode = malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = parent;
	newnode->key = key;
	return newnode;
}
void insertitem(node **h, int key) {
	if (*h == NULL) {
		*h = getnode(key, NULL);
		return;
	}
	node* p = *h;
	if (p->key > key) {
		if (p->left == NULL) {
			p->left = getnode(key, p);
			return;
		}
		insertitem(&(p->left), key);
	}
	else {
		if (p->right == NULL) {
			p->right = getnode(key, p);
			return;
		}
		insertitem(&(p->right), key);
	}
}
node* search(node* h, int key) {
	if (h == NULL) return NULL;
	if (h->key == key) return h;
	if (h->key > key) {
		return search(h->left, key);
	}
	else {
		return search(h->right, key);
	}
}
node* findmin(node* p) {
	while (p->left != NULL) {
		p = p->left;
	}
	return p;
}
void delnode(node** h, node *p) {
	if (p->left == NULL && p->right == NULL) {
		if (p == *h) {
			*h = NULL;
		}
		else {
			if (p->parent->left == p) {
				p->parent->left = NULL;
			}
			else {
				p->parent->right = NULL;
			}
		}
		free(p);
	}
	else if (p->left == NULL || p->right == NULL){
		node* child = (p->left == NULL) ? p->right : p->left;
		if (p == *h) {
			*h = child;
		}
		else {
			if (p->parent->left == p) {
				p->parent->left = child;
			}
			else {
				p->parent->right = child;
			}
		}
		child->parent = p->parent;
		free(p);
	}
	else {
		node *q = findmin(p->right);
		p->key = q->key;
		delnode(h, q);
		return;
	}
}
void print(node *h) {
	if (h == NULL) return;
	printf(" %d", h->key);
	print(h->left);
	print(h->right);
}
int main() {
	char c;
	int key;
	node* h = NULL;
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertitem(&h, key);
		}
		else if (c == 'd') {
			scanf("%d", &key);
			node *p = search(h, key);
			if (p != NULL) {
				printf("%d\n", p->key);
				delnode(&h, p);
			}
			else {
				printf("X\n");
			}
		}
		else if (c == 's') {
			scanf("%d", &key);
			node* p = search(h, key);
			if (p == NULL) {
				printf("X\n");
			}
			else {
				printf("%d\n", p->key);
			}
		}
		else if (c == 'p') {
			print(h);
			printf("\n");
		}
		else if (c == 'q') {
			exit(0);
		}
	}
	return 0;
}

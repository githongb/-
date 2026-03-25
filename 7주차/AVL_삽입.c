#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#pragma warning (disable:4996)
node* search(node* root, int key);	//탐색
node* getnode(int key, node* parent);
int getheight(node* root);				//높이 반환
void updateheight(node* root);			//높이 갱신
int getbalance(node* root);				//균형도
void rotate_left(node** root);			//회전
void rotate_right(node** root);
void rebalance(node** root);			//균형잡기
void insertnode(node** root, int key);	//삽입

typedef struct node {
	struct node* left;
	struct node* right;
	struct node* parent;
	int key;
	int height;	// 높이 추가
} node;
node* getnode(int key, node* parent) {
	node* newnode = malloc(sizeof(node));
	newnode->key = key;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = parent;
	newnode->height = 1;	// 높이 초기화
	return newnode;
}
//////////////////////////////////////////////////////////////////
int getheight(node *root) {	// 높이 반환
	if (root == NULL) return 0;
	return root->height;
}
void updateheight(node *root) {	// 높이 갱신
	if (root == NULL) return;
	int a = getheight(root->left);
	int b = getheight(root->right);
	root->height = 1 + ((a > b) ? a : b);	// 왼쪽과 오른쪽 높이중 더 큰값 + 1
}
int getbalance(node *root) {	// 균형체크
	if (root == NULL) return 0;
	return getheight(root->left) - getheight(root->right);	// 높이 차이 반환 -> 균형측정
}
void rotate_left(node** root) { //  왼쪽으로 회전
	node* down = *root;	// 내려갈 노드
	node* up = (*root)->right;	// 올라갈 노드
	
	if (up->left) {	//up의 왼쪽노드가 존재하면 -> down의 오른쪽 노드로 이동
		down->right = up->left;
		up->left->parent = down;
	}
	else down->right = NULL; //없으면 down의 오른쪽은 null

	up->left = down;	//up올리고 down내리기
	up->parent = down->parent;
	down->parent = up;

	updateheight(down);	// 높이 갱신
	updateheight(up);

	*root = up; //루트 연결
}
void rotate_right(node** root) {	//오른쪽으로 회전
	node* down = *root;
	node* up = (*root)->left;

	if (up->right) {
		down->left = up->right;
		up->right->parent = down;
	}
	else down->left = NULL;

	up->right = down;
	up->parent = down->parent;
	down->parent = up;

	updateheight(down);
	updateheight(up);

	*root = up;
}
void rebalance(node **root) {
	updateheight(*root);	// 높이 업데이트
	int balance = getbalance(*root);	//균형도

	if (balance > 1) {	// L
		if (getbalance((*root)->left) > 0) {	// LL
			rotate_right(root);
		}
		else {	//LR
			rotate_left(&((*root)->left));	// 회전 두번
			rotate_right(root);
		}
	}
	else if (balance < -1) {	// R
		if (getbalance((*root)->right) > 0) {	// RL
			rotate_right(&((*root)->right));
			rotate_left(root);
		}
		else {	//RR
			rotate_left(root);
		}
	}
}
void insertnode(node **root, int key) {
	if (*root == NULL) {
		*root = getnode(key, NULL);
		return;
	}
	if ((*root)->key > key) {
		if ((*root)->left == NULL) {
			(*root)->left = getnode(key, (*root));
		}
		else insertnode(&(*root)->left, key);
	}
	else if ((*root)->key < key) {
		if ((*root)->right == NULL) {
			(*root)->right = getnode(key, (*root));
		}
		else insertnode(&(*root)->right, key);
	}
	rebalance(root);	// 균형잡기, 삽입한 노드부터 올라가며 실행
}
///////////////////////////////////////////////////////////////////
node* search(node *root, int key) {
	if (root == NULL) return NULL;
	if (root->key == key) return root;
	if (root->key > key) return search(root->left, key);
	else return search(root->right, key);
}
void preorder(node *root) {
	if (root == NULL) return;
	printf(" %d", root->key);
	preorder(root->left);
	preorder(root->right);
}

int main() {
	char c;
	int key;
	node* root = NULL;
	while (1) {
		scanf(" %c", &c);
		if (c == 'i') {
			scanf("%d", &key);
			insertnode(&root, key);
		}
		else if (c == 's') {
			scanf("%d", &key);
			node* p = search(root, key);
			if (p == NULL)	printf("X\n");
			else printf("%d\n", p->key);
		}
		else if (c == 'p') {
			preorder(root);
			printf("\n");
		}
		else if (c == 'q') {
			exit(0);
		}
	}

	
	return 0;
}

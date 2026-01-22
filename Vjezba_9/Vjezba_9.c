#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tree;
typedef struct tree* ptree;
typedef struct tree {
	int num;
	ptree right;
	ptree left;
}tree;

ptree create(int);
ptree insert(ptree, int);
int inorder(ptree,FILE*);
int replace(ptree);
int deleteTree(ptree);

int main() {

	srand(time(NULL));

	ptree root = NULL;
	for (int i = 0; i < 10; i++) {
		root = insert(root, rand() % (91 - 10) + 10);
	}

	FILE* fp = NULL;
	fp = fopen("stablo.txt", "w");
	if (fp == NULL) {
		printf("Pogreska u otvaranju");
		return 1;
	}


	root = insert(root, 2);
	insert(root, 5);
	insert(root, 1);
	insert(root, 7);
	insert(root, 4);
	insert(root, 8);
	insert(root, 2);
	insert(root, 11);
	insert(root, 7);
	insert(root, 3);

	inorder(root,fp);
	replace(root);
	printf("\n");
	inorder(root,fp);


	return 0;
}

ptree create(int value) {
	ptree newNode = (ptree)malloc(sizeof(tree));
	newNode->num = value;
	newNode->right = NULL;
	newNode->left = NULL;
	return newNode;
}

ptree insert(ptree root, int value) {
	if (root == NULL) {
		return create(value);
	}

	if (value < root->num) {
		root->left = insert(root->left, value);
	}

	else if (value > root->num) {
		root->right = insert(root->right, value);
	}

	return root;
}

int replace(ptree root) {
	if (root == NULL) return 0;
	int data = root->num;
	root->num = replace(root->left) + replace(root->right);
	return data + root->num;
}

int inorder(ptree root,FILE* fp) {
	if (root != NULL) {
		inorder(root->left,fp);
		fprintf(fp, "%d ", root->num);
		inorder(root->right,fp);
		return 0;
	}
	else return 1;
}

int deleteTree(ptree root) {
	if (root == NULL) return 0;

	deleteTree(root->left);
	deleteTree(root->right);
	free(root);

	return 0;
}
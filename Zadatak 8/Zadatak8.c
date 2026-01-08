#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct tree;
typedef struct tree* p;
typedef struct tree {
	int data;
	p left;
	p right;
}tree;

p insert(p root, int a);
p search(p root, int a);
int printInorder(p root);
int printPreorder(p root);
int printPostorder(p root);
p deleteElement(p root, int x);
int freeTree(p root);


int main(){

	p root = NULL;
	int c;

	do {
		printf("1-insert,2-search,3-inorder,4-preorder,5-postorder,6-delelement,0-out\n");
		int value;

		switch (c) {
		case 1:
			scanf("%d", &value);
			insert(root, value);
			break;
		case 2:
			scanf("%d", &c);
			if (search(root, value))
				printf("found");
			else
				printf("not found");

			break;
		case 3:
			printInorder(root);
			printf("\n");
			break;
		case 4:
			printPreorder(root);
			printf("\n");
			break;
		case 5:
			printPostorder(root);
			printf("\n");
			break;
		case 6:
			printf("what number do you want to delete?");
			scanf("%d", &value);
			deleteElement(root, value);
			break;
	}
	} while (c != 0);
	

	freeTree(root);

	return 0;
}


p insert(p root,int a) {
	if (root == NULL) {
		root = (p)malloc(sizeof(tree));

		root->data = a;
		root->left = NULL;
		root->right = NULL;
	}
	else if (a < root->data)
		insert(root->left, a);
	else if (a > root->data)
		insert(root->right, a);

	return 0;
}

p search(p root, int a) {
	if (root == NULL) {
		printf("%d not found.\n", a);
		return NULL;
	}
	else if (a < root->data)
		return search(root->left, a);
	else if (a > root->data)
		return search(root->left, a);
}

int printInorder(p root) {
	if (root == NULL)
		return 0;

	printInorder(root->left);
	printf("%d ", root->data);
	printInorder(root->right);
	return 0;
}

int printPreorder(p root) {
	if (root == NULL)
		return 0;

	printf("%d ", root->data);
	printPreorder(root->left);
	printPreorder(root->right);
	return 0;
}

int printPostorder(p root) {
	if (root == NULL)
		return 0;

	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ", root->data);
	return 0;
}

p deleteElement(p root, int x)
{
	if (root == NULL) {
		printf("Element not found.\n");
		return NULL;
	}

	if (x < root->data) root->left = deleteElement(root->left, x);
	else if (x > root->data) root->right = deleteElement(root->right, x);

	else {
		p temp = root;

		if (root->left == NULL) root = root->right; 
		else root = root->left; 

		free(temp);
	}

	return root;
}

int freeTree(p root) {
	if (root == NULL)
		return 0;

	freeTree(root->left);
	freeTree(root->right);
	free(root);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory;
typedef struct directory* p;
typedef struct directory {
	char name[20];
	p subdir;
	p next;
}dir;

struct stack;
typedef struct stack* ps;
typedef struct stack {
	p dirlevel;
	ps next;
}stack;


p createdir(char* dirname);
int adddir(p fatherdir, p sondir);
int push(ps, p);
int pop(ps);
int changeDirectory(ps, char*);
int printDirectory(p, int);

int main() {
	dir headdir = { .name = 0, .subdir = NULL, .next = NULL };
	char dirname[30];
	stack headstack = { .dirlevel = NULL, .next = NULL };

	printf("1-make, 2-change,3-goparent,4-view,5-end\n");
	int input;

	do {
		scanf("%d", &input);
		switch (input) {
		case 1:
			scanf("%s", dirname);
			p newdir = createdir(dirname);
			adddir(headstack.next->dirlevel, newdir);
			break;
		case 2:
			changeDirectory(&headstack, dirname);
		case 3:
			pop(&headstack);
		case 4:
			print("%s", headstack.next->dirlevel->name);
			break;
		}
	} while (input != 5);
	return 0;
}

p createdir(char* dirname) {
	p newdir = NULL;
	newdir = (p)malloc(sizeof(dir));

	if (newdir = NULL) return NULL;

	strcpy(newdir->name, dirname);
	newdir->next = NULL;

	return newdir;
}

int adddir(p fatherdir, p sondir) {
	
	sondir->next = fatherdir->subdir;
	fatherdir->subdir = sondir;

}

int push(ps headstack, p curdir) {
	ps newstack = NULL;
	newstack = (ps)malloc(sizeof(stack));

	newstack -> dirlevel = curdir;
	newstack->next = headstack->next;
	headstack->next = newstack;

	return 0;
}

int pop(ps headstack) {
	ps temp;

	temp = headstack->next;
	headstack->next = headstack->next->next;
	free(temp);

	return 0;
}

int changeDirectory(ps headstack, char* dirname) {

	p current = headstack->next->dirlevel->subdir;

	while (current != NULL && strcmp(current->name, dirname) != 0) current = current->next;

	if (current != NULL) {
		printf("Changed directory to %s\n", dirname);
		push(headstack, current);
	}
	else printf("Directory not found.\n");

	return 0;
}

int printDirectory(p current, int depth) {

	int i = 0;
	p currentSubdirectory = NULL;

	if (current->subdir != NULL) {
		currentSubdirectory = current->subdir;
		while (currentSubdirectory != NULL) {
			for (i = 0; i < depth; i++)
				printf(" ");
			printf("%s\n", currentSubdirectory->name);
			printDirectory(currentSubdirectory, depth + 1);
			currentSubdirectory = currentSubdirectory->next;
		}
	}

	return 0;
}

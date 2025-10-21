#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct person* P;
struct person {
	char name[15];
	char surname[30];
	int date_of_birth;

	P next;
};

P create();
P getinfo();
P add_in_front(P new_person);
void print(P head);


int main(void) {
	
	P head = NULL;
	P p1, p2, p3;

	head = add_in_front(head);
	head = add_in_front(head);
	head = add_in_front(head);

	print(head);






	return 0;
}


P create() {
	P new_person = (P)malloc(sizeof(struct person));
	if (new_person == NULL) {
		printf("Mistake in allocation\n");
		return NULL;
	}

	new_person->name[0] = '0';
	new_person->surname[0] = '0';
	new_person->date_of_birth = 0;
	new_person->next = NULL;

	return new_person;
}

P getinfo() {
	P new_person = create();
	printf("Enter name\n");
	scanf("%14s", new_person->name);
	printf("Enter surname\n");
	scanf("%29s", new_person->surname);
	printf("Enter year of birth :\n");
	scanf("%d", &new_person->date_of_birth);
	return new_person;


}

P add_in_front(P head) {
	P new_person = getinfo();
	new_person->next = head;
	return new_person;
}

void print(P head) {
	P start = head;
	while (start != NULL) {
		printf("%s %s %d\n", start->name, start->surname, start->date_of_birth);

		start = start->next;
	}


}






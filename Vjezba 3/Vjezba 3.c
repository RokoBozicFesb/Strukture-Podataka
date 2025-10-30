#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person;							//kreiranje strukture i pokazivaca P za strukturu
typedef struct person* P;
struct person {
	char name[15];
	char surname[30];
	int date_of_birth;

	P next;
};

P create();									//deklaracija funckija
P getinfo();
P add_in_front(P);
P add_in_back(P);
P add_in_front_of(P,char*);
P add_in_back_of(P,char*);
P delete_from_list(P, char*);
int find_in_list(P, char*);
void print(P);

int main(void) {

	P head = NULL;
	int choice;
	char surname1;
	printf("IZBORNIK\n");


	do {
		printf("1 add to front,2 add to back, 3 remove from list, 4 find person, 5 print, 6 exit\n");
		scanf("%d", &choice);



		switch (choice) {
		case 1: head = add_in_front(head);
			break;
		case 2:
			head = add_in_back(head);
			break;
		case 3:
			print("Unesi prezime osobe za izbrisati: \n");
			scanf("%s", &surname1);
			if (delete_from_list(head, surname1) == NULL) {
				printf("Nema upisanih ljudi\n");
				return 1;
			}
			break;
		case 4:
			printf("Unesi prezime osobe za pronaci"); scanf("%s", &surname1);
			if (find_in_list(head, surname1) == 1) {
				printf("Nema te ososbe");
				return 1;
			}
			break;
		case 5:
			print(head);
		}
	} while (choice != 6);

	return 0;
}


P create() {																//kreiranje nove osobe
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

P getinfo() {															//getinfo koristi funckiju za kreiranje osobe
	P new_person = create();											//time korisnik moze odluciti hoce li kreirati praznu osobu
	printf("Enter name\n");												//ili moze odrediti
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

P add_in_back(P head) {
	P new_person = getinfo();
	P temp = head;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = new_person;

	return head;

}

void print(P head) {
	P start = head;
	while (start != NULL) {
		printf("%s %s %d\n", start->name, start->surname, start->date_of_birth);

		start = start->next;
	}
}

P delete_from_list(P head, char* surname) {
	P temp = head;
	P previous = NULL;

	while (temp != NULL && strcmp(temp->surname, surname) != 0) {
		previous = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("Greska! Ne postoji osoba s tim imenom!\n");
		free(temp);
		return head;
	}

	if (previous == NULL) {
		head = temp->next;
	}
	else {
		previous->next = temp->next;
	}

	free(temp);
	return head;
}


int find_in_list(P head, char* surname) {
	if (head == NULL) {
		return 1;
	}
	P temp = head;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			printf("Pronada je osoba: %s %s\n rodena %d\n", temp->name, temp->surname, temp->date_of_birth);
			return 0;
		}
		temp = temp->next;
	}
	return 1;
}

P add_in_front_of(P head, char* surname) {
	P temp = head;
	P prev = NULL;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			P new_person = create();
			if (new_person == NULL) {
				return head;
			}
			if (prev == NULL) {
				new_person->next = head;
				return new_person;
			}
			prev->next = new_person;
			new_person->next = temp;
			return head;
		}
		prev = temp;
		temp = temp->next;
	}
	return head;
}

P add_behind_of(P head, char* surname) {
	P temp = head;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			P new_person = create();
			new_person->next = temp->next;
			temp->next = new_person;
		}
		temp = temp->next;
	}

	return head;
}






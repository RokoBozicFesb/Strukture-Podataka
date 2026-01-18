#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct citytree;
typedef struct citytree* citytreeP;
typedef struct citytree {
	int population;
	char name[25];
	citytreeP left;
	citytreeP right;
}citytree;

struct country;
typedef struct country* countryP;
typedef struct country {
	char name[25];
	countryP next;
	citytreeP city;
}country;

struct city;
typedef struct city* cityP;
typedef struct city {
	int population;
	char name[25];
	cityP next;
}city;


struct countrytree;
typedef struct countrytree* countrytreeP;
typedef struct countrytree {
	char name[25];
	countrytreeP left;
	countrytreeP right;
	cityP city;
}countrytree;


countryP addtocountry(countryP, char*);
citytreeP addcitytree(citytreeP root, char*, int);
int printlist(countryP);
int printcities(citytreeP);
countrytreeP addcountrytree(countrytreeP, char*);
cityP addcity(cityP, char*, int);
countrytreeP addcitytocountry(countrytreeP, char*, char*,int);
int printtree(countrytreeP);
int printcities1(cityP);
int printhigher(citytreeP root, int pop);




int main() {

	char buffer[256];
	char buffer2[256];
	char* tokens[2] = { NULL };
	countryP head = NULL;
	countrytreeP root = NULL;

	FILE* f1 = fopen("drzave.txt", "r");
	if (f1 == NULL) {
		printf("pogreska u otvaranju filea1");
	}
	while (fgets(buffer, sizeof(buffer), f1) != NULL) {
		tokens[0] = strtok(buffer, ",");
		tokens[1] = strtok(NULL, "  \n");
		head = addtocountry(head, tokens[0]);
		root = addcountrytree(root, tokens[0]);

		FILE* f2 = fopen(tokens[1], "r");
		if (f2 == NULL) {
			printf("pogreska u otvaranju filea2");

		}

		while (fgets(buffer2, sizeof(buffer2), f2) != NULL) {
			char* cityName = strtok(buffer2, ",");
			char* population = strtok(NULL, ",");


			int pop = atoi(population);
			countryP p = head;
			countrytreeP q = root;
			while (p->next != NULL) {
				p = p->next;
			}
			p->city = addcitytree(p->city, cityName, pop);
		    addcitytocountry(root, tokens[0], cityName, pop);
		}
		fclose(f2);
	}

	fclose(f1);

	printlist(head);
	printtree(root);

	printf("\nUnesi drzavu koju zelis pretraziti,pripazi na veliko slovo\n");
	char drzava[25];
	int stanovnici;
	scanf("%s", drzava);
	printf("\nUnesi broj stanovnika\n");
	scanf("%d", &stanovnici);
	countryP temp = head;
	while (temp != NULL && strcmp(temp->name, drzava) != 0) {
		temp = temp->next;
	}

	if (temp == NULL) {
		printf("drzava nije pronadzena");
	}
	else {
		printf("svi gradovi drzave koji imaju veci broj stanovnika od vaseg unosa\n ");
		printhigher(temp->city, stanovnici);
	}

	


	return 0;
}


countryP addtocountry(countryP head, char* namebuffer) {
	countryP newcountry = (countryP)malloc(sizeof(country));
	if (newcountry == NULL) {
		printf("pogresna alokacija memorije");
		return head;
	}
	strcpy(newcountry->name, namebuffer);
	newcountry->next = NULL;
	newcountry->city = NULL;

	if (head == NULL || strcmp(namebuffer, head->name) < 0) {
		newcountry->next = head;
		return newcountry;
	}

	countryP p = head;
	while (p->next != NULL && strcmp(namebuffer, p->next->name) > 0) {
		p = p->next;
	}
	newcountry->next = p->next;
	p->next = newcountry;



	return head;
}

citytreeP addcitytree(citytreeP root, char* names, int numpopulation) {

	if (root == NULL) {
		citytreeP newcity = (citytreeP)malloc(sizeof(citytree));
		strcpy(newcity->name, names);
		newcity->population = numpopulation;
		newcity->left = newcity->right = NULL;
		return newcity;
	}

	if (strcmp(names, root->name) < 0) {
		root->left = addcitytree(root->left, names, numpopulation);
	}
	else {
		root->right = addcitytree(root->right, names, numpopulation);
	}
	return root;

}


int printlist(countryP head) {
	countryP q = head;

	while (q != NULL) {
		printf("%s\n", q->name);
		printcities(q->city);
		printf("\n\n");
		q = q->next;
	}

	return 0;
}

int printcities(citytreeP root) {
	if (root == NULL) {
		return 1;
	}

	printcities(root->left);
	printf("%s %d\n", root->name, root->population);
	printcities(root->right);

	return 0;
}

countrytreeP addcountrytree(countrytreeP root, char* name1) {
	if (root == NULL) {
		countrytreeP newroot = (countrytreeP)malloc(sizeof(countrytree));
		strcpy(newroot->name, name1);
		newroot->right = NULL;
		newroot->left = NULL;
		newroot->city = NULL;
		return newroot;
	}
	if (strcmp(name1, root->name) < 0) {
		root->left = addcountrytree(root->left, name1);
	}
	else {
		root->right = addcountrytree(root->right, name1);
	}
	return root;
}

cityP addcity(cityP head, char* name1, int pop) {
	cityP newcity = (cityP)malloc(sizeof(city));
	if (newcity == NULL) {
		return head;
	}
	strcpy(newcity->name, name1);
	newcity->population = pop;
	newcity->next = NULL;

	if (head == NULL) {
		return newcity;
	}

	cityP p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newcity;

	return head;
}

countrytreeP addcitytocountry(countrytreeP root,char* countryname,char *cityname,int pop){
	if (root == NULL) {
		return NULL;
	}
	int temp = strcmp(countryname, root->name);

	if (temp == 0) {
		root->city = addcity(root->city, cityname, pop);
		return root;
	}
	else if (temp < 0) {
		return addcitytocountry(root->left, countryname, cityname, pop);
	}
	else {
		return addcitytocountry(root->right, countryname, cityname, pop);
	}

}

int printtree(countrytreeP root) {
	if (root == NULL) {
		return 1;
	}

	printtree(root->left);
	printf("%s\n", root->name);
	printcities1(root->city);
	printf("\n");
	printtree(root->right);

	return 0;
}

int printcities1(cityP head) {
	cityP p = head;
	while (p != NULL) {
		printf("%s %d\n", p->name, p->population);
		p = p->next;
	}

	return 0;
}

int printhigher(citytreeP root, int pop) {
	if (root == NULL) {
		return 0;
	}
	printhigher(root->left, pop);

	if (root->population > pop) {
		printf("%s %d\n", root->name, root->population);
	}
	printhigher(root->right, pop);

	return 0;
}




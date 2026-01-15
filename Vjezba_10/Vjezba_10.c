#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city;
typedef struct city* cityP;
typedef struct city {
	int population;
	char name[25];
	cityP left;
	cityP right;
}city;


struct country;
typedef struct country* countryP;
typedef struct country {
	char name[25];
	char namefile[25];
	countryP next;
	cityP city;
}country;

struct cityList;
typedef struct cityList* cityListP;
typedef struct cityList {
	int population;
	char name[20];
	cityListP next;
};

countryP addtolist(countryP,char*,char*);
void printCities(cityP root);
cityP insertCity(cityP, char*, int);


int main() {
	char countryName[25], cityFileName[25];
	countryP head = NULL;


	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) {
		printf("File drzave.txt not found!\n");
		return 1;
	}


	while (fscanf(fp, "%24s %24s", countryName, cityFileName) == 2) {
		head = addtolist(head, countryName, cityFileName);
	}

	fclose(fp);

	
	countryP current = head;
	while (current) {
		FILE* cityfp = fopen(current->namefile, "r");
		if (!cityfp) {
			printf("City file %s not found for country %s\n", current->namefile, current->name);
			current = current->next;
			continue;
		}

		char cityName[25];
		int population;

		while (fscanf(cityfp, "%24s %d", cityName, &population) == 2) {
			current->city = insertCity(current->city, cityName, population);
		}

		fclose(cityfp);
		current = current->next;
	}

	
	current = head;
	while (current) {
		printf("%s:\n", current->name);
		printCities(current->city);  
		current = current->next;
	}

	return 0;
}


countryP addtolist(countryP head,char* countryName,char* countryfile) {
	countryP newelement = (countryP)malloc(sizeof(country));
	if (!newelement) return head;

	strncpy(newelement->name, countryName, 24);
	newelement->name[24] = '\0';

	strncpy(newelement->namefile, countryfile, 24);
	newelement->namefile[24] = '\0';

	if (!head || strcmp(countryName, head->name) < 0) {
		newelement->next = head;
		return newelement;
	}

	countryP p = head;
	while (p->next && strcmp(p->next->name, countryName) < 0) {
		p = p->next;
	}

	newelement->next = p->next;
	p->next = newelement;

	return head;
}

cityP insertCity(cityP root, char* cityName, int population) {
	if (!root) {
		cityP newNode = malloc(sizeof(*newNode));
		if (!newNode) return NULL;

		strncpy(newNode->name, cityName, 24);
		newNode->name[24] = '\0';
		newNode->population = population;
		newNode->left = newNode->right = NULL;

		return newNode;
	}

	if (strcmp(cityName, root->name) < 0) {
		root->left = insertCity(root->left, cityName, population);
	}
	else {
		root->right = insertCity(root->right, cityName, population);
	}

	return root;
}



void printCities(cityP root) {
	if (!root) return;
	printCities(root->left);
	printf("%s %d\n", root->name, root->population);
	printCities(root->right);
}
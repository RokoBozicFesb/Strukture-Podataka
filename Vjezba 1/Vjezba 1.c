#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct {
	char ime[20];
	char prezime[30];
	int bodovi;
	float relatvan_br_bodova;

}_studenti;




int main(void) {

	FILE* fp = fopen("studenti.txt", "r");
	if (fp == NULL) {
		printf("Greska");
		return 1;
	}

	int brojac = 0;
	char ime[20], prezime[30];
	int bodovi;


	while (fscanf(fp, " %19s %29s %d", ime, prezime, &bodovi) == 3) {			//provjeravamo koliko studenata se nalazi u file-u								
		brojac++;
	}

	printf("%d\n", brojac);

	rewind(fp);

	_studenti* s;
	s = (_studenti*)malloc(brojac * sizeof(_studenti));
	if (!s) {
		printf("Pogresna alokacija");
		fclose(fp);
		return 1;
	}

	for (int i = 0; i < brojac; i++) {
		fscanf(fp, "%19s %29s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
	}

	fclose(fp);

	for (int i = 0; i < brojac; i++) {
		s[i].relatvan_br_bodova = (float)s[i].bodovi / MAX * 100;

	}

	printf("\nIspis\n");
	printf("IME\tPREZIME\t\tBODOVI\t RELATIVAN_BROJ_BODOVA\n");
	for (int i = 0; i < brojac; i++) {
		printf("%s\t %-10s\t %3d\t %f\n", s[i].ime, s[i].prezime, s[i].bodovi, s[i].relatvan_br_bodova);

	}

	free(s);

	return 0;
}
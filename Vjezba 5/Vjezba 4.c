#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct poly* Position;
typedef struct poly {
	int coeficient;
	int pow;
	Position next;
}poly;


void read(Position head, char* filename);
int suma(Position p, Position q, Position r);
int multiply(Position p, Position q, Position r);



int main(void) {


	poly head1 = {0,0, NULL };
	poly head2 = { 0,0, NULL };
    poly sum = { 0,0, NULL };
    poly mul = { 0,0, NULL };
	
	read(&head1, "1.txt");
	read(&head2, "2.txt");

    suma(head1.next, head2.next, &sum);
    multiply(head1.next, head2.next, &mul);

    printf("Zbroj je: \n");
    Print(sum.next);


    printf("Umnozak je: \n");
    Print(mul.next);



	return 0;
}



Position CreateNode(int coef, int exp)
{
	Position newNode = (Position)malloc(sizeof(poly));
	newNode->coeficient = coef;
	newNode->pow = exp;
	newNode->next = NULL;
	return newNode;
}




void read(Position head, char* filename) {
	FILE* f1 = fopen(filename, "r");

	if (f1 == NULL) {
		printf("Nema filea");
		return 1;
	}
	int coef, exp;
	Position q = head;

	while (fscanf(f1, "%d %d", &coef, &exp) == 2) {

		Position newNode = CreateNode(coef, exp);
		q->next = newNode;
		q = newNode;

	}
	fclose(f1);
	return 0;
}

int sum(Position p1, Position p2, Position r)
{
    Position last = r;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->pow == p2->pow)
        {
            int sumCoef = p1->coeficient + p2->coeficient;
            if (sumCoef != 0)
            {
                Position newNode = CreateNode(sumCoef, p1->pow);
                last->next = newNode;
                last = newNode;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->pow > p2->pow)
        {
            Position newNode = CreateNode(p1->coeficient, p1->pow);
            last->next = newNode;
            last = newNode;
            p1 = p1->next;
        }
        else
        {
            Position newNode = CreateNode(p2->coeficient, p2->pow);
            last->next = newNode;
            last = newNode;
            p2 = p2->next;
        }
    }
}

    int multiply(Position p1, Position p2, Position r)
    {
        Position last = r;
        Position temp;

        while (p1 != NULL)
        {
            temp = p2;
            while (temp != NULL)
            {
                int c = p1->coef * temp->coef;
                int e = p1->pow + temp->pow;

                Position newNode = CreateNode(c, e);
                last->next = newNode;
                last = newNode;

                temp = temp->next;
            }
            p1 = p1->next;
        }

        r->next = sortPoly(r->next);
        addP(r->next);

        return 0;
    }

    int Print(Position head)
    {
        while (head != NULL)
        {
            printf("%dx^%d ", head->coeficient, head->pow);
            head = head->next;
        }
        printf("\n");
        return 0;
    }
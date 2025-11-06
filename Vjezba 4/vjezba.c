#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 250

struct Stack;
typedef struct Stack* S;

 struct Stack {
	float variable;
	 S next;
};

S create(float);
S push(S, float);
S pop(S, float*, float*);

int main() {
	int brojac = 0;
	float op1, op2, result;
	char buffer[MAX];
	char* clean = remove_spaces(buffer);
	printf("%s\n", clean);
	S head = NULL;

	while (*(clean + brojac) != '\0') {
		char var_op = *(clean + brojac);
		if (var_op >= '0' && var_op <= '9') {
			head = push(head, (float)(var_op - '0'));
		}
		else {
			switch (var_op) {
			case '+': {
				head = pop(head, &op1, &op2);
				result = op1 + op2;
				head = push(head, result);
				break;
			}
			case '-': {
				head = pop(head, &op1, &op2);
				result = op1 - op2;
				head = push(head, result);
				break;
			}
			case '*': {
				head = pop(head, &op1, &op2);
				result = op1 * op2;
				head = push(head, result);
				break;
			}
			case '/': {
				head = pop(head, &op1, &op2);
				if (op2 == 0) {
					printf("Greska! Nesmije se dijeliti s nulom!\n");
					return 1;
				}
				result = op1 / op2;
				head = push(head, result);
				break;
			}

			default:
				printf("Znak nije prepoznat!\n");
				break;
			}
		}
		brojac++;
	}
	if (head == NULL) {
		printf("Greska! Prazan stog!\n");
	}
	else if (head->next != NULL) {
		printf("Greska! Na stogu ima više od jednog elementa!\n");
	}
	else {
		printf("\nRezultat: %.1f\n", head->variable);
	}
}


S create(float var) {
	S new_var = (S)malloc(sizeof(struct Stack));
	if (!new_var) {
		printf("Greska u alokaciji!\n");
		return NULL;
	}
	new_var->next = NULL;
	new_var->variable = var;

	return new_var;
}

S push(S head, float variable) {
	S new_var = create(variable);
	if (!new_var) {
		printf("Greska u kreiranju osobe!\n");
		return NULL;
	}

	if (head == NULL) {
		return new_var;
	}

	new_var->next = head;
	return new_var;
}

S pop(S head, float* op1, float* op2) {
	if (head == NULL || head->next == NULL) {
		printf("Nedovoljno elemenata za racunanje!\n");
		exit(1);
	}

	*op2 = head->variable;
	S temp = head;
	head = head->next;
	free(temp);

	*op1 = head->variable;
	temp = head;
	head = head->next;
	free(temp);

	return head;
}
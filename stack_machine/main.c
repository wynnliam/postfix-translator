// Liam Wynn, 5/11/2020, Stack Machine.

/*
	I guess this would count as a virtual machine. The Postfix Translator
	acts as the front half of a language whose back end is a stack machine.

*/

#include <stdio.h>
#include "./stack.h"

int main() {
	printf("Welcome to the stack!\n");

	push(1);
	push(2);
	size_t v = pop();

	printf("%d\n", v);

	return 0;
}

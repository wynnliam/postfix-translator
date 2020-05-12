// Liam Wynn, 5/11/2020, Stack Machine.

/*
	I guess this would count as a virtual machine. The Postfix Translator
	acts as the front half of a language whose back end is a stack machine.

*/

#include <stdio.h>
#include "./stack.h"
#include "./data.h"

int main() {
	printf("Welcome to the stack!\n");

	lvalue("a");
	push(2);
	push(3);
	add();
	assignment();

	var_cleanup();

	return 0;
}

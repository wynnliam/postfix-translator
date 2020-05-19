// Liam Wynn, 5/11/2020, Stack Machine.

/*
	I guess this would count as a virtual machine. The Postfix Translator
	acts as the front half of a language whose back end is a stack machine.

*/

#include <stdio.h>
#include <ctype.h>
#include "./program.h"
#include "./stack.h"
#include "./data.h"

static char command[100];
static char arg[100];

void read() {
	scanf("%s %s", command, arg);

	while(getchar() != '\n');
}

int main() {
	printf("Welcome to the stack!\n");

	while(1) {
		read();
	}

	/*add_instruction(INST_LVAL, (size_t)"a");
	add_instruction(INST_PUSH, 2);
	add_instruction(INST_PUSH, 3);
	add_instruction(INST_ADD, 0);
	add_instruction(INST_ASSIGN, 0);

	execute_program();

	print_variables();
	var_cleanup();*/

	/*lvalue("a");
	push(2);
	push(3);
	add();
	assignment();

	print_variables();
	var_cleanup();*/

	return 0;
}

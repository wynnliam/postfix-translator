// Liam Wynn, 5/11/2020, Stack Machine.

/*
	I guess this would count as a virtual machine. The Postfix Translator
	acts as the front half of a language whose back end is a stack machine.

*/

#include <stdio.h>
#include "./program.h"
#include "./stack.h"
#include "./data.h"

int main() {
	printf("Welcome to the stack!\n");

	add_instruction(INST_LVAL, (size_t)"a");
	add_instruction(INST_PUSH, 2);
	add_instruction(INST_PUSH, 3);
	add_instruction(INST_ADD, 0);
	add_instruction(INST_ASSIGN, 0);

	// TODO: Execute

	/*lvalue("a");
	push(2);
	push(3);
	add();
	assignment();

	print_variables();
	var_cleanup();*/

	return 0;
}

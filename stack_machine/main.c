// Liam Wynn, 5/11/2020, Stack Machine.

/*
	I guess this would count as a virtual machine. The Postfix Translator
	acts as the front half of a language whose back end is a stack machine.

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "./program.h"
#include "./stack.h"
#include "./data.h"
#include "./error.h"

static size_t command = INST_NONE;
static char buffer[100];

int read() {
	while(1) {
		int t = getchar();

		if(t == ' ' || t == '\t' || t == '\n');

		else if(t == '+') {
			add_instruction(INST_ADD, 0);
			return 1;
		} else if(t == '-') {
			add_instruction(INST_SUBTRACT, 0);
			return 1;
		} else if(t == '*') {
			add_instruction(INST_MULT, 0);
			return 1;
		} else if(t == '/') {
			add_instruction(INST_DIVIDE, 0);
			return 1;
		} else if(t == ':') {
			t = getchar();
			if(t == '=') {
				add_instruction(INST_ASSIGN, 0);
				return 1;
			} else {
				error("Bad command");
			}
		} else if(isalnum(t)) {
			// Read the command
			int bindex = 0;
			do {
				buffer[bindex] = t;
				bindex++;
				t = getchar();
			} while(isalnum(t));

			ungetc(t, stdin);
			buffer[bindex] = '\0';

			// Treat as command
			if(command == INST_NONE) {
				if(strcmp(buffer, "push") == 0)
					command = INST_PUSH;
				else if(strcmp(buffer, "pop") == 0)
					command = INST_POP;
				else if(strcmp(buffer, "copy") == 0)
					command = INST_COPY;
				else if(strcmp(buffer, "rvalue") == 0)
					command = INST_RVAL;
				else if(strcmp(buffer, "lvalue") == 0)
					command = INST_LVAL;
				else
					error("Bad command");
			} else {
				char* argcopy = (char*)malloc(strlen(buffer) + 1);
				strcpy(argcopy, buffer);

				// Treat as argument.
				size_t argnum = atoi(argcopy);
				size_t arg;

				if(command == INST_PUSH) {
					arg = argnum;
					free(argcopy);
				} else {
					arg = (size_t)argcopy;
				}

				add_instruction(command, arg);

				command = INST_NONE;
			}

		} else if(t == EOF) {
			return 0;
		} else {
			error("Bad command");
		}

		return 1;
	}
}

int main() {
	printf("Welcome to the stack!\n");

	while(read() != 0);

	execute_program();

	print_variables();
	var_cleanup();

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

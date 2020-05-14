// Liam Wynn, 5/14/2020, Stack Machine

#include "./program.h"

#include "./stack.h"
#include "./data.h"
#include "./error.h"

#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCTIONS	1000

struct instruction {
	size_t type;
	union {
		size_t val;
		char* identifier;
	} arg;
};

struct label {
	char* id;
	size_t instaddr;
};

static struct instruction program[MAX_INSTRUCTIONS];
static int num_instructions = 0;

static struct label labels[MAX_INSTRUCTIONS];
static int num_labels = 0;

// Program counter - keeps track of the current instruction we
// are on. Needed for control flow instructions.
static int pc = 0;

void add_instruction(const size_t type, const size_t arg) {
	if(num_instructions >= MAX_INSTRUCTIONS)
		error("Out of instruction memory");

	program[num_instructions].type = type;

	if(type == INST_LVAL || type == INST_RVAL) {
		program[num_instructions].arg.identifier = (char*)arg;
	} else {
		program[num_instructions].arg.val = arg;
	}

	num_instructions++;
}

void execute_program() {
	for(pc = 0; pc < num_instructions; pc++) {
		switch(program[pc].type) {
			case INST_ADD:
				add();
				break;
			case INST_SUBTRACT:
				subtract();
				break;
			case INST_DIVIDE:
				divide();
				break;
			case INST_MULT:
				multiply();
				break;

			case INST_PUSH:
				push(program[pc].arg.val);
				break;
			case INST_POP:
				pop(); // TODO: Cannot save value
				break;
			case INST_COPY:
				copy();
				break;

			case INST_RVAL:
				rvalue(program[pc].arg.identifier);
				break;
			case INST_LVAL:
				lvalue(program[pc].arg.identifier);
				break;
			case INST_ASSIGN:
				assignment();
				break;

			default:
				error("Bad instruction");
		}
	}
}

// TODO: Free memory.
void add_label(const char* id) {
	if(num_labels >= MAX_INSTRUCTIONS)
		error("Out of label memory");

	labels[num_labels].instaddr = pc;

	labels[num_labels].id = (char*)malloc(strlen(id) + 1);
	strcpy(labels[num_labels].id, id);

	num_labels++;
}

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

static size_t address_from_label(const char* label);

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

	// Labels aren't really instructions, but have the same
	// syntax. So we want to keep track of the address when
	// we add this instruction.
	if(type == INST_LABEL)
		add_label((char*)arg);

	if(type == INST_LVAL || type == INST_RVAL ||
	   INST_LABEL || type == INST_GOTO ||
	   type == INST_GOTRUE || type == INST_GOFALSE) {
		program[num_instructions].arg.identifier = (char*)arg;
	} else {
		program[num_instructions].arg.val = arg;
	}

	num_instructions++;
}

void execute_program() {
	size_t jaddr;
	size_t val;

	while(pc < num_instructions) {
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

			// They don't do anything
			case INST_LABEL:
				break;
			case INST_GOTO:
				jaddr = address_from_label(program[pc].arg.identifier);
				pc = jaddr + 1;
				continue;
			case INST_GOFALSE:
				jaddr = address_from_label(program[pc].arg.identifier);
				val = pop();
				if(val == 0) {
					pc = jaddr + 1;
					continue;
				}
				break;
			case INST_GOTRUE:
				jaddr = address_from_label(program[pc].arg.identifier);
				val = pop();
				if(val) {
					pc = jaddr + 1;
					continue;
				}
				break;

			case INST_HALT:
				return;

			default:
				error("Bad instruction");
		}

		pc++;
	}
}

// TODO: Free memory.
void add_label(const char* id) {
	if(num_labels >= MAX_INSTRUCTIONS)
		error("Out of label memory");

	labels[num_labels].instaddr = num_instructions;

	labels[num_labels].id = (char*)malloc(strlen(id) + 1);
	strcpy(labels[num_labels].id, id);

	num_labels++;
}

size_t address_from_label(const char* label) {
	size_t i;
	for(i = 0; i < num_labels; i++) {
		if(strcmp(label, labels[i].id) == 0)
			return labels[i].instaddr;
	}

	error("Bad label");
}

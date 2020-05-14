// Liam Wynn, 5/14/2020, Stack Machine

#include "./program.h"

#include "./stack.h"
#include "./data.h"
#include "./error.h"

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
	size_t i = 0;

	for(i = 0; i < num_instructions; i++) {
		switch(program[i].type) {
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
				push(program[i].arg.val);
				break;
			case INST_POP:
				pop(); // TODO: Cannot save value
				break;
			case INST_COPY:
				copy();
				break;

			case INST_RVAL:
				rvalue(program[i].arg.identifier);
				break;
			case INST_LVAL:
				lvalue(program[i].arg.identifier);
				break;
			case INST_ASSIGN:
				assignment();
				break;

			default:
				error("Bad instruction");
		}
	}
}

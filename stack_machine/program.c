// Liam Wynn, 5/14/2020, Stack Machine

#include "./program.h"

#include "./error.h"

#define MAX_INSTRUCTIONS	1000

struct instruction {
	size_t type;
	union {
		size_t val;
		char* identifier;
	} arg;
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

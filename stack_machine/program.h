// Liam Wynn, 5/14/2020, Stack Machine

#include <stddef.h>

#define INST_ADD		0
#define INST_SUBTRACT	INST_ADD + 1
#define INST_DIVIDE		INST_SUBTRACT + 1
#define INST_MULT		INST_DIVIDE + 1
#define INST_PUSH		INST_MULT + 1
#define INST_POP		INST_PUSH + 1
#define INST_COPY		INST_POP + 1
#define INST_RVAL		INST_COPY + 1
#define INST_LVAL		INST_RVAL + 1
#define INST_ASSIGN		INST_LVAL + 1

struct instruction {
	size_t type;
	union {
		size_t val;
		char* identifier;
	} arg;
};


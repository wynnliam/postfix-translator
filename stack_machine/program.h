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

#define INST_LABEL		INST_ASSIGN + 1
#define INST_GOTO		INST_LABEL + 1
#define INST_GOFALSE	INST_GOTO + 1
#define INST_GOTRUE		INST_GOFALSE + 1
#define INST_HALT		INST_GOTRUE + 1

#define INST_NONE		INST_HALT + 1

extern void add_instruction(const size_t type, const size_t arg);
extern void execute_program();

extern void add_label(const char* id);

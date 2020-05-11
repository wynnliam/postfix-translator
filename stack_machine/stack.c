// Liam Wynn, 5/11/2020, Stack Machine.

#include "./stack.h"
#include "./error.h"

#define STACK_MEMORY	1000

static size_t stack[STACK_MEMORY];
static size_t head = 0;

extern void push(const size_t val) {
	if(head >= STACK_MEMORY)
		error("Out of memory");

	stack[head] = val;
	head++;
}


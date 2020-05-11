// Liam Wynn, 5/11/2020, Stack Machine.

#include "./stack.h"
#include "./error.h"

#define STACK_MEMORY	1000

static size_t stack[STACK_MEMORY];
static size_t head = 0;

void push(const size_t val) {
	if(head >= STACK_MEMORY)
		error("Out of memory");

	stack[head] = val;
	head++;
}

size_t pop() {
	if(head == 0)
		error("Nothing to pop");

	head--;
	size_t val = stack[head];

	return val;
}

// Liam Wynn, 5/11/2020, Stack Machine.

#include "./stack.h"
#include "./error.h"

#define STACK_MEMORY	1000

static size_t stack[STACK_MEMORY];
// The index we will add our next value to.
static size_t next = 0;

void push(const size_t val) {
	if(next >= STACK_MEMORY)
		error("Out of memory");

	stack[next] = val;
	next++;
}

size_t pop() {
	if(next == 0)
		error("Nothing to pop");

	next--;
	size_t val = stack[next];

	return val;
}

void copy() {
	if(next == 0)
		error("Nothing to copy");

	size_t val = stack[next - 1];
	push(val);
}

void add() {
	if(next < 2)
		error("Need two values for addition");

	size_t a = pop();
	size_t b = pop();
	push(a + b);
}

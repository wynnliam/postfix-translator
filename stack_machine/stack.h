// Liam Wynn, 5/11/2020, Stack Machine.

#include <stddef.h>

// Pushes val to the top of the stack.
extern void push(const size_t val);

// Pops the top value of the head of the stack and returns it.
extern size_t pop();

// Pushes a copy of whatever is currently on the top of the stack.
extern void copy();

/* MATH OPERATIONS */
extern void add();
extern void subtract();

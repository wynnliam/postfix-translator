// Liam Wynn, 5/11/2020, Stack Machine

#include "./data.h"
#include "./stack.h"
#include "./error.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARS	1000

struct variable {
	char* identifier; // The name of the variable used in code.
	size_t* address; // Pointer into the values array.
};

static struct variable variables[MAX_VARS];
static size_t values[MAX_VARS];

static int num_vars = 0;

void lvalue(const char* var) {
	if(!var)
		error("Bad lvalue instruction");

	size_t i;
	for(i = 0; i < num_vars; i++) {
		if(strcmp(var, variables[i].identifier) == 0) {
			break;
		}
	}

	// We must add a new variable.
	if(i == num_vars) {
		if(num_vars == MAX_VARS)
			error("Out of variable memory");

		variables[i].identifier = (char*)malloc(strlen(var) + 1);
		strcpy(variables[i].identifier, var);

		// Set the address to the next available spot
		variables[i].address = &values[i];

		num_vars++;
	}

	push((size_t)variables[i].address);
}

void rvalue(const char* var) {
	if(!var)
		error("Bad variable name");

	size_t i;
	for(i = 0; i < num_vars; i++) {
		if(strcmp(var, variables[i].identifier) == 0) {
			push(*(variables[i].address));
			break;
		}
	}

	if(i == num_vars)
		error("Cannot push variable that doesn't exist");
}

void var_cleanup() {
	size_t i;
	for(i = 0; i < num_vars; i++) {
		free(variables[i].identifier);
		variables[i].identifier = NULL;
	}
}

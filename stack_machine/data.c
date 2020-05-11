// Liam Wynn, 5/11/2020, Stack Machine

#include "./data.h"

#include <stddef.h>

#define MAX_VARS	1000

struct variable {
	char* identifier; // The name of the variable used in code.
	size_t* address; // Pointer into the values array.
};

static struct variable* variables[MAX_VARS];
static size_t values[MAX_VARS];

static int num_vars = 0;

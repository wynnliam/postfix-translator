// Liam Wynn, 5/14/2020, Stack Machine

#include <stddef.h>

struct instruction {
	size_t type;
	union {
		size_t val;
		char* identifier;
	} arg;
};


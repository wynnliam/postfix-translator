// Liam Wynn, 5/11/2020, Stack Machine

#include "./error.h"
#include "./data.h"

#include <stdio.h>
#include <stdlib.h>

void error(const char* message) {
	printf("ERROR: %s\n", message);

	var_cleanup();
	exit(1);
}

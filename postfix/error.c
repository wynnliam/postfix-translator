// Liam Wynn, 3/14/2020, Postfix Translator

#include "./globals.h"

int line_num = 1;

void error(const char* message);

void error(const char* message) {
	printf("ERROR: %s\n", message);
	exit(1);
}

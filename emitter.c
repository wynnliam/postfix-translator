// Liam Wynn, 5/4/2020, Postfix Translator

#include "./globals.h"
#include <stdio.h>

void emit(int t, int tval) {
	switch(t) {
		case '+': case '-': case '*': case '/':
			printf("%c ", t);
			break;
		case NUM:
			printf("%d ", tval);
			break;
		default:
			printf("token %d, tokenval: %d\n", t, tval);
	}
}

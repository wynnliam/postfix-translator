// Liam Wynn, 5/4/2020, Postfix Translator

#include "./globals.h"
#include <stdio.h>

void emit(int t, int tval) {
	switch(t) {
		case '+': case '-': case '*': case '/':
			printf("%c\n", t);
		default:
			printf("token %d, tokenval: %d\n", t, tval);
	}
}

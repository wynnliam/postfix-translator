// Liam Wynn, 2/11/2020, Postfix Translator.

/*
	Working example from Compilers: Principles, Techniques, and Tools.

	This is an example of a recursive descent parser for implementing
	a postfix translator.

	For example, given 9-5+2
	The result is 95-2+

	The grammar for expressions we parse is:

	expr -> term rest
	rest -> + term rest
	rest -> - term rest
	rest -> e (empty)
	term -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int lookahead;

void match(const int token);
void expr();
void rest();
void term();
void error(const char* message);

int main() {
	lookahead = getchar();
	expr();
	putchar('\n');
	return 0;
}

void match(const int token) {
	if(lookahead == token)
		lookahead = getchar();
	else
		error("Bad token");
}

void expr() {
	term();
	rest();
}

void rest() {
	if(lookahead == '+') {
		match('+');
		term();
		putchar('+');
		rest();
	} else if(lookahead == '-') {
		match('-');
		term();
		putchar('-');
		rest();
	}
}

void term() {
	if(isdigit(lookahead)) {
		putchar(lookahead);
		match(lookahead);
	} else {
		error("Bad digit");
	}
}

void error(const char* message) {
	printf("ERROR: %s\n", message);
	exit(1);
}

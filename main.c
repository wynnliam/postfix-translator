// Liam Wynn, 2/11/2020, Postfix Translator.

/*
	Working example from Compilers: Principles, Techniques, and Tools.

	This is an example of a recursive descent parser for implementing
	a postfix translator.

	For example, given 9-5+2
	The result is 95-2+

	The grammar for expressions we parse is:

	start -> list EOF

	list -> expr ; list | e

	expr -> term moreterms

	moreterms -> + term moreterms
			  |  - term moreterms
			  | e

	term -> factor morefactors

	morefactors -> * factor morefactors
				 | / factor morefactors
				 | div factor morefactors
				 | mod factor morefactors
				 | e

	factor -> ( expr ) | id | num

	We assume that the user will input an expression. Our job
	is to a) decide if the user input is a correct expression
	and b) print the corresponding postfix translation of that
	expression.

	A recursive descent parser defines a procedure for each
	nonterminal in our grammar. So we have functions expr,
	rest, and term as per the grammar above. Then, for each
	production, we call the appropriate nonterminal procedure.
	We finally use a function called match that gives us the
	next token in our stream. In doing it this way, our parser
	never has to backtrack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NONE	-1
#define NUM 	256

int lookahead;
// The number value of the current token
int tokenval = NONE;
int line_num = 1;

int lexan();
void match(const int token);
void expr();
void rest();
void factor();
void term();
void error(const char* message);

int main() {
	lookahead = lexan();
	expr();
	putchar('\n');
	return 0;
}

int lexan() {
	int t;

	while(1) {
		t = getchar();

		// Whitespace: just ignore it
		if(t == ' ' || t == '\t')
			;
		else if(t == '\n') {
			line_num += 1;
			return NONE;
		}

		else if(isdigit(t)) {
			tokenval = t - '0'; // Gives numeric value of t
			t = getchar();
			while(isdigit(t)) {
				// Adding a new digit means increasing token by a factor of 10
				tokenval = tokenval * 10 + t - '0';
				t = getchar();
			}

			// If isdigit(t) == false, we've gone too far, so put t back
			ungetc(t, stdin);
			return NUM;
		}

		else {
			tokenval = NONE;
			return t;
		}
	}
}

void match(const int token) {
	if(lookahead == token)
		lookahead = lexan();
	else
		error("Bad token");
}

void expr() {
	factor();
	rest();
}

void rest() {
	if(lookahead == '+') {
		match('+');
		factor();
		putchar('+');
		rest();
	} else if(lookahead == '-') {
		match('-');
		factor();
		putchar('-');
		rest();
	}
}

void factor() {
	if(lookahead == '(') {
		match('(');
		expr();
		match(')');
	} else if(lookahead == NUM) {
		printf(" %d ", tokenval);
		match(NUM);
	} else error("Bad factor");
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

// Liam Wynn, 3/14/2020, Postfix Translator.

#include "./globals.h"

extern int lexan();
extern void match(const int token);
extern void error(const char* message);

void parse();
void expr();
void term();
void factor();

void parse() {
	// Essentially this handles the production:
	// list -> expr ; list | e
	lookahead = lexan();
	while(lookahead != DONE) {
		expr();
		putchar('\n');
		match(';');
	}
}

/*
	Implements the expr and moreterm production rules:

	expr -> term moreterms
	moreterms -> + term moreterms
			  |  - term moreterms
			  | e
*/
void expr() {
	int t;
	term();
	while(1) {
		if(lookahead == '+' || lookahead == '-') {
			t = lookahead;
			match(lookahead);
			term();
			emit(t, NONE);
			continue;
		} else {
			return;
		}
	}
}

/*
	Implements the term and morefactors production rules:

	term -> factor morefactors
	morefactors -> * factor morefactors
				 | / factor morefactors
				 | div factor morefactors
				 | mod factor morefactors
				 | e
*/
void term() {
	int t;
	factor();
	while(1) {
		if(lookahead == '*' || lookahead == '/') {
			t = lookahead;
			match(lookahead);
			factor();
			printf(" %c ", (char)t);
			continue;
		} else {
			return;
		}
	}
	/*if(isdigit(lookahead)) {
		putchar(lookahead);
		match(lookahead);
	} else {
		error("Bad digit");
	}*/
}

/*
	Implements the factor production rule:
	factor -> ( expr ) | id | num
*/
void factor() {
	if(lookahead == '(') {
		match('(');
		expr();
		match(')');
	} else if(lookahead == NUM) {
		//printf(" %d ", tokenval);
		emit(NUM, tokenval);
		match(NUM);
	} else if(lookahead == ID) {
		printf(" %s ", symbol_table[tokenval].lexptr);
		match(ID);
	} else error("Bad factor");
}

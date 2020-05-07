// Liam Wynn, 3/14/2020, Postfix Translator.

#include "./globals.h"

extern int lexan();
extern void match(const int token);
extern void error(const char* message);

// A cheap way to keep track of labels. Everytime
// we generate a label, we return this value then increment.
static int lbl_count = 0;

int newlabel();

void parse();
void stmt_list();
void stmt();
void opt_stmt();
void expr();
void term();
void factor();

void parse() {
	// Essentially this handles the production:
	// list -> stmt ; list | e
	lookahead = lexan();
	stmt_list();
	/*while(lookahead != DONE) {
		stmt();
		putchar('\n');
		match(';');
	}*/
}

void stmt_list() {
	do {
		stmt();
		putchar('\n');
		match(';');
	} while(lookahead != DONE && lookahead != END);
}

/*
	Implements rule:
	stmt -> id := expr
		  | if expr then stmt
		  | while expr do stmt
		  | begin opt_stmt end

	At the moment, stmt doesn't do much. However,
	we are setting it up to handle a more rich variety
	of real statements.
*/
void stmt() {
	if(lookahead == ID) {
		//emit(ASSIGN, tokenval); // tokenval now set to index to id in symbol table.
		emit_lvalue(tokenval);
		match(ID); // Checks lookahead is an ID then reads next token.
		match(ASSIGN); // Checks lookahead is an assignment token then does read.
		expr(); // Now read an expression.
		emit_assign();
	} else if(lookahead == IFSTMT) {
		match(IFSTMT);
		expr(); // We want to evaluate the test expression
		int out = newlabel(); // We want the gofalse if the expression evaluates to 0.
		emit_gotofalse(out);
		match(THENSTMT); // Match the then.
		stmt(); // Parse the branch true statement.
		emit_label(out);
	} else if(lookahead == WHILESTMT) {
		int test = newlabel();
		int out = newlabel();
		emit_label(test);
		match(WHILESTMT);
		expr();
		emit_gotofalse(out);
		match(DOSTMT);
		stmt();
		emit_goto(test);
		emit_label(out);
	} else if(lookahead == BEGIN) {
		match(BEGIN);
		opt_stmt();
		match(END);
	}
}

/*
	Implements :
	opt_stmt -> list | e

	TODO: Rewrite grammar so we have
	stmt_list -> stmt_list ; stmt | stmt
	AND
	opt_list -> stmt_list | e

	Otherwise we are forced to have a semi-colon after an end
*/
void opt_stmt() {
	if(lookahead != END)
		stmt_list();
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
			emit(t, NONE);
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
		//emit(NUM, tokenval);
		emit_push(tokenval);
		match(NUM);
	} else if(lookahead == ID) {
		//printf(" %s ", symbol_table[tokenval].lexptr);
		//emit(ID, tokenval);
		emit_rvalue(tokenval);
		match(ID);
	} else error("Bad factor");
}

int newlabel() {
	return lbl_count++;
}

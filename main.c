// Liam Wynn, 2/11/2020, Postfix Translator.

/*
	Working example from Compilers: Principles, Techniques, and Tools.

	This is an example of a predictive parser for implementing
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

	We will implement our translator using predictive parsing.
	To understand what that is, we must first learn what is called
	"recusrive descent parsing".

	Recursive descent parsing is a top down method for syntax analysis
	where in each production rule has a corresponding procedure to handle
	it. For example, "expr -> term moreterms" would be handled by writing
	a procedure called "expr()" that would eventually call "term()" and
	"moreterms()". So our syntax analysis starts with the "start()" procedure,
	and descends down to parse (hence the "descent parsing" in the name). The
	"recusrive" part comes from the fact that production rules indirectly
	resolve to themselves, hence the "recursive" part in the name.

	So how do we implement recursive descent parsing? We use "predictive
	parsing". Essentially, predictive parsing uses a lookahead symbol to determine
	what production to take. The lookahead symbol unambiguously decides the
	production to take *without having to backtrack*! Thats incredibly powerful.
	However, we have some rules for our grammar to make this work: 1. Production
	rules must not be ambiguous and 2. no left recursion.

	When I say "production rules mus not be ambigious", I mean that two derivations
	for a nonterminal must be disjoint. For example, suppose I had the rule:

	expr -> id A | id B
	A -> ...
	B -> ...

	The predictive parser would not be able to handle this situation. The lookahead
	token would read id, and then which one would it pick?

	Second, we cannot have left recursion in our grammar. Why is this a problem?
	consider the rule:

	A -> A + B

	The corresponding code might me:

	A_expr() {
		A_expr();
		match('+');
		B_expr();
	}

	You would get an infinite loop!

	As such, we remove these problems from our grammar.
*/

#include "./globals.h"

int line_num = 1;
int tokenval = NONE;

char lexbuf[LEXBUF_SIZE];

// Symbol table functions we use
extern int lookup(char* lexeme);
extern int insert(char* lexeme, int token_val);

int lexan();
void match(const int token);
void expr();
void rest();
void factor();
void term();
void error(const char* message);

int main() {
	insert("div", DIV);
	insert("mod", MOD);

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
			// Put t back and read the entire number
			ungetc(t, stdin);
			scanf("%d", &tokenval);
			// I'll keep the old version here for your (and my) edification.
			/*tokenval = t - '0'; // Gives numeric value of t
			t = getchar();
			while(isdigit(t)) {
				// Adding a new digit means increasing token by a factor of 10
				tokenval = tokenval * 10 + t - '0';
				t = getchar();
			}

			// If isdigit(t) == false, we've gone too far, so put t back
			ungetc(t, stdin);*/
			return NUM;
		}

		else if(isalpha(t)) {
			int sym_table_pos;
			int buff_pos = 0;

			while(isalnum(t)) {
				lexbuf[buff_pos] = t;
				t = getchar();
				++buff_pos;

				if(buff_pos >= LEXBUF_SIZE)
					error("compiler error");
			}

			lexbuf[buff_pos] = EOS;
			// We are not done with all tokens to read so put
			// t back.
			if(t != EOF)
				ungetc(t, stdin);

			sym_table_pos = lookup(lexbuf);

			if(sym_table_pos == 0)
				sym_table_pos = insert(lexbuf, ID);

			tokenval = sym_table_pos;
			return symbol_table[sym_table_pos].token_val;
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

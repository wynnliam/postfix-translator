// Liam Wynn, 2/11/2020, Postfix Translator.

/*
	Working example from Compilers: Principles, Techniques, and Tools.

	This is an example of a predictive parser for implementing
	a postfix translator.

	For example, given 9-5+2
	The result is 95-2+

	The grammar for expressions we parse is:

	start -> list EOF

	list -> stmt ; list | e

	stmt -> id := expr
		  | if expr then stmt
		  | while expr do stmt
		  | begin opt_stmt end

	opt_stmt -> list | e

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

	TODO: We want to extend this system to support a grammar of this type:
	stmt -> id := expr
		 |  if expr then stmt
		 |  while expr do stmt
		 |  begin opt_stmts end

	opt_stmts -> stmt_list | e
	stmt_list -> stmt_list ; stmt | stmt

	TODO: We want to add a stack machine to produce an intermediate representation
	of our language.

	TODO: Write an emitter to abstract out print statements!
*/

#include "./globals.h"


extern void init();
extern void parse();

int main() {
	init();
	parse();

	return 0;
}


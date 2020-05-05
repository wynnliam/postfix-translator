// Liam Wynn, 3/13/2020, Postfix Translator.

/*
	This file stores all global variables and values.
	Basically, if more than one file uses it, it's here.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* TOKEN VALUE DEFINITIONS */

// Possible values for tokenval. We choose
// values that a char cannot have with the exception
// of EOS, which in ASCII is 0 and universally means 
// "end of string".
#define NONE		-1
#define EOS			0
#define NUM 		256
#define DIV			NUM + 1
#define MOD			DIV + 1
#define ID			MOD + 1
#define DONE		ID + 1
#define ASSIGN		DONE + 1
#define IFSTMT		ASSIGN + 1
#define THENSTMT	IFSTMT + 1
#define WHILESTMT	THENSTMT + 1
#define DOSTMT		WHILESTMT + 1

// The number value of the current token. For
// a token we read in, this tells us the type in a way
// the system can easily understand.
extern int tokenval;


/* SYMBOL TABLE DEFINITIONS */

// The symbol table holds every id the program sees:
// "mod", "div", and all id's that start with an alphabet
// character.

// The symbol table is implemented in two parts:
// First there is the array of symbols (the symbol_table),
// and a single character array that holds every id lexeme.
struct sym_entry {
	// Points to the first character in a string within
	// lexemes
	char* lexptr;
	// The token value for this entry.
	int token_val;
};


extern struct sym_entry symbol_table[];


/* LEXER DEFINITIONS */

#define LEXBUF_SIZE	128

// The key to predictive parsing. We use this to choose
// what production rule to follow given the one we are already
// at. Given how our grammar is structured, we can use this
// to always correctly choose the next production rule.
int lookahead;


/* ERROR HANDLING DEFITIONS */
// Use this for primitive error checking. When a problem
// occurs, we can at least point out the line that is
// the offender.
extern int line_num;
extern void error(const char* message);


/* EMIT - PRINTING OUTPUT */
// Prints a token's value (tval) according to its type (t).
extern void emit(int t, int tval);

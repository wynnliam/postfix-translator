// Liam Wynn, 3/13/2020, Postfix Translator.

/*
	This file stores all global variables and values.
	Basically, if more than one file uses it, it's here.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* TOKEN VALUE DEFINITIONS */

// Possible values for tokenval. We choose
// values that a char cannot have with the exception
// of EOS, which in ASCII is 0 and universally means 
// "end of string".
#define NONE	-1
#define EOS		0
#define NUM 	256
#define DIV		257
#define MOD		258
#define ID		259
#define DONE	260

// The number value of the current token. For
// a token we read in, this tells us the type in a way
// the system can easily understand.
int tokenval = NONE;


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

// Specifies the number the size of the lexeme array
#define STRMAX	999
// Specifies the size of the symbol table array.
#define SYMMAX	100

struct sym_entry symbol_table[SYMMAX];
char lexemes[STRMAX];


/* LEXER DEFINITIONS */

// The key to predictive parsing. We use this to choose
// what production rule to follow given the one we are already
// at. Given how our grammar is structured, we can use this
// to always correctly choose the next production rule.
int lookahead;


/* ERROR HANDLING DEFITIONS */
// Use this for primitive error checking. When a problem
// occurs, we can at least point out the line that is
// the offender.
int line_num = 1;

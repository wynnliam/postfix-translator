// Liam Wynn, 3/13/2020, Postfix Translator.

/*
	Here I implement all the functions used for updating and adding
	to the symbol table.

	We have only two procedures: lookup and insert. Lookup returns the
	index to the array of symbol_table that has the the lexeme we
	want to find (returns 0 if none found). Insert will insert a new
	symbol into the table provided it isn't there already.
*/

#include "./globals.h"

// Specifies the number the size of the lexeme array
#define STRMAX	999
// Specifies the size of the symbol table array.
#define SYMMAX	100

struct sym_entry symbol_table[SYMMAX];
char lexemes[STRMAX];

// The last used position in lexemes.
int last_char = -1;
// Last used position in the symbol table.
int last_entry = 0;

int lookup(char* s) {
	return 0;
}

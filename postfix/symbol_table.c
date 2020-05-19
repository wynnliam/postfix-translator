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

int lookup(char* lexeme) {
	int curr_pos;
	for(curr_pos = last_entry; curr_pos > 0; --curr_pos) {
		if(strcmp(symbol_table[curr_pos].lexptr, lexeme) == 0)
			return curr_pos;
	}

	return 0;
}

int insert(char* lexeme, int token_val) {
	int lexeme_len = strlen(lexeme);

	if(last_entry + 1 >= SYMMAX)
		error("symbol table full");
	if(last_char + lexeme_len + 1 >= STRMAX)
		error("lexems array full");

	++last_entry;

	symbol_table[last_entry].token_val = token_val;
	symbol_table[last_entry].lexptr = &lexemes[last_char + 1];

	last_char += lexeme_len + 1;

	strcpy(symbol_table[last_entry].lexptr, lexeme);

	return last_entry;
}

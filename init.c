// Liam Wynn, 3/14/2020, Postfix Translator.

#include "globals.h"

extern int insert(char* lexeme, int token_val);

void init() {
	insert("div", DIV);
	insert("mod", MOD);
	insert("if", IFSTMT);
	insert("then", THENSTMT);
}

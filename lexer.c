// Liam Wynn, 3/14/2020, Postfix Translator.

#include "./globals.h"

// Symbol table functions we use
extern int lookup(char* lexeme);
extern int insert(char* lexeme, int token_val);

int tokenval = NONE;
char lexbuf[LEXBUF_SIZE];

int lexan();
void match(const int token);

int lexan() {
	int t;

	while(1) {
		t = getchar();

		// Whitespace: just ignore it
		if(t == ' ' || t == '\t')
			;
		else if(t == '\n') {
			line_num += 1;
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

		else if(t == ':') {
			t = getchar();

			if(t == '=') {
				return ASSIGN;
			} else
				error("bad token");
		}

		else if(t == EOF)
			return DONE;

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

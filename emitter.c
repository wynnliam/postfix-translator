// Liam Wynn, 5/4/2020, Postfix Translator

#include "./globals.h"
#include <stdio.h>

void emit(int t, int tval) {
	switch(t) {
		case '+': case '-': case '*': case '/':
			printf("%c\n", t);
			break;
		case NUM:
			printf("%d\n", tval);
			break;
		case ID:
			printf("%s\n", symbol_table[tval].lexptr);
			break;
		case ASSIGN:
			printf("lvalue %s\n", symbol_table[tval].lexptr);
			break;
		case IFSTMT:
			printf("gofalse label\n");
			break;
		default:
			printf("token %d, tokenval: %d\n", t, tval);
	}
}

void emit_push(int val) {
	printf("push %d\n", val);
}

void emit_rvalue(int tval) {
	printf("rvalue %s\n", symbol_table[tval].lexptr);
}

void emit_label(int label) {
	printf("label_%d\n", label);
}

void emit_goto(int label) {
	printf("goto label_%d\n", label);
}

void emit_gotofalse(int label) {
	printf("gofalse label_%d\n", label);
}

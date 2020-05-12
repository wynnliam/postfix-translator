// Liam Wynn, 5/11/2020, Stack Machine

/*
	Pushes the address of var onto the stack.
	Side note: if var is not found, then we add
	it to our data list.
*/
extern void lvalue(const char* var);

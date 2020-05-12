// Liam Wynn, 5/11/2020, Stack Machine

/*
	Pushes the address of var onto the stack.
	Side note: if var is not found, then we add
	it to our data list.

	TODO: Free variables!
*/
extern void lvalue(const char* var);

/*
	Pushes the value of a var onto the stack.
	If the value is not found, we get an error
*/
extern void rvalue(const char* var);

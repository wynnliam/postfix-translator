## Postfix Translator Language

## Overview
This a complete compiler that transforms Postfix Translator Language into Stack Machine Code.

## How do I compile this compiler?
Once you've cloned the repo, move into the root directory of the project.
There are two subfolders: one for Postfix Translator Language (postfix) and
Stack Machine Code (stack_machine). The following steps apply to both projects.

Move to the folder of your choice and run the following command:

`gcc -g *.c`

## How do I run this compiler?
I should make a script that solves this. First, make sure both projects are compiled.
### Running Postfix Translator Language
First, move into the `postfix` folder. Next, create a file with some code in it (let's call it `example.pft`).
We will compile this to a Stack Machine Code with the following command:

`./a.out < example.pft > example.smc`

This will run the Postfix Translator part of the compiler on example.pft and put the resulting
Stack Machine Code into example.smc.
### Running Stack Machine
Now move example.smc to the `stack_machine` folder. Next,
move into this folder and run the following command:

`./a.out < example.smc`

The Stack Machine will run your code and print a listing of the values of all variables.

The rest of this document will describe what exactly the compiler is in greater detail.

## What is Postfix Translator Language?
Postfix Translator Language is a simple Pascal-like language. It has the following features:

1. Assignment statements like `a := 3 + 2;`
2. If-then statements `if a then b := 3 + 2`
3. While statements `while a do a := a - 1`
4. Begin-statements, which allow your to have a group of statements inside of one of the above. For example:
```
while a do
  begin
    a := a + 2;
    b := a - 1;
    a := b - 1;
  end;
;
```
5. Finally, you can do basic arithmetic: addition, subtraction, multiplication, division. Note that all variables
are UNSIGNED, so no negative numbers.

As a rule, all statements must end with a `;`. You may see have noticed an extra `;` in the example in feature 4. That
was not a mistake, but a quirk of the language.

### How does Postfix Translator Work?
There's a wonderful summary of how this front half compiler works in `main.c`. This will be basically the same information.
Essentially, the user inputs statements, and we use "recursive descent parsing" to decide if the user input is valid
Postfix Translator code and then output the appropriate Stack Machine Code.

#### What is "Recursive Descent Parsing#?
Recursive Descent Parsing is a "top-down" technique for parsing statements according to the language grammar (see below).
For each production of the grammar, we have a procedure that implements it. Suppose our grammar had the following statement:
`expr -> term moreterms`. Then we would have a procedure `expr()` that would call `term()` and then `moreterms()`.
In this way, we would descend down our grammar to parse the statement (hence the "descent parsing" in the name).

The "recursive" part comes from the fact that production rules typically resolve to themselves after enough productions
happen.

So how do we actually implement recursive descent parsing? We use a technique called "predictive parsing". Predictive parsing
uses a look-ahead symbol to decide what production to take. It's powerful because it unambiguously decides the production
*without having to backtrack!*.

However, this is only possible if the grammar is itself unambiguous. Consider the following grammar:
```
expr -> id A | id B
A -> C
B -> C
C -> q
```
This grammar is ambiguous. What I mean is that you have two different ways of reaching "id q" from expr:
1. `expr -> id A -> id C -> id q`
2. `expr -> id B -> id C -> id q`

The parser cannot handle this situation. The lookahead token would read an id, then which production should I take?
In this case, either path yields the same answer, but what if `A` and `B` went two different routes?

Second, consider a production rule like this:
`A -> A + B`

This what we call "left recursion": the left-most symbol of the production reduces to itself. The code for this might
be:

```
A_expr() {
  A_expr();
  emit('+');
  B_expr();
}
```

An infinite loop!

So in sum, your grammar cannot be ambigious, nor have "left recursion" in it. If you can do away with those two, then
you can implement recurisve descent parsing.

### Why is it called "Postfix Translator Language"?
Originally, the extent of this project was to "Use recusrive descent parsing to translate infix notation expressions to postfix notation." This is still a part of the language, as we translate infix expressions (`a + b`) to postfix (`a b +`). But
it was extended to have more statement types, as well as a stack machine for a back end to actually compute the code.

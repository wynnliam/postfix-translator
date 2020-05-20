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

Uses recusrive descent parsing to translate infix notation expressions to postfix notation.


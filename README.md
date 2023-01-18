# bfi
Simple BrainF*ck Interpreter and its clever examples

This is a sample BrainF*ck interpreter with some examples. 

Brainfuck is an esoteric programming language created in 1993 by Urban Müller. Notable for its extreme minimalism, the language consists of only eight simple commands, a data pointer and an instruction pointer. While it is fully Turing complete, it is not intended for practical use, but to challenge and amuse programmers. How it works ?

> 	++ptr;
< 	--ptr;
+ 	++*ptr;
- 	--*ptr;
. 	putchar(*ptr);
, 	*ptr = getchar();
[ 	while (*ptr) {
] 	}

No more :)

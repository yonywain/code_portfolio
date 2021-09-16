obj/calc.o: src/calc.c src/stack.h src/calc.h
	gcc -ansi -pedantic-errors -Wall -Wextra -g  -c -o obj/calc.o src/calc.c 

cli: cli.c 
	yacc -d parser.y
	lex tokens.l
	gcc -o tokens.o -c lex.yy.c
	gcc -o parser.o -c y.tab.c
	gcc -o cli cli.c tokens.o parser.o -I.

clean:
	rm -rf cli
	rm -rf *.o
	rm -rf lex.yy.c
	rm -rf y.tab.c
	rm -rf y.tab.h

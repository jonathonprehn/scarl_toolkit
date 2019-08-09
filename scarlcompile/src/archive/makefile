scarlcompile: lex.yy.o scarlastnode.o scarlcodegenerator.o \
			  scarltypes.o
			  
lex.yy.o: lex.yy.c
	g++ -o lex.yy.o -I. -iy.tab.h -L./../lib -lfl lex.yy.c y.tab.c

lex.yy.c: scarl.l
	flex scarl.l


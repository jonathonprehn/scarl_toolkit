flex scarl.l
yacc -v -d scarl_tokens.y
gcc -o ./../obj/linked_list.o -c linked_list.c
gcc -o ./../obj/stringstack.o -c stringstack.c
gcc -o ./../obj/lex.yy.o -c lex.yy.c
gcc -o ./../obj/y.tab.o -c y.tab.c
gcc -o ./../obj/scarlastnode.o -c scarlastnode.c
gcc -o ./../obj/scarlcodegenerator.o -c scarlcodegenerator.c
gcc -o ./../obj/scarlsymboltable.o -c scarlsymboltable.c
gcc -o ./../obj/scarltypes.o -c scarltypes.c
gcc -o ./../bin/scarlcompile.exe ./../obj/linked_list.o ./../obj/stringstack.o ./../obj/lex.yy.o ./../obj/y.tab.o ./../obj/scarlastnode.o ./../obj/scarlsymboltable.o ./../obj/scarlcodegenerator.o ./../obj/scarltypes.o
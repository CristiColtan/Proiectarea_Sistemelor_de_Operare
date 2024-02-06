run:
	bison -d -Wcounterexamples interpretor.y
	flex interpretor.l
	g++ -Wno-register interpretor.tab.c lex.yy.c -o main

go:
	bison -d interpretor.y
	flex interpretor.l
	g++ -Wno-register interpretor.tab.c lex.yy.c -o main
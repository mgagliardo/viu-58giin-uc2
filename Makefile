all: 
	flex lex.l
	bison -y -d syntax.y
	g++ -std=c++11 lex.yy.c y.tab.c -o compilador

run: all
	./compilador tests/test6
	java -jar ./jasmin-1.1/jasmin.jar output.j
	java test

all: 
	@echo "\nEjecutando el analizador lexico"
	flex lex.l
	@echo "\nEjecutando el analizador Semantico"
	bison -y -d syntax.y
	@echo "\nCreando el compilador"
	g++ -w -std=c++11 lex.yy.c y.tab.c -o compilador

run: all
	@echo "\nEjecutando el test"
	./compilador tests/$(test)
	java -jar ./jasmin.jar output.j
	java test

clean:
	rm -rf y.tab.c y.tab.h test.class output.j lex.yy.c compilador

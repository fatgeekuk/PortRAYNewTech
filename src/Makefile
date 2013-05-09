../bin/dummy_writer: dummy_writer.o vectors.o targa.o
	gcc -o $@ $< vectors.o targa.o -lm

../bin/portray: grammar.o vectors.o targa.o lexer.o
	gcc -o $@ grammar.o vectors.o targa.o lexer.o -lm
	
.c.o:
	gcc -o $@ -g -c -O2 $<

vectors.o: vectors.c

targa.o: targa.c

grammar.c: grammar.y
	bison -o $@ -d grammar.y

grammar.o: grammar.c

dummy_writer.o: dummy_writer.c

lexer.c: lexer.l
	flex -o $@ $<

lexer.o: lexer.c



TESTS=tests/*.c

tester: tester.o Maketests test_index.o test_helper.o tests/*.c all
	gcc -o $@ $< test_index.o test_helper.o tests/*.o -lm

all:
	make -f Maketests all

clean:
	rm unit/teste? || ls
	rm unit/test_index.* || ls

.c.o:
	gcc -o $@ -g -c -O2 $<

test_helper.o: test_helper.c

test_index.o: test_index.c

test_index.c: $(TESTS) build_makefile
	./build_makefile $(TESTS) > Maketests

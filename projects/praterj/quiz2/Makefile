CFLAGS = -Wall -fpic -coverage -lm -O0

testme: testme.c
	gcc -o testme testme.c -g  $(CFLAGS)

test: testme
	./testme

clean:
	rm -f *.o
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f testme



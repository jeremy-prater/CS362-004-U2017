CFLAGS = -Wall -fpic -coverage -lm -O0

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffects.o: cardEffects.h cardEffects.c
	gcc -c cardEffects.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffects.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cardEffects.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cardEffects.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o cardEffects.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest.o: dominion.o rngs.o cardEffects.o unittest/unittest1.c unittest/unittest2.c unittest/unittest3.c unittest/unittest4.c unittest/unittest_framework.c unittest/cardtest1.c unittest/cardtest2.c unittest/cardtest3.c unittest/cardtest4.c
	gcc -o unittest/unittest dominion.o rngs.o cardEffects.o unittest/unittest1.c unittest/unittest2.c unittest/unittest3.c unittest/unittest4.c unittest/unittest_framework.c unittest/cardtest1.c unittest/cardtest2.c unittest/cardtest3.c unittest/cardtest4.c -g $(CFLAGS)

unittests.out: unittest.o
	./unittest/unittest &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	gcov cardEffects.c >> unittestresult.out
	cat cardEffects.c.gcov >> unittestresult.out

randomtest.o: dominion.o rngs.o cardEffects.o randomtest/randomtest_framework.c randomtest/randomtestadventurer.c
	gcc -g $(CFLAGS) -o randomtest/randomtest dominion.o rngs.o cardEffects.o randomtest/randomtest_framework.c randomtest/randomtestadventurer.c

randomtests.out: randomtest.o
	./randomtest/randomtest &> randomtestresult.out
	gcov dominion.c >> randomtestresult.out
	cat dominion.c.gcov >> randomtestresult.out
	gcov cardEffects.c >> randomtestresult.out
	cat cardEffects.c.gcov >> randomtestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cardEffects.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest/unittest

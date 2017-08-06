/*
 * cardtest2.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{

/*
int smith(int currentPlayer, struct gameState *state, int handPos)
{
    int i;
    //+3 Cards
    //for (i = 0; i < 3; i++)
    for (i = 0; i < 4; i++)
	{
	    drawCard(currentPlayer, state);
	}
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
}
*/
    srand(time(NULL));

    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    fprintf(stderr, "********Testing smith()********\n");

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
//		   struct gameState *state);
    int numPlayers;
    do
    {
       numPlayers = rand() % 100;
    } while (numPlayers < 2);
    int randomSeed = rand() % 9999 + 1;    
    
    fprintf(stderr, "numPlayers: %d, randomSeed: %d\n", numPlayers, randomSeed);

    initializeGame(numPlayers, k, randomSeed, g);
    memcpy(test, g, sizeof(struct gameState));

    int handPos = rand() % 1000;
    int currentPlayer;
    do
    {
        currentPlayer = rand() % 100;
    } while (currentPlayer > numPlayers);

//int smith(int currentPlayer, struct gameState *state, int handPos)
    if( smith(currentPlayer, g, handPos) != 0)
        fprintf(stderr,"Bad return value\n");
    else
        fprintf(stderr,"Good return value\n");
    //test the hand count is 3 drawn, 1 discarded
    if(g->handCount[currentPlayer] == test->handCount[currentPlayer]+2)
        fprintf(stderr,"Test 1 passed\n");
    else
        fprintf(stderr,"Incorrect handCount: is %d, should be %d\n", 
            g->handCount[currentPlayer], test->handCount[currentPlayer]+2);

    //test that deck count was decremented by 3
    if(g->deckCount[currentPlayer] == test->deckCount[currentPlayer]-3)
        fprintf(stderr,"Test 2 passed\n");
    else
        fprintf(stderr,"Incorrect deckCount: is %d, should be %d\n",
            g->deckCount[currentPlayer], test->deckCount[currentPlayer]-3);
    
    int secondPlayer;
    do
    {
        secondPlayer = rand() % 100;
    } while (secondPlayer == currentPlayer || secondPlayer > numPlayers);

    //test that othe player not changed
    if(g->handCount[secondPlayer] == test->handCount[secondPlayer])
        fprintf(stderr,"Test 3 passed\n");
    else
        fprintf(stderr,"Other player inappropriately affected\n");

    //trash flag set properly
    if(g->playedCardCount > test->playedCardCount)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Trash flag error\n");

    fprintf(stderr, "********smith() tests complete********\n\n");
}//end main

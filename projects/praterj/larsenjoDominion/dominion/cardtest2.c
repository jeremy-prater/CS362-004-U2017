/*
 * randomtestcard1.c
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    fprintf(stderr, "********Testing smith()********\n");

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
//		   struct gameState *state);

    initializeGame(2, k, 2, g);
    memcpy(test, g, sizeof(struct gameState));

    int handPos = 0;
//int smith(int currentPlayer, struct gameState *state, int handPos)
    if( smith(0, g, handPos) != 0)
        fprintf(stderr,"Bad return value\n");

    //test the hand count is 3 drawn, 1 discarded
    if(g->handCount[0] == test->handCount[0]+2)
        fprintf(stderr,"Test 1 passed\n");
    else
        fprintf(stderr,"Incorrect handCount: is %d, should be %d\n", 
            g->handCount[0], test->handCount[0]+2);

    //test that deck count was decremented by 3
    if(g->deckCount[0] == test->deckCount[0]-3)
        fprintf(stderr,"Test 2 passed\n");
    else
        fprintf(stderr,"Incorrect deckCount: is %d, should be %d\n",
            g->deckCount[0], test->deckCount[0]-3);

    //test that othe player not changed
    if(g->handCount[2] == test->handCount[2])
        fprintf(stderr,"Test 3 passed\n");
    else
        fprintf(stderr,"Other player inappropriately affected\n");

    //trash flag set properly
    if(g->playedCardCount > test->playedCardCount)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Trash flag error\n");

    fprintf(stderr, "********smith() tests complete********\n\n");

}

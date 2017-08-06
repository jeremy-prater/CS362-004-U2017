/*
 * cardtest4.c
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
int greatHall(int currentPlayer, struct gameState *state, int handPos)
{
    //+1 Card
    drawCard(currentPlayer, state);
			
    //+1 Actions
    state->numActions++;
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 1);
    return 0;
}
*/
  
    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    fprintf(stderr, "********Testing greatHall()********\n");

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
//		   struct gameState *state);
    initializeGame(2, k, 2, g);
    memcpy(test, g, sizeof(struct gameState));

    int handPos = 0;

    //int greatHall(int currentPlayer, struct gameState *state, int handPos)
    if(greatHall(0, g, handPos) != 0)
        fprintf(stderr,"Bad return value\n");

    //test the hand count - draw 1, discard 1
    if(g->handCount[0] == test->handCount[0])
        fprintf(stderr,"Test 1 passed\n");
    else
        fprintf(stderr,"Incorrect handCount\n");

    //test that deck count was decremented by 1
    if(g->deckCount[0] == test->deckCount[0]-1)
        fprintf(stderr,"Test 2 passed\n");
    else
        fprintf(stderr,"Incorrect deckCount\n");

    //test that othe player not changed
    if(g->handCount[1] == test->handCount[1])
        fprintf(stderr,"Test 3 passed\n");
    else
        fprintf(stderr,"Other player affected - %d, %d\n", g->handCount[1], test->handCount[1]);

    //test actions incremented by 1
    if(g->numActions == test->numActions+1)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Incorrect number of actions\n");

    //trash flag set properly
    if(g->playedCardCount > test->playedCardCount)
        fprintf(stderr,"Test 5 passed\n");
    else
        fprintf(stderr,"Trash flag error\n");

    fprintf(stderr, "********greatHall() tests complete********\n\n");
}//end main

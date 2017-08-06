/*
 * randomtestcard2.c
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
int vill(int currentPlayer, struct gameState *state, int handPos)
{
    //+1 Card
    drawCard(currentPlayer, state);
			
    //+2 Actions
    state->numActions = state->numActions + 3;
			
    //discard played card from hand
    //discardCard(handPos, currentPlayer, state, 0);
    discardCard(handPos, currentPlayer, state, 0);
}*/
  
    srand(time(NULL) + 2);

    struct gameState* g = malloc(sizeof(struct gameState));
    struct gameState* test = malloc(sizeof(struct gameState));

    fprintf(stderr, "********Testing vill()********\n");

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


    //int vill(int currentPlayer, struct gameState *state, int handPos)
    if( vill(currentPlayer, g, handPos) != 0)
        fprintf(stderr,"Bad return value\n");

    //test the hand count - draw 1, discard 1
    if(g->handCount[currentPlayer] == test->handCount[currentPlayer])
        fprintf(stderr,"Test 1 passed\n");
    else
        fprintf(stderr,"Incorrect handCount\n");

    //test that deck count was decremented by 1
    if(g->deckCount[currentPlayer] == test->deckCount[currentPlayer]-1)
        fprintf(stderr,"Test 2 passed\n");
    else
        fprintf(stderr,"Incorrect deckCount\n");

    int secondPlayer;
    do
    {
        secondPlayer = rand() % 100;
    } while (secondPlayer == currentPlayer || secondPlayer > numPlayers);

    //test that othe player not changed
    if(g->handCount[secondPlayer] == test->handCount[secondPlayer])
        fprintf(stderr,"Test 3 passed\n");
    else
        fprintf(stderr,"Other player affected\n");

    //test actions incremented by 2
    if(g->numActions == test->numActions+2)
        fprintf(stderr,"Test 4 passed\n");
    else
        fprintf(stderr,"Incorrect number of actions\n");

    //trash flag set properly
    if(g->playedCardCount > test->playedCardCount)
        fprintf(stderr,"Test 5 passed\n");
    else
        fprintf(stderr,"Trash flag error\n");

    fprintf(stderr, "********vill() tests complete********\n\n");
}//end main

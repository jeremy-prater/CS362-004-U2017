////////////////////////////////////////////////////////////////////////
//
// Random Card Test 2 - Dominion - cardEffect_Smithy
//
// Random test function : int cardEffect_Smithy(int *currentPlayer, struct gameState *state, int *handPos)
//
// int * currentPlayer - Player ID
// struct gameState * state - Pointer to game state
// int * handPos - hand position to discard
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../cardEffects.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "randomtest.h"

static int testPlayer = 0;

static void clearState(struct gameState * testState)
{
    memset (testState, 0, sizeof (struct gameState));
}

static void addHand(struct gameState * testState, int card)
{
    int handPos = testState->handCount[testPlayer];
    testState->hand[testPlayer][handPos] = card;
    testState->handCount[testPlayer]++;
}

static void addDiscard(struct gameState * testState, int card)
{
    int deckPos = testState->discardCount[testPlayer];
    testState->discard[testPlayer][deckPos] = card;
    testState->discardCount[testPlayer]++;
}

void randomTest_cardSmithy()
{
    LogStart ("Random Test : test_cardSmithy");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    srand(time(NULL));

    /////////////////////////////
    //
    // Random test 2 : Smithy
    //
    int testCounter = 0;
    for (testCounter = 0; testCounter < 100; testCounter++)
    {
        clearState (&testState);
        int cardsToAddHand = (rand() % 6);
        int cardsToAddDiscard = 3 + (rand() % 3);

        int handCard, discardCard;
        for (handCard = 0; handCard < cardsToAddHand; handCard++)
        {
            addHand (&testState, rand() % treasure_map + 2);
        }

        for (discardCard = 0; discardCard < cardsToAddDiscard; discardCard++)
        {
            addDiscard (&testState, rand() % treasure_map + 2);
        }

        addHand (&testState, smithy);
        int handPos = testState.handCount[testPlayer];
        
        cardEffect_Smithy(&testPlayer, & testState, &handPos);

        testPassed |= AssertEq (testState.handCount[testPlayer], cardsToAddHand + 3, "Random Test 2 : Hand has +3 cards");
    }
    AssertEq (0, testPassed, "Random Test 2 : test_cardSmithy\n");
}

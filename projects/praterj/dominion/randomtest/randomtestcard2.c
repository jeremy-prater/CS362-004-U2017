////////////////////////////////////////////////////////////////////////
//
// Random Card Test 2 - Dominion - cardEffect_Mine
//
// Random test function : int cardEffect_Mine(int *currentPlayer, struct gameState *state, int *handPos, int *choice1, int *choice2)

//
// int * currentPlayer - Player ID
// struct gameState * state - Pointer to game state
// int * handPos - hand position to discard
// int * choice1 - treasure card to trash
// int * choice2 - card to gain
//
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

static void addSupply(struct gameState * testState, int card)
{
    testState->supplyCount[card]++;
}

void randomTest_cardMine()
{
    LogStart ("Random Test : test_cardSmithy");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 1;

    srand(time(NULL));

    /////////////////////////////
    //
    // Random test 3 : Mine
    //
    int testCounter = 0;
    for (testCounter = 0; testCounter < 100; testCounter++)
    {
        clearState (&testState);
        int choice1 = -1;
        int choice2 = rand() % (treasure_map + 2);

        int cardsToAddHand = (rand() % 6);
        int cardsToAddSupply = (rand() % 10);

        int handCard, supplyCard;
        for (handCard = 0; handCard < cardsToAddHand; handCard++)
        {
            int newCard = rand() % (treasure_map + 2);
            addHand (&testState, newCard);
            if ((newCard == copper) || (newCard == silver) || (newCard == gold))
            {
                choice1 = handCard;
            }
        }
        
        // Ensure one treasure card exists...
        if (choice1 == -1)
        {
            addHand (&testState, copper);
            choice1 = testState.handCount[testPlayer] - 1;
        }

        for (supplyCard = 0; supplyCard < cardsToAddSupply; supplyCard++)
        {
            addSupply (&testState, rand() % (treasure_map + 1));
        }

        int handPos = testState.handCount[testPlayer];
        addHand (&testState, feast);
        int handCount = choice1;

        cardEffect_Mine(&testPlayer, & testState, &handPos, &choice1, &choice2);
        int localTestPassed = 0;
        localTestPassed |= AssertEq (testState.handCount[testPlayer], handCount + 1, "Random Test 3 : Mine swapped card");
        localTestPassed |= AssertEq (testState.playedCardCount, 2, "Random Test 3 : Two discards");
        if (localTestPassed)
        {
            testPassed = 0;
        }
    }
    AssertEq (0, testPassed, "Random Test 3 : test_cardMine\n");
}

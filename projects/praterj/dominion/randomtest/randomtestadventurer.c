////////////////////////////////////////////////////////////////////////
//
// Random Card Test - Dominion - cardEffect_Adventurer
//
// Random test function : int cardEffect_Adventurer(int *drawntreasure, struct gameState *state, int *currentPlayer, int *cardDrawn, int *temphand, int *z)
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

static void addDeck(struct gameState * testState, int card, int playerID)
{
    int deckPos = testState->deckCount[playerID];
    testState->deck[playerID][deckPos] = card;
    testState->deckCount[playerID]++;
}

static void addDiscard(struct gameState * testState, int card)
{
    int deckPos = testState->discardCount[testPlayer];
    testState->discard[testPlayer][deckPos] = card;
    testState->discardCount[testPlayer]++;
}

void randomTest_cardAdventurer()
{
    LogStart ("Random Test : test_cardAdventurer");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    srand(time(NULL));

    /////////////////////////////
    //
    // Random test 1 : Add to deck
    //

    clearState (&testState);
    int treasureCards = 0;
    while (treasureCards < 2)
    {
        int newCard = rand() % (treasure_map + 1);
        addDeck(&testState, newCard, testPlayer);
        if ((newCard == copper) || (newCard == silver) || (newCard == gold))
        {
            treasureCards++;
        }
    }

    // These should be internal to the cardEffect_Adventurer function
    int drawnTreasure = 0;
    int z = 0;
    int cardDrawn = 0;
    int tempHand[MAX_HAND];

    cardEffect_Adventurer(&drawnTreasure, &testState, &testPlayer, &cardDrawn, tempHand, &z);

    treasureCards = 0;
    testPassed |= AssertEq (2, testState.handCount[testPlayer], "Random Test : 2 cards in hand -- buffer underrun probably occured!");
    for (int cardIndex = 0; ((cardIndex < testState.handCount[testPlayer]) && (testPassed == 0)); cardIndex++)
    {
        int testCard = testState.hand[testPlayer][cardIndex];
        if ((testCard == copper) || (testCard == silver) || (testCard == gold))
        {
            treasureCards++;
        }
    }
    testPassed |= AssertEq (2, treasureCards, "Random Test 1 : 2 treasure cards in hand");

    /////////////////////////////
    //
    // Random test 2 : Add to discard
    //

    clearState (&testState);
    treasureCards = 0;
    while (treasureCards < 2)
    {
        int newCard = rand() % (treasure_map + 1);
        addDiscard(&testState, newCard);
        addDeck(&testState, newCard, testPlayer + 1);
        if ((newCard == copper) || (newCard == silver) || (newCard == gold))
        {
            treasureCards++;
        }
    }

    // These should be internal to the cardEffect_Adventurer function
    drawnTreasure = 0;
    z = 0;
    cardDrawn = 0;

    cardEffect_Adventurer(&drawnTreasure, &testState, &testPlayer, &cardDrawn, tempHand, &z);

    treasureCards = 0;
    testPassed |= AssertEq (2, testState.handCount[testPlayer], "Random Test : 2 cards in hand -- buffer underrun probably occured!");
    for (int cardIndex = 0; ((cardIndex < testState.handCount[testPlayer]) && (testPassed == 0)); cardIndex++)
    {
        int testCard = testState.hand[testPlayer][cardIndex];
        if ((testCard == copper) || (testCard == silver) || (testCard == gold))
        {
            treasureCards++;
        }
    }
    testPassed |= AssertEq (2, treasureCards, "Random Test : 2 treasure cards in hand");

    AssertEq (0, testPassed, "Random Test 2 : test_cardAdventurer\n");
}

////////////////////////////////////////////////////////////////////////
//
// Card Test 2 - Dominion - cardEffect_Adventurer
//
// Test function : int cardEffect_Adventurer(int *drawntreasure, struct gameState *state, int *currentPlayer, int *cardDrawn, int *temphand, int *z)
//
// int * currentPlayer - Player ID
// struct gameState * state - Pointer to game state
// int * handPos - hand position to discard
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

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

static void addDeck(struct gameState * testState, int card)
{
    int deckPos = testState->deckCount[testPlayer];
    testState->deck[testPlayer][deckPos] = card;
    testState->deckCount[testPlayer]++;
}

void test_cardAdventurer()
{
    LogStart ("Unit Test: test_cardAdventurer");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : Add 4 cards to deck, add 3 cards to hand, execute adventurer
    //
    clearState (&testState);
    addHand(&testState, copper);
    addHand(&testState, silver);
    addHand(&testState, gold);
    addHand(&testState, adventurer);

    addDeck(&testState, great_hall);
    addDeck(&testState, silver);
    addDeck(&testState, baron);
    addDeck(&testState, curse);
    addDeck(&testState, gold);

    // These should be internal to the cardEffect_Adventurer function
    int drawnTreasure = 0;
    int z = 0;
    int cardDrawn = 0;
    int tempHand[MAX_HAND];

    cardEffect_Adventurer(&drawnTreasure, &testState, &testPlayer, &cardDrawn, tempHand, &z);

    testPassed |= AssertEq (5, testState.handCount[testPlayer], "Test 1 : handCount == 5");
    testPassed |= AssertEq (copper, testState.hand[testPlayer][0], "Test 1 : hand[0] == copper");
    testPassed |= AssertEq (silver, testState.hand[testPlayer][1], "Test 1 : hand[1] == silver");
    testPassed |= AssertEq (gold, testState.hand[testPlayer][2], "Test 1 : hand[2] == gold");
    testPassed |= AssertEq (adventurer, testState.hand[testPlayer][3], "Test 1 : hand[3] == adventurer");
    testPassed |= AssertEq (silver, testState.hand[testPlayer][5], "Test 1 : hand[5] == silver");
    testPassed |= AssertEq (gold, testState.hand[testPlayer][4], "Test 1 : hand[4] == gold");

    AssertEq (0, testPassed, "Unit Test: cardEftest_cardAdventurerfect_Smithy\n");
}

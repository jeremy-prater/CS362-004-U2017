////////////////////////////////////////////////////////////////////////
//
// Card Test 1 - Dominion - cardEffect_Smithy
//
// Test function : int cardEffect_Smithy(int *currentPlayer, struct gameState *state, int *handPos)
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

void test_cardSmithy()
{
    LogStart ("Unit Test: cardEffect_Smithy");

    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : Add 4 cards to deck, add 3 cards to hand, execute Smithy
    //
    clearState (&testState);
    addHand(&testState, copper);
    addHand(&testState, silver);
    addHand(&testState, gold);
    addHand(&testState, smithy);

    addDeck(&testState, great_hall);
    addDeck(&testState, baron);
    addDeck(&testState, treasure_map);
    addDeck(&testState, curse);

    int handPos = 3;

    smith(testPlayer, &testState, handPos);

    testPassed |= AssertEq (6, testState.handCount[testPlayer], "Test 1 : Handcount == 6");
    testPassed |= AssertEq (copper, testState.hand[testPlayer][0], "Test 1 : hand[0] == copper");
    testPassed |= AssertEq (silver, testState.hand[testPlayer][1], "Test 1 : hand[1] == silver");
    testPassed |= AssertEq (gold, testState.hand[testPlayer][2], "Test 1 : hand[2] == gold");
    testPassed |= AssertEq (great_hall, testState.hand[testPlayer][3], "Test 1 : hand[3] == great_hall");
    testPassed |= AssertEq (treasure_map, testState.hand[testPlayer][5], "Test 1 : hand[5] == treasure_map");
    testPassed |= AssertEq (curse, testState.hand[testPlayer][4], "Test 1 : hand[4] == curse");

    AssertEq (0, testPassed, "Unit Test: cardEffect_Smithy\n");
}

////////////////////////////////////////////////////////////////////////
//
// Unit Test 3 - Dominion
//
// Test function : int updateCoins(int player, struct gameState *state, int bonus)
//
// int player - Player ID
// struct gameState * state - Pointer to game state
// int bonus - Extra bonus to add on top of treasure cards in hand
//
// Return value Always 0
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

static int testPlayer = 0;

static void clearHand(struct gameState * testState)
{
    memset (testState, 0, sizeof (struct gameState));
}

static void addHand(struct gameState * testState, int card)
{
    int handPos = testState->handCount[testPlayer];
    testState->hand[testPlayer][handPos] = card;
    testState->handCount[testPlayer]++;
}

void test_updateCoins()
{
    LogStart ("Unit Test: updateCoins");
    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : 3 copper in hand
    //
    // Result : coins == 3
    //
    clearHand(&testState);
    addHand(&testState, copper);
    addHand(&testState, copper);
    addHand(&testState, copper);
    updateCoins(testPlayer, &testState, 0);
    testPassed |= AssertEq (3, testState.coins, "Test 1 : 3 copper in hand, coins = 3");

    /////////////////////////////
    //
    // Test 2 : 3 copper in hand
    //
    // Result : coins == 6
    //
    clearHand(&testState);
    addHand(&testState, silver);
    addHand(&testState, silver);
    addHand(&testState, silver);
    updateCoins(testPlayer, &testState, 0);
    testPassed |= AssertEq (6, testState.coins, "Test 2 : 3 silver in hand, coins = 6");

    /////////////////////////////
    //
    // Test 3 : 1 copper in hand
    //
    // Result : coins == 9
    //
    clearHand(&testState);
    addHand(&testState, gold);
    addHand(&testState, gold);
    addHand(&testState, gold);
    updateCoins(testPlayer, &testState, 0);
    testPassed |= AssertEq (9, testState.coins, "Test 3 : 3 gold in hand, coins = 9");

    /////////////////////////////
    //
    // Test 4 : 10 bonus
    //
    // Result : coins == 10
    //
    clearHand(&testState);
    updateCoins(testPlayer, &testState, 10);
    testPassed |= AssertEq (10, testState.coins, "Test 4 : 10 bonus, coins = 10)");
   
    AssertEq (0, testPassed, "Unit Test: updateCoins\n");
}

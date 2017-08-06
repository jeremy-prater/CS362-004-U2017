////////////////////////////////////////////////////////////////////////
//
// Unit Test 3 - Dominion
//
// Test function : int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
//
// int supplyPos - enum of chosen card
// int player - Player ID
// struct gameState * state - Pointer to game state
// int toFlag - 0 : add to discard
// int toFlag - 1 : add to deck
// int toFlag - 2 : add to hand
//
// Return value -1 if pile is empty or card is not in game, 0 on success
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

static int testPlayer = 0;
static int testCard = great_hall;

static void clearSupply(struct gameState * testState)
{
    memset (testState, 0, sizeof (struct gameState));
}

static void addSupply(struct gameState * testState, int card)
{
    testState->supplyCount[card]++;
}

void test_gainCard()
{
    LogStart ("Unit Test: gainCard");
    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    int testPassed = 0;
    int result;

    /////////////////////////////
    //
    // Test 1 : Request card not in supply
    //
    // Result : Returns (-1)
    //
    clearSupply(&testState);
    //addSupply(&testState, copper);
    result = gainCard(copper, &testState, 0, testPlayer);
    testPassed |= AssertEq (-1, result, "Test 1 : Requested card not in supply");

    /////////////////////////////
    //
    // Test 2 : Request invalid card
    //
    // Result : Returns (-1)
    //
    clearSupply(&testState);
    //addSupply(&testState, copper);
    result = gainCard(treasure_map + 1, &testState, 0, testPlayer);
    testPassed |= AssertEq (-1, result, "Test 2 : Requested card is invalid");

    /////////////////////////////
    //
    // Test 3 : gainCard to discard
    //
    // Add two testCards, remove one, check state, remove second, check state.
    //
    // Result : Requested card goes to discard
    //
    clearSupply(&testState);
    addSupply(&testState, testCard);
    addSupply(&testState, testCard);
    result = gainCard(testCard, &testState, 0, testPlayer);
    testPassed |= AssertEq (0, result, "Test 3 : Requested card to discard");
    testPassed |= AssertEq (1, testState.supplyCount[testCard], "Test 3 : supplyCound[testCard] = 1");
    testPassed |= AssertEq (1, testState.discardCount[testPlayer], "Test 3 : discardCount = 1");
    testPassed |= AssertEq (testCard, testState.discard[testPlayer][0], "Test 3 : discard[0] = testCard");
    result = gainCard(testCard, &testState, 0, testPlayer);
    testPassed |= AssertEq (0, result, "Test 3 : Requested card to discard");
    testPassed |= AssertEq (0, testState.supplyCount[testCard], "Test 3 : supplyCound[testCard] = 0");
    testPassed |= AssertEq (2, testState.discardCount[testPlayer], "Test 3 : discardCount = 2");
    testPassed |= AssertEq (testCard, testState.discard[testPlayer][1], "Test 3 : discard[0] = testCard");

    /////////////////////////////
    //
    // Test 4 : gainCard to deck
    //
    // Add two testCards, remove one, check state, remove second, check state.
    //
    // Result : Requested card goes to deck
    //
    clearSupply(&testState);
    addSupply(&testState, testCard);
    addSupply(&testState, testCard);
    result = gainCard(testCard, &testState, 1, testPlayer);
    testPassed |= AssertEq (0, result, "Test 4 : Requested card to discard");
    testPassed |= AssertEq (1, testState.supplyCount[testCard], "Test 4 : supplyCound[testCard] = 1");
    testPassed |= AssertEq (1, testState.deckCount[testPlayer], "Test 4 : deckCount = 1");
    testPassed |= AssertEq (testCard, testState.deck[testPlayer][0], "Test 4 : deck[0] = testCard");
    result = gainCard(testCard, &testState, 1, testPlayer);
    testPassed |= AssertEq (0, result, "Test 4 : Requested card to discard");
    testPassed |= AssertEq (0, testState.supplyCount[testCard], "Test 4 : supplyCound[testCard] = 0");
    testPassed |= AssertEq (2, testState.deckCount[testPlayer], "Test 4 : deckCount = 2");
    testPassed |= AssertEq (testCard, testState.deck[testPlayer][1], "Test 4 : deck[0] = testCard");

    /////////////////////////////
    //
    // Test 5 : gainCard to hand
    //
    // Add two testCards, remove one, check state, remove second, check state.
    //
    // Result : Requested card goes to hand
    //
    clearSupply(&testState);
    addSupply(&testState, testCard);
    addSupply(&testState, testCard);
    result = gainCard(testCard, &testState, 2, testPlayer);
    testPassed |= AssertEq (0, result, "Test 5 : Requested card to discard");
    testPassed |= AssertEq (1, testState.supplyCount[testCard], "Test 5 : supplyCound[testCard] = 1");
    testPassed |= AssertEq (1, testState.handCount[testPlayer], "Test 5 : handCount = 1");
    testPassed |= AssertEq (testCard, testState.hand[testPlayer][0], "Test 5 : hand[0] = testCard");
    result = gainCard(testCard, &testState, 2, testPlayer);
    testPassed |= AssertEq (0, result, "Test 5 : Requested card to discard");
    testPassed |= AssertEq (0, testState.supplyCount[testCard], "Test 5 : supplyCound[testCard] = 0");
    testPassed |= AssertEq (2, testState.handCount[testPlayer], "Test 5 : handCount = 2");
    testPassed |= AssertEq (testCard, testState.hand[testPlayer][1], "Test 5 : hand[0] = testCard");
   
    AssertEq (0, testPassed, "Unit Test: gainCard\n");
}

////////////////////////////////////////////////////////////////////////
//
// Unit Test 1 - Dominion
//
// Test function : int drawCard(int player, struct gameState *state);
//
// int player - Player ID
// struct gameState * state - Pointer to game state
//
// Return value -1 if deckCounter is 0, 0 if deckCounter != 0
//

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "unittest.h"

void test_drawCard()
{
    LogStart ("Unit Test: drawCard");
    /////////////////////////////
    //
    // Initalize a gameState for testing.
    //

    struct gameState testState;
    memset (&testState, 0, sizeof (struct gameState));
    int testPlayer = 0;
    int result;
    int testPassed = 0;

    /////////////////////////////
    //
    // Test 1 : Empty Deck, Empty discard pile.
    //
    // Result : Should return (-1) due to no cards.
    //
    result = drawCard (testPlayer, &testState);
    testPassed |= AssertEq (result, -1, "Test 1 : Empty Deck, Empty discard pile.");

    /////////////////////////////
    //
    // Test 2 : Empty Deck, Non empty discard pile.
    //
    // Result : Should return (0) with great_hall in hand
    //
    memset (&testState, 0, sizeof (struct gameState));
    testState.discardCount[testPlayer] = 1;
    testState.discard[testPlayer][0] = great_hall;
    result = drawCard (testPlayer, &testState);
    testPassed |= AssertEq (result, 0, "Test 2 : Empty Deck, Non empty discard pile.");
    testPassed |= AssertEq (great_hall, testState.hand[testPlayer][0], "Test 2 : great_hall is in hand[0].");

    /////////////////////////////
    //
    // Test 3 : Empty Hand, Non empty Deck
    //
    // Result : Should return (0) with baron in hand
    //
    memset (&testState, 0, sizeof (struct gameState));
    testState.deckCount[testPlayer] = 1;
    testState.deck[testPlayer][0] = baron;
    result = drawCard (testPlayer, &testState);
    testPassed |= AssertEq (result, 0, "Test 3 : Empty Hand, Non empty Deck");
    testPassed |= AssertEq (baron, testState.hand[testPlayer][0], "Test 3 : baron is in hand[0].");

    /////////////////////////////
    //
    // Test 4 : Non empty Hand, Non empty Deck
    //
    // Result : Should return (0) with baron and great_hall in hand
    //
    memset (&testState, 0, sizeof (struct gameState));
    testState.deck[testPlayer][0] = great_hall;
    testState.deckCount[testPlayer] = 1;

    testState.hand[testPlayer][0] = baron;
    testState.handCount[testPlayer] = 1;
    result = drawCard (testPlayer, &testState);
    testPassed |= AssertEq (result, 0, "Test 4 : Non empty Hand, Non empty Deck");
    testPassed |= AssertEq (baron, testState.hand[testPlayer][0], "Test 4 : baron is in hand[0].");
    testPassed |= AssertEq (great_hall, testState.hand[testPlayer][1], "Test 4 : great_hall is in hand[1].");
    
    AssertEq (testPassed, 0, "Unit Test: drawCard\n");
}

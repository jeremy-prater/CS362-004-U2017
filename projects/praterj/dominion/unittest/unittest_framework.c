#include "unittest.h"

int main()
{
    printf ("Starting Dominion Unit Tests...\n\n");

    test_drawCard();
    test_discardCard();
    test_updateCoins();
    test_gainCard();

    test_cardSmithy();
    test_cardAdventurer();
    test_cardCouncilRoom();
    test_cardFeast();

    return 0;
}

int AssertEq (int a, int b, const char * tag)
{
    int passed = (a == b);
    printf ("[%s] %s\n", (passed) ? PASSED : FAILED, tag);
    if (!passed)
    {
        printf ("[%s] %d expected, got %d\n", (passed) ? PASSED : FAILED, a, b);
    }
    return !passed;
}

void LogStart(const char * tag)
{
    printf ("\n[GO--->] %s\n", tag);
}

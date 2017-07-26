#include "randomtest.h"

int main()
{
    printf ("Starting Dominion Random Tests...\n\n");

    randomTest_cardAdventurer();
    
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

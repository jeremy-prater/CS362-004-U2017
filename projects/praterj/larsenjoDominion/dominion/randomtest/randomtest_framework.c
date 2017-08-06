#include "randomtest.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf ("Please specify a card test to run (0, 1, 2)...\n\n");
        return -1;
    }
    printf ("Starting Dominion Random Tests...\n\n");

    int cardTest = atoi (argv[1]);

    switch (cardTest)
    {
        case 1: randomTest_cardAdventurer(); break;
        case 2: randomTest_cardSmithy(); break;
        //case 3: randomTest_cardMine(); break;
    }
    
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

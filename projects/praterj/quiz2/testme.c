#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define BUFFER_LENGTH 6

static char buffer[BUFFER_LENGTH];

char getAlphaChar(char min, char max)
{
  // Return an ASCII set between min and max
  char delta = max - min;
  return (rand() % (delta + 1)) + min;
}

char inputChar()
{
    // Return an ASCII set between 0x20 ' ' and 0x7D '}'
    return getAlphaChar(' ', '}');
}

char *inputString()
{
    int index = 0;
    for (index = 0; index < BUFFER_LENGTH - 1; index++)
    {
      // Return an ASCII set between 0x65 'e' and 0x74 't'
      buffer[index] = getAlphaChar('e', 't');
    }

    buffer[BUFFER_LENGTH - 1] = 0x00;
    return buffer;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

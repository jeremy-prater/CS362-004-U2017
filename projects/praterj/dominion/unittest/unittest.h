#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UNITTEST_H
#define UNITTEST_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define PASSED "PASSED"
#define FAILED "FAILED"

void test_drawCard();
void test_discardCard();
void test_updateCoins();
void test_gainCard();

int AssertEq (int a, int b, const char * tag);
void LogStart(const char * tag);

#endif // UNITTEST_H
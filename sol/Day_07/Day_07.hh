#ifndef __DAY_7_HEADER_H__
#define __DAY_7_HEADER_H__
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

typedef enum
{
    HIGH_CARD = 0,   // 1, 1, 1, 1, 1
    ONE_PAIR,        // 1, 1, 1, 2
    TWO_PAIR,        // 1, 2, 2
    THREE_OF_A_KIND, // 1, 1, 3
    FULL_HOUSE,      // 2, 3
    FOUR_OF_A_KIND,  // 1, 4
    FIVE_OF_A_KIND   // 5
} CARD_TYPE;

typedef struct CARD
{
    vector<int> value;
    int         bid;
} CARD;

int day7(int argc, char **argv, string input, bool runTest);

#endif
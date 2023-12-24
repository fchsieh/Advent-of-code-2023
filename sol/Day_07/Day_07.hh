#ifndef __HEADER_H__
#define __HEADER_H__
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

unordered_map<char, int> LABEL_P1 = {
    {'2',  0},
    {'3',  1},
    {'4',  2},
    {'5',  3},
    {'6',  4},
    {'7',  5},
    {'8',  6},
    {'9',  7},
    {'T',  8},
    {'J',  9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

unordered_map<char, int> LABEL_P2 = {
    {'J', -1},
    {'2',  0},
    {'3',  1},
    {'4',  2},
    {'5',  3},
    {'6',  4},
    {'7',  5},
    {'8',  6},
    {'9',  7},
    {'T',  8},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

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

uint64_t solve_1(const string &input);
uint64_t solve_2(const string &input);

#endif
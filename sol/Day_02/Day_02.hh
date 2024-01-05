#ifndef __DAY_2_HEADER_H__
#define __DAY_2_HEADER_H__
#include "../../lib/helper.cc"
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

typedef enum
{
    RED = 0,
    BLUE,
    GREEN
} CUBES;

int day2(int argc, char **argv, string input, bool runTest);

#endif
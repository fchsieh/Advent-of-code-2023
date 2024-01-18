#ifndef __DAY_20_HEADER_H__
#define __DAY_20_HEADER_H__
#include "../../lib/helper.cc"
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

enum MODULETYPE
{
    FLIPFLOP = 0,
    CONJUNCTION,
    BROADCASTER
};

enum PULSE
{
    LOW = 0, // equivalent to "OFF"
    HIGH     // equivalent to "ON"
};

#define STATE_OFF LOW
#define STATE_ON  HIGH

int day20(int argc, char **argv, string input, bool runTest);

#endif
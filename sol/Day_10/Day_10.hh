#ifndef __HEADER_H__
#define __HEADER_H__
#include "../../lib/helper.cc"
#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

enum DIRECTIONS
{
    SOUTH = 0,
    NORTH,
    EAST,
    WEST
};

#define ROW  agent[0]
#define COL  agent[1]
#define FROM agent[2]

// |
#define PIPE_VERTICAL                                                          \
    [](vector<int> &agent) { ROW = (FROM == SOUTH) ? (ROW - 1) : (ROW + 1); }
// -
#define PIPE_HORIZONTAL                                                        \
    [](vector<int> &agent) { COL = (FROM == WEST) ? (COL + 1) : (COL - 1); }
// L
#define PIPE_NORTH_EAST                                                        \
    [](vector<int> &agent) {                                                   \
        COL  = (FROM == NORTH) ? (COL + 1) : COL;                              \
        ROW  = (FROM == EAST) ? (ROW - 1) : ROW;                               \
        FROM = (FROM == NORTH) ? WEST : SOUTH;                                 \
    }
// J
#define PIPE_NORTH_WEST                                                        \
    [](vector<int> &agent) {                                                   \
        COL  = (FROM == NORTH) ? (COL - 1) : COL;                              \
        ROW  = (FROM == WEST) ? (ROW - 1) : ROW;                               \
        FROM = (FROM == NORTH) ? EAST : SOUTH;                                 \
    }
// 7
#define PIPE_SOUTH_WEST                                                        \
    [](vector<int> &agent) {                                                   \
        COL  = (FROM == SOUTH) ? (COL - 1) : COL;                              \
        ROW  = (FROM == WEST) ? (ROW + 1) : ROW;                               \
        FROM = (FROM == SOUTH) ? EAST : NORTH;                                 \
    }
// F
#define PIPE_SOUTH_EAST                                                        \
    [](vector<int> &agent) {                                                   \
        COL  = (FROM == SOUTH) ? (COL + 1) : COL;                              \
        ROW  = (FROM == EAST) ? (ROW + 1) : ROW;                               \
        FROM = (FROM == SOUTH) ? WEST : NORTH;                                 \
    }

uint64_t solve_1(const string &input);
int64_t  solve_2(const string &input);

#endif
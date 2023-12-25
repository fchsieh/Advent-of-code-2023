#ifndef __HEADER_H__
#define __HEADER_H__
#include <bits/stdc++.h>
#include <cstdint>
#include <gtest/gtest.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

#define L 0
#define R 1

#define DIR_CHAR_TO_INT(x) (x == 'L') ? L : R
#define FINISH_ITER(arr)                                                       \
    (all_of(arr.begin(), arr.end(), [](string s) { return s[2] == 'Z'; }))

uint64_t solve_1(const string &input);
uint64_t solve_2(const string &input);

#endif
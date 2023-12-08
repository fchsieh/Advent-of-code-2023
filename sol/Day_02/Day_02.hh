#ifndef __HEADER_H__
#define __HEADER_H__
#include <bits/stdc++.h>
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

int solve_1(const string &input);
int solve_2(const string &input);

#endif
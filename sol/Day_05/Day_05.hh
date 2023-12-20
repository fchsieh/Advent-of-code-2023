#ifndef __HEADER_H__
#define __HEADER_H__
#include "../../lib/ThreadPool.hh"
#include "../../lib/helper.hh"
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <pthread.h>
using namespace std;

#define OK    0
#define ERROR 1
#define TRUE  1
#define FALSE 0

uint64_t solve_1(const string &input);
uint64_t solve_2(const string &input);

#endif
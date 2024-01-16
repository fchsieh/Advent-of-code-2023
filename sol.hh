#ifndef __ALL_HEADERS__
#define __ALL_HEADERS__

#include "sol/Day_01/Day_01.hh"
#include "sol/Day_02/Day_02.hh"
#include "sol/Day_03/Day_03.hh"
#include "sol/Day_04/Day_04.hh"
#include "sol/Day_05/Day_05.hh"
#include "sol/Day_06/Day_06.hh"
#include "sol/Day_07/Day_07.hh"
#include "sol/Day_08/Day_08.hh"
#include "sol/Day_09/Day_09.hh"
#include "sol/Day_10/Day_10.hh"
#include "sol/Day_11/Day_11.hh"
#include "sol/Day_12/Day_12.hh"
#include "sol/Day_13/Day_13.hh"
#include "sol/Day_14/Day_14.hh"
#include "sol/Day_15/Day_15.hh"
#include "sol/Day_16/Day_16.hh"
#include "sol/Day_17/Day_17.hh"
#include "sol/Day_18/Day_18.hh"
#include "sol/Day_19/Day_19.hh"
// TMP_H

unordered_map<int, int (*)(int, char **, string, bool)> dayMap = {
    { 1,  &day1},
    { 2,  &day2},
    { 3,  &day3},
    { 4,  &day4},
    { 5,  &day5},
    { 6,  &day6},
    { 7,  &day7},
    { 8,  &day8},
    { 9,  &day9},
    {10, &day10},
    {11, &day11},
    {12, &day12},
    {13, &day13},
    {14, &day14},
    {15, &day15},
    {16, &day16},
    {17, &day17},
    {18, &day18},
    {19, &day19},
 // TMP_ENTRY
};

#endif
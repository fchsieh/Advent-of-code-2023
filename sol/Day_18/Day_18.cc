#include "Day_18.hh"
#include <cstdint>
#include <sstream>
#include <string>

int64_t countArea(vector<pair<int, int>> &vertices)
{
    int64_t area = 0;
    // calculate the area using shoelace formula
    // I = 1/2 * sum((x_i * y_i+1) - (x_i+1 * y_i))
    for (int i = 0; i < (int)vertices.size(); i++)
    {
        auto [currR, currC] = vertices[i];
        auto [nextR, nextC] = vertices[(i + 1) % vertices.size()];
        area += (currR + nextR) * (nextC - currC);
    }
    // Pick's theorem:   A = i + b/2 - 1
    return abs(area) / 2 + vertices.size() / 2 + 1;
}

static uint64_t solve_1(const string &input)
{
    stringstream           ss(input);
    string                 line, dir, stepCount, ignore;
    int                    r = 0, c = 0;
    vector<pair<int, int>> vertices;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        ssLine >> dir >> stepCount >> ignore;
        int steps = stoi(stepCount);

        for (int i = 0; i < steps; i++)
        {
            if (dir == "R")
                c++;
            else if (dir == "L")
                c--;
            else if (dir == "U")
                r--;
            else if (dir == "D")
                r++;
            vertices.push_back({r, c});
        }
    }

    return countArea(vertices);
}

static uint64_t solve_2(const string &input)
{
    stringstream           ss(input);
    string                 line, ignore, hexCode;
    long long              r = 0, c = 0;
    vector<pair<int, int>> vertices;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        ssLine >> ignore >> ignore >> hexCode;
        // decode the steps and dir from color
        int64_t hexValue = stoi(hexCode.substr(2, hexCode.size() - 3), 0, 16);
        int64_t steps    = hexValue >> 4;
        int64_t dir      = hexValue & 0xF;

        for (int64_t i = 0; i < steps; i++)
        {
            if (dir == 0) // R
                c++;
            else if (dir == 1) // D
                r++;
            else if (dir == 2) // L
                c--;
            else if (dir == 3) // U
                r--;
            vertices.push_back({r, c});
        }
    }

    return countArea(vertices);
}

static string
    testStr = "R 6 (#70c710)\nD 5 (#0dc571)\nL 2 (#5713f0)\nD 2 "
              "(#d2c081)\nR 2 (#59c680)\nD 2 (#411b91)\nL 5 (#8ceee2)\nU 2 "
              "(#caa173)\nL 1 (#1b58a2)\nU 2 (#caa171)\nR 2 (#7807d2)\nU 3 "
              "(#a77fa3)\nL 2 (#015232)\nU 2 (#7a21e3)\n";

TEST(Aoc2023Test_day18, Problem1)
{
    EXPECT_EQ(62, solve_1(testStr));
}

TEST(Aoc2023Test_day18, Problem2)
{
    EXPECT_EQ(952408144115, solve_2(testStr));
}

int day18(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day18.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
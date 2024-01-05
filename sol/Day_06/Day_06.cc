#include "Day_06.hh"

using namespace std;

uint64_t ways(uint64_t time, uint64_t dist)
{
    uint64_t way = 0;
    for (uint64_t speed = 1; speed < time; speed++)
    {
        int      remain  = time - speed;
        uint64_t maxDist = speed * remain;
        if (maxDist > dist)
            way++;
    }
    return way;
}

static uint64_t solve_1(const string &input)
{
    stringstream                     ss(input);
    string                           line, tok;
    vector<pair<uint64_t, uint64_t>> races;
    bool                             isTime = true;
    uint64_t                         ans    = 1;
    int                              idx    = 0;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            if (!isdigit(tok[0]))
                continue;
            if (isTime)
            {
                races.push_back({stoull(tok), 0});
            }
            else // is distance
            {
                races[idx].second = stoull(tok);
                idx++;
            }
        }
        isTime = false;
    }

    for (auto &[t, d] : races)
    {
        uint64_t possibleWays = ways(t, d);
        if (possibleWays != 0)
            ans *= possibleWays;
    }

    return ans;
}

static uint64_t solve_2(const string &input)
{
    stringstream ss(input);
    string       line, tok, timeTok = "", distTok = "";
    uint64_t     time, dist;
    bool         isTime = true;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            if (!isdigit(tok[0]))
                continue;
            if (isTime)
                timeTok += tok;
            else
                distTok += tok;
        }
        isTime = false;
    }
    time = stoull(timeTok);
    dist = stoull(distTok);

    return ways(time, dist);
}

string testStr = "Time:      7  15   30\nDistance:  9  40  200";

TEST(Aoc2023Test_day6, Problem1)
{
    EXPECT_EQ(288, solve_1(testStr));
}

TEST(Aoc2023Test_day6, Problem2)
{
    EXPECT_EQ(71503, solve_2(testStr));
}

int day6(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day6.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
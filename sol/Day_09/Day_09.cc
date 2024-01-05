#include "Day_09.hh"

int64_t computeDiff(vector<int64_t> &arr, bool part2)
{
    adjacent_difference(arr.begin(), arr.end(), arr.begin());
    arr.erase(arr.begin());
    return part2 ? arr.front() : arr.back();
}

static int64_t solve_1(const string &input)
{
    stringstream    ss(input);
    string          line, tok;
    vector<int64_t> currLine;
    int64_t         currLast = 0;
    int64_t         ans      = 0;

    while (getline(ss, line))
    {
        currLine.clear();
        currLast = 0;

        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            currLine.push_back(stoll(tok));
        }

        currLast = currLine.back();
        while (!CHECK_ARR_IDENTITY(currLine))
        {
            currLast += computeDiff(currLine, false);
        }
        ans += currLast;
    }

    return ans;
}

static int64_t solve_2(const string &input)
{
    stringstream    ss(input);
    string          line, tok;
    vector<int64_t> currLine;
    stack<int64_t>  frontRecord;
    int64_t         currFirst = 0, ans = 0;

    while (getline(ss, line))
    {
        currLine.clear();
        currFirst = 0;

        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            currLine.push_back(stoll(tok));
        }

        while (!CHECK_ARR_IDENTITY(currLine))
        {
            frontRecord.push(currLine.front());
            currFirst = computeDiff(currLine, true);
        }
        while (!frontRecord.empty())
        {
            currFirst = frontRecord.top() - currFirst;
            frontRecord.pop();
        }
        ans += currFirst;
    }

    return ans;
}

TEST(Aoc2023Test_day9, Problem1)
{
    string testStr = "0 3 6 9 12 15\n1 3 6 10 15 21\n10 13 16 21 30 45\n";
    EXPECT_EQ(114, solve_1(testStr));
}

TEST(Aoc2023Test_day9, Problem2)
{
    string testStr = "10 13 16 21 30 45\n";
    EXPECT_EQ(5, solve_2(testStr));
}

int day9(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day9.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
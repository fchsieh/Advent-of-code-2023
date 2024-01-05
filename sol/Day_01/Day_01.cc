#include "Day_01.hh"

using namespace std;

#define FIND_DIGIT [](char c) { return std::isdigit(c) && c != '0'; }

static int solve_1(const string &input)
{
    stringstream ss(input);
    int          ans   = 0;
    int          first = 0, last = 0;
    string       line;

    while (getline(ss, line))
    {
        string numsOnly = regex_replace(line, regex("[^0-9]"),
                                        std::string("$1"));

        first = numsOnly[0] - '0';
        last  = numsOnly[numsOnly.length() - 1] - '0';
        ans += first * 10 + last;
    }
    return ans;
}

static int solve_2(const string &input)
{
    stringstream               ss(input);
    int                        ans   = 0;
    int                        first = 0, last = 0;
    string                     line;
    unordered_map<string, int> dict = {
        {  "one", 1},
        {  "two", 2},
        {"three", 3},
        { "four", 4},
        { "five", 5},
        {  "six", 6},
        {"seven", 7},
        {"eight", 8},
        { "nine", 9}
    };

    while (getline(ss, line))
    {
        // num, pos
        pair<int, int> firstDigit = {-1, INT_MAX};
        pair<int, int> lastDigit  = {-1, INT_MIN};
        pair<int, int> firstStr   = {-1, INT_MAX};
        pair<int, int> lastStr    = {-1, INT_MIN};
        // parse str
        for (auto &[cand, val] : dict)
        {
            size_t pos;
            if ((pos = line.find(cand)) != string::npos)
            {
                if ((int)pos < firstStr.second)
                    firstStr = make_pair(val, static_cast<int>(pos));
            }
            if ((pos = line.rfind(cand)) != string::npos)
            {
                if ((int)pos > lastStr.second)
                    lastStr = make_pair(val, static_cast<int>(pos));
            }
        }
        // find first and last digit
        if (auto it = find_if(begin(line), end(line), FIND_DIGIT);
            it != end(line))
        {
            firstDigit.first  = *it - '0';
            firstDigit.second = it - begin(line);
        }
        if (auto it = find_if(line.rbegin(), line.rend(), FIND_DIGIT);
            it != line.rend())
        {
            lastDigit.first  = *it - '0';
            lastDigit.second = line.length() - (it - rbegin(line)) - 1;
        }
#if 0
        cout << "[DEBUG] first str = " << firstStr.first << " at "
             << firstStr.second << ", last str = " << lastStr.first << " at "
             << lastStr.second << '\n';
        cout << "[DEBUG] first digit = " << firstDigit.first << " at "
             << firstDigit.second << ", last digit = " << lastDigit.first
             << " at " << lastDigit.second << '\n';
#endif
        // compare pos of first digit and first str
        first = firstDigit.second <= firstStr.second ? firstDigit.first
                                                     : firstStr.first;
        // compare pos of last digit and last str
        last = lastDigit.second > lastStr.second ? lastDigit.first
                                                 : lastStr.first;
        ans += first * 10 + last;
    }
    return ans;
}

TEST(Aoc2023Test_day1, Problem1)
{
    string testStr = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n";
    EXPECT_EQ(142, solve_1(testStr));
}

TEST(Aoc2023Test_day1, Problem2)
{
    string testStr = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4ni"
                     "neeightseven2\nzoneight234\n7pqrstsixteen\n";
    EXPECT_EQ(281, solve_2(testStr));
}

int day1(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day1.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
#include "temp.hh"

static uint64_t solve_1(const string &input)
{
    return 0;
}

static uint64_t solve_2(const string &input)
{
    return 0;
}

TEST(Aoc2023Test_dayXX, Problem1)
{
    string testStr = "test";
    EXPECT_EQ(0, solve_1(testStr));
}

TEST(Aoc2023Test_dayXX, Problem2)
{
    string testStr = "test";
    EXPECT_EQ(0, solve_2(testStr));
}

int dayXX(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_dayXX.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
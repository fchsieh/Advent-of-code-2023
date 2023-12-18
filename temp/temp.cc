#include "temp.hh"
#include <gtest/gtest.h>
using namespace std;

int64_t solve_1(const string &input)
{
    return 0;
}

int64_t solve_2(const string &input)
{
    return 0;
}

TEST(Aoc2023Test, Problem1)
{
    string testStr = "test";
    EXPECT_EQ(0, solve_1(testStr));
}

TEST(Aoc2023Test, Problem2)
{
    string testStr = "test";
    EXPECT_EQ(0, solve_2(testStr));
}

// ========================================================================
// ===================== Utils and helper functions  ======================
// ========================================================================
string readFile(const string &file)
{
    ifstream inputFile;
    inputFile.open(file);
    if (inputFile.is_open())
    {
        stringstream buffer;
        string       res((std::istreambuf_iterator<char>(inputFile)),
                         std::istreambuf_iterator<char>());
        return res;
    }
    return "";
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "test") == 0)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    // Start solving the actual problem, read the input
    string input = readFile("../../input/temp.txt");
    if (input.empty())
    {
        cerr << "ERROR: Input is empty! Check the input file again.\n";
        return ERROR;
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
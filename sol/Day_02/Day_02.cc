#include "Day_02.hh"
#include "../../lib/helper.hh"
#include <gtest/gtest.h>
using namespace std;

#define VALID_BAG(_BAG, _RED, _BLUE, _GREEN)                                   \
    (_BAG[RED] <= _RED && _BAG[BLUE] <= _BLUE && _BAG[GREEN] <= _GREEN)        \
        ? TRUE                                                                 \
        : FALSE

unordered_map<string, int> COLORMAP = {
    {  "red",   RED},
    { "blue",  BLUE},
    {"green", GREEN}
};

vector<vector<int>> p1_parser(const string &input)
{
    // {ID, bag} each stores MAX appearance of colors
    stringstream        ss(input);
    vector<vector<int>> res;
    vector<int>         currGame = {0, 0, 0};
    string              line;
    string              tok;
    int                 count = 0;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            if (tok[tok.length() - 1] == ':') // is game id, reset game
            {
                currGame[RED] = currGame[BLUE] = currGame[GREEN] = 0;
                continue;
            }

            if (stringIsNumber(tok))
                count = stoi(tok);
            else // is a color
            {
                if (tok[tok.length() - 1] == ',' ||
                    tok[tok.length() - 1] == ';')
                    tok.pop_back();

                int color = COLORMAP[tok];
#if 0
                printf("[DEBUG] Tok: %s, Color: %d, currGame orig: %d, "
                       "currGame now: %d\n",
                       tok.c_str(), color, currGame[color],
                       max(currGame[color], count));
#endif
                currGame[color] = max(currGame[color], count);
            }
        }
        res.push_back(currGame);
    }

    return res;
}

int solve_1(const string &input)
{
    vector<vector<int>> parsedInput = p1_parser(input);
    int                 ans         = 0;

    for (size_t i = 0; i < parsedInput.size(); i++)
    {
        if (VALID_BAG(parsedInput[i], 12, 14, 13))
            ans += i + 1;
    }
    return ans;
}

int solve_2(const string &input)
{
    vector<vector<int>> parsedInput = p1_parser(input);
    int                 ans         = 0;
    int                 power       = 0;

    for (auto &vec : parsedInput)
    {
        power = vec[0] * vec[1] * vec[2];
        ans += power;
    }

    return ans;
}

TEST(Aoc2023Test, Problem1)
{
    string
        testStr = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 "
                  "green\nGame 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 "
                  "green, 1 blue\nGame 3: 8 green, 6 blue, 20 red; 5 blue, 4 "
                  "red, 13 green; 5 green, 1 red\nGame 4: 1 green, 3 red, 6 "
                  "blue; 3 green, 6 red; 3 green, 15 blue, 14 red\nGame 5: 6 "
                  "red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    EXPECT_EQ(8, solve_1(testStr));
}

TEST(Aoc2023Test, Problem2)
{
    string
        testStr = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 "
                  "green\nGame 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 "
                  "green, 1 blue\nGame 3: 8 green, 6 blue, 20 red; 5 blue, 4 "
                  "red, 13 green; 5 green, 1 red\nGame 4: 1 green, 3 red, 6 "
                  "blue; 3 green, 6 red; 3 green, 15 blue, 14 red\nGame 5: 6 "
                  "red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    EXPECT_EQ(2286, solve_2(testStr));
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
    string input = readFile("../../input/Day_02.txt");
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
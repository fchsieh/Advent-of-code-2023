#include "Day_08.hh"

#define MAP_TABLE unordered_map<string, vector<string>>

tuple<MAP_TABLE, vector<char>, vector<string>> getMapTable(const string &input)
{
    stringstream   ss(input);
    string         line, tok;
    MAP_TABLE      map;
    bool           isInstruct = true;
    string         currElem, left, right;
    vector<char>   instructions;
    vector<string> startPos; // for part 2

    while (getline(ss, line))
    {
        if (line.empty())
            continue;
        if (isInstruct)
        {
            for (auto c : line)
                instructions.push_back(c);
            isInstruct = false;
        }
        else // build map
        {
            stringstream ssLine(line);
            while (ssLine >> tok)
            {
                if (tok[0] == '=')
                    continue;
                if (isalnum(tok[0]) && isalnum(tok[tok.size() - 1]))
                    currElem = tok;
                else if (tok[0] == '(')
                    left = tok.substr(1, 3);
                else if (tok[tok.size() - 1] == ')')
                    right = tok.substr(0, 3);
            }
            map[currElem] = {left, right};
            if (currElem[2] == 'A')
                startPos.push_back(currElem);
        }
    }
    return {map, instructions, startPos};
}

static uint64_t solve_1(const string &input)
{
    string   currPos  = "AAA";
    uint64_t steps    = 0;
    int      CUR_INST = 0;
    int      direction;

    auto [MAP, INSTRUCTION, ignore] = getMapTable(input);

    while (currPos != "ZZZ")
    {
        direction = DIR_CHAR_TO_INT(INSTRUCTION[CUR_INST]);
        currPos   = MAP[currPos][direction];
        CUR_INST  = (CUR_INST + 1) % (INSTRUCTION.size());
        steps++;
    }
    return steps;
}

static uint64_t solve_2(const string &input)
{
    string      currPos;
    uint64_t    ans = 1, steps;
    int         CUR_INST, direction;
    vector<int> allSteps;

    auto [MAP, INSTRUCTION, allPos] = getMapTable(input);

    for (auto &startPos : allPos)
    {
        steps    = 0;
        CUR_INST = 0;
        currPos  = startPos;
        while (currPos[2] != 'Z')
        {
            direction = DIR_CHAR_TO_INT(INSTRUCTION[CUR_INST]);
            currPos   = MAP[currPos][direction];
            CUR_INST  = (CUR_INST + 1) % (INSTRUCTION.size());
            steps++;
        }
        allSteps.push_back(steps);
    }

    for (auto &dist : allSteps)
        ans = lcm(ans, dist);

    return ans;
}

TEST(Aoc2023Test_day8, Problem1)
{
    string testStr1 = "RL\n\nAAA = (BBB, CCC)\nBBB = (DDD, EEE)\nCCC = (ZZZ, "
                      "GGG)\nDDD = (DDD, DDD)\nEEE = (EEE, EEE)\nGGG = (GGG, "
                      "GGG)\nZZZ = (ZZZ, ZZZ)\n";
    string testStr2 = "LLR\n\nAAA = (BBB, BBB)\nBBB = (AAA, ZZZ)\nZZZ = (ZZZ, "
                      "ZZZ)\n";
    EXPECT_EQ(2, solve_1(testStr1));
    EXPECT_EQ(6, solve_1(testStr2));
}

TEST(Aoc2023Test_day8, Problem2)
{
    string testStr = "LR\n\n11A = (11B, XXX)\n11B = (XXX, 11Z)\n11Z = (11B, "
                     "XXX)\n22A = (22B, XXX)\n22B = (22C, 22C)\n22C = (22Z, "
                     "22Z)\n22Z = (22B, 22B)\nXXX = (XXX, XXX)\n";
    EXPECT_EQ(6, solve_2(testStr));
}

int day8(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day8.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
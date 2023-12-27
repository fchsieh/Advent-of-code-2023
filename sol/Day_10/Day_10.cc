#include "Day_10.hh"

unordered_map<char, function<void(vector<int> &)>> MOVE = {
    {'|',   PIPE_VERTICAL},
    {'-', PIPE_HORIZONTAL},
    {'L', PIPE_NORTH_EAST},
    {'J', PIPE_NORTH_WEST},
    {'7', PIPE_SOUTH_WEST},
    {'F', PIPE_SOUTH_EAST},
};

vector<vector<int>> GET_FOUR_DIRECTIONS(int r, int c, int rMax, int cMax)
{
    vector<vector<int>> tmp;
    if (r - 1 >= 0)
        tmp.push_back({r - 1, c});
    if (r + 1 < rMax)
        tmp.push_back({r + 1, c});
    if (c - 1 >= 0)
        tmp.push_back({r, c - 1});
    if (c + 1 < cMax)
        tmp.push_back({r, c + 1});
    return tmp;
}

void moveAgent(char pipe, vector<int> &agent)
{
    MOVE[pipe](agent);
}

uint64_t solve_1(const string &input)
{
    stringstream         ss(input), ssLine;
    string               line;
    char                 tok;
    vector<char>         currRow;
    vector<vector<char>> MAP; // MAP[row][col] = pipe
    pair<int, int>       START = {0, 0};
    vector<vector<int>>  MOVING_AGENT;
    int                  row = 0, col = 0;
    uint64_t             steps = 0;

    while (getline(ss, line))
    {
        currRow.clear();
        ssLine.clear();
        ssLine.str(line);
        col = 0;

        while (ssLine >> tok)
        {
            if (tok == 'S')
                START = {row, col};
            currRow.push_back(tok);
            col++;
        }
        MAP.push_back(currRow);
        row++;
    }

    // find two starting points
    for (auto &cand : GET_FOUR_DIRECTIONS(START.first, START.second, MAP.size(),
                                          MAP[0].size()))
    {
        if (MAP[cand[0]][cand[1]] == '|')
        {
            // S       |
            // |   or  S
            if (START.first - 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], SOUTH});
            else if (START.first + 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], NORTH});
        }
        if (MOVING_AGENT.size() == 2)
            break;
        if (MAP[cand[0]][cand[1]] == '-')
        {
            // S -  or - S
            if (START.second - 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], EAST});
            else if (START.second + 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], WEST});
        }
        if (MOVING_AGENT.size() == 2)
            break;
        if (MAP[cand[0]][cand[1]] == 'L')
        {
            // S
            // L   or   L S
            if (START.first + 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], NORTH});
            else if (START.second - 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], EAST});
        }
        if (MOVING_AGENT.size() == 2)
            break;
        if (MAP[cand[0]][cand[1]] == 'J')
        {
            // S
            // J   or   S J
            if (START.first + 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], NORTH});
            else if (START.second + 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], WEST});
        }
        if (MOVING_AGENT.size() == 2)
            break;
        if (MAP[cand[0]][cand[1]] == '7')
        {
            // 7
            // S   or   S 7
            if (START.first - 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], SOUTH});
            else if (START.second + 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], WEST});
        }
        if (MOVING_AGENT.size() == 2)
            break;
        if (MAP[cand[0]][cand[1]] == 'F')
        {
            // F
            // S   or   F S
            if (START.first - 1 == cand[0])
                MOVING_AGENT.push_back({cand[0], cand[1], SOUTH});
            else if (START.second - 1 == cand[1])
                MOVING_AGENT.push_back({cand[0], cand[1], EAST});
        }
        if (MOVING_AGENT.size() == 2)
            break;
    }

    while (MOVING_AGENT[0][0] != MOVING_AGENT[1][0] ||
           MOVING_AGENT[0][1] != MOVING_AGENT[1][1])
    {
        moveAgent(MAP[MOVING_AGENT[0][0]][MOVING_AGENT[0][1]], MOVING_AGENT[0]);
        moveAgent(MAP[MOVING_AGENT[1][0]][MOVING_AGENT[1][1]], MOVING_AGENT[1]);
        steps++;
    }
    return steps + 1;
}

uint64_t solve_2(const string &input)
{
    // find all points on the loop
    // start walk: find starting points that is on RHS of the loop
    // for each starting points, run bfs to count # of points within the loop
    return 0;
}

TEST(Aoc2023Test, Problem1)
{
    map<string, uint64_t> tests = {
        {".....\n.S-7.\n.|.|.\n.L-J.\n.....\n", 4},
        {"..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ...\n", 8}
    };
    for (auto &[test, res] : tests)
        EXPECT_EQ(res, solve_1(test));
}

TEST(Aoc2023Test, Problem2)
{
    map<string, uint64_t> tests = {
        // clang-format off
        {"...........\n.S-------7.\n.|F-----7|.\n.||.....||.\n.||.....||.\n.|L-"
        "7.F-J|.\n.|..|.|..|.\n.L--J.L--J\n...........\n",
        4},
        {".F----7F7F7F7F-7....\n.|F--7||||||||FJ....\n.||.FJ||||||||L7....\n"
        "FJL7L7LJLJ||LJ.L-7..\nL--J.L7...LJS7F-7L7.\n....F-J..F7FJ|L7L7L7\n"
        "....L7.F7||L7|.L7L7|\n.....|FJLJ|FJ|F7|.LJ\n....FJL-7.||.||||...\n"
        "....L---J.LJ.LJLJ...\n",
        8},
        {"FF7FSF7F7F7F7F7F---7\nL|LJ||||||||||||F--J\nFL-7LJLJ||||||LJL-77\n"
        "F--JF--7||LJLJ7F7FJ-\nL---JF-JLJ.||-FJLJJ7\n|F|F-JF---7F7-L7L|7|\n"
        "|FFJF7L7F-JF7|JL---7\n7-L-JL7||F7|L7F-7F7|\nL.L7LFJ|||||FJL7||LJ\n"
        "L7JLJL-JLJLJL--JLJ.L\n",
        10}
    };
    // clang-format on
    for (auto &[test, res] : tests)
        EXPECT_EQ(res, solve_2(test));
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
    string input = readFile("../../input/Day_10.txt");
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
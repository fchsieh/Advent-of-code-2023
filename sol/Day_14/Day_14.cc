#include "Day_14.hh"

static void moveNorth(vector<string> &map)
{
    for (int r = 1; r < (int)map.size(); r++)
    {
        for (int c = 0; c < (int)map[0].size(); c++)
        {
            if (map[r][c] == 'O')
            {
                int newR = r;
                while (newR > 0 && map[newR - 1][c] == '.')
                    newR--;
                map[r][c]    = '.';
                map[newR][c] = 'O';
            }
        }
    }
}

static void moveSouth(vector<string> &map)
{
    for (int r = (int)map.size() - 1; r > -1; r--)
    {
        for (int c = 0; c < (int)map[0].size(); c++)
        {
            if (map[r][c] == 'O')
            {
                int newR = r;
                while (newR < (int)map.size() - 1 && map[newR + 1][c] == '.')
                    newR++;
                map[r][c]    = '.';
                map[newR][c] = 'O';
            }
        }
    }
}

static void moveEast(vector<string> &map)
{
    for (int r = 0; r < (int)map.size(); r++)
    {
        for (int c = (int)map[0].size() - 1; c > -1; c--)
        {
            if (map[r][c] == 'O')
            {
                int newC = c;
                while (c < (int)map[0].size() - 1 && map[r][newC + 1] == '.')
                {
                    newC++;
                }
                map[r][c]    = '.';
                map[r][newC] = 'O';
            }
        }
    }
}

static void moveWest(vector<string> &map)
{
    for (int r = 0; r < (int)map.size(); r++)
    {
        for (int c = 0; c < (int)map[0].size(); c++)
        {
            if (map[r][c] == 'O')
            {
                int newC = c;
                while (c > 0 && map[r][newC - 1] == '.')
                {
                    newC--;
                }
                map[r][c]    = '.';
                map[r][newC] = 'O';
            }
        }
    }
}

static uint64_t load(vector<string> &map)
{
    uint64_t ans  = 0;
    uint64_t rows = map.size();

    for (size_t r = 0; r < map.size(); r++)
    {
        for (size_t c = 0; c < map[0].size(); c++)
        {
            if (map[r][c] == 'O')
                ans += rows - r;
        }
    }
    return ans;
}

static uint64_t solve_1(const string &input)
{
    stringstream   ss(input);
    string         line;
    vector<string> map;

    while (getline(ss, line))
        map.push_back(line);

    moveNorth(map);
    return load(map);
}

static uint64_t solve_2(const string &input)
{
    struct vectorStringHash
    {
        // hash vector of strings into a single string
        size_t operator()(const vector<string> &v) const
        {
            stringstream ss;
            for (auto &s : v)
                ss << s;
            return hash<string>{}(ss.str());
        }
    };

    stringstream                                         ss(input);
    string                                               line;
    vector<string>                                       map;
    unordered_map<vector<string>, int, vectorStringHash> cache;
    constexpr uint64_t iterations = 1000000000;
    uint64_t           cyclesDone = 0;

    while (getline(ss, line))
        map.push_back(line);

    while (cyclesDone < iterations)
    {
        cyclesDone++;
        moveNorth(map);
        moveWest(map);
        moveSouth(map);
        moveEast(map);
        if (cache.count(map) == 0)
            cache[map] = cyclesDone;
        else
        {
            // found a cycle, try to move as far as possible
            uint64_t cycleLength = cyclesDone - cache[map];
            while (cyclesDone + cycleLength < iterations)
                cyclesDone += cycleLength;
        }
    }

    return load(map);
}

static string
    testStr = "O....#....\nO.OO#....#\n.....##...\nOO.#O....O\n.O.....O#"
              ".\nO.#..O.#.#\n..O..#O..O\n.......O..\n#....###..\n#OO..#"
              "....\n";

TEST(Aoc2023Test_day14, Problem1)
{
    EXPECT_EQ(136, solve_1(testStr));
}

TEST(Aoc2023Test_day14, Problem2)
{
    EXPECT_EQ(64, solve_2(testStr));
}

int day14(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day14.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
#include "Day_21.hh"

static uint64_t bfs(vector<string> &map, pair<int, int> &start,
                    uint64_t stepLimit, bool part2 = false)
{
    set<pair<int, int>>              seen;
    queue<tuple<int, int, uint64_t>> q;
    vector<pair<int, int>>           res;
    const uint64_t                   n = map.size();
    const uint64_t                   m = map[0].size();

    const auto IN_MAP = [map](int r, int c) {
        return r >= 0 && c >= 0 && r < (int)map.size() &&
               c < (int)map[0].size();
    };

    const auto NEXT_POS = [](int r, int c) -> vector<vector<int>> {
        return {
            {r + 1,     c},
            {r - 1,     c},
            {    r, c + 1},
            {    r, c - 1}
        };
    };

    q.push({start.first, start.second, stepLimit});
    seen.insert(start);

    while (!q.empty())
    {
        auto [r, c, step] = q.front();
        q.pop();

        if (step % 2 == 0)
            res.push_back({r, c});

        if (step == 0)
            continue;

        // find next possible positions
        for (auto next : NEXT_POS(r, c))
        {
            int mapped_r = next[0]; // map coordinate to original puzzle
            int mapped_c = next[1];

            if (part2)
            {
                // map extended-map coordinate to original map
                while (mapped_r < 0)
                    mapped_r += n;
                while (mapped_c < 0)
                    mapped_c += m;
                mapped_r = (mapped_r + n) % n;
                mapped_c = (mapped_c + m) % m;
            }

            if (seen.contains({next[0], next[1]}))
                continue;

            if (IN_MAP(mapped_r, mapped_c) && map[mapped_r][mapped_c] != '#')
            {
                q.push({next[0], next[1], step - 1});
                seen.insert({next[0], next[1]});
            }
        }
    }
    return res.size();
}

static uint64_t solve_1(const string &input, int stepLimit = 64)
{
    stringstream   ss(input);
    string         line;
    vector<string> map;
    pair<int, int> start;
    size_t         row = 0;

    while (getline(ss, line))
    {
        // find starting position
        for (size_t col = 0; col < line.length(); col++)
        {
            if (line[col] == 'S')
            {
                start = {row, col};
                break;
            }
        }
        map.push_back(line);
        row++;
    }

    return bfs(map, start, stepLimit);
}

static uint64_t solve_2(const string &input)
{
    stringstream   ss(input);
    string         line;
    vector<string> map;
    pair<int, int> start;
    size_t         row = 0;

    while (getline(ss, line))
    {
        // find starting position
        for (size_t col = 0; col < line.length(); col++)
        {
            if (line[col] == 'S')
            {
                start = {row, col};
                break;
            }
        }
        map.push_back(line);
        row++;
    }

    uint64_t steps = 26501365LLU - 65LLU;
    uint64_t a0    = bfs(map, start, 65, true);
    uint64_t a1    = bfs(map, start, 131 + 65, true);
    uint64_t a2    = bfs(map, start, 131 * 2 + 65, true);
    uint64_t b0    = a0;
    uint64_t b1    = a1 - a0;
    uint64_t b2    = a2 - a1;
    uint64_t x     = steps / 131;

    return ((b0 + b1 * x + (x * (x - 1) / 2) * (b2 - b1)));
}

static string
    testStr = "...........\n.....###.#.\n.###.##..#.\n..#.#...#..\n....#"
              ".#....\n.##..S####.\n.##..#...#.\n.......##..\n.##.#.####"
              ".\n.##..##.##.\n...........\n";
TEST(Aoc2023Test_day21, Problem1)
{
    EXPECT_EQ(16, solve_1(testStr, 6));
}

TEST(Aoc2023Test_day21, Problem2)
{
    // EXPECT_EQ(0, solve_2(testStr));
    // no test for part2
}

int day21(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day21.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}

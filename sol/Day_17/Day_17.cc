#include "Day_17.hh"

#define IN_MAP(x, y, m)                                                        \
    ((x) >= 0 && (x) < (int)(m.size()) && (y) >= 0 && (y) < (int)(m[0].size()))

struct State
{
    int      r     = 0;
    int      c     = 0;
    char     dir   = 'x';
    int      steps = 0;
    uint64_t cost  = 0;

    State()
    {
    }

    State(int r, int c, char dir, int steps, uint64_t cost)
        : r(r), c(c), dir(dir), steps(steps), cost(cost)
    {
    }

    bool operator==(const State &rhs) const
    {
        // no need to check cost
        return r == rhs.r && c == rhs.c && dir == rhs.dir && steps == rhs.steps;
    }

    bool isEmpty() const
    {
        return dir == 'x';
    }
};

const vector<char>                  DIRECTIONS = {'>', 'v', '<', '^'};
unordered_map<char, pair<int, int>> MOTION     = {
    {'>',  {0, 1}},
    {'v',  {1, 0}},
    {'<', {0, -1}},
    {'^', {-1, 0}},
};

static State move(const State &cur, vector<vector<int>> &map, string dir)
{
    char nextDir   = cur.dir;
    int  nextSteps = cur.steps + 1;
    if (dir != "Forward")
    {
        char dirIdx = find(DIRECTIONS.begin(), DIRECTIONS.end(), cur.dir) -
                      DIRECTIONS.begin();
        nextDir   = dir == "Left" ? DIRECTIONS[(dirIdx + 3) % 4]
                                  : DIRECTIONS[(dirIdx + 1) % 4];
        nextSteps = 1;
    }

    auto [dr, dc] = MOTION[nextDir];
    int nr = cur.r + dr, nc = cur.c + dc;

    if (!IN_MAP(nr, nc, map))
        return State();

    return State(nr, nc, nextDir, nextSteps, cur.cost + map[nr][nc]);
}

uint64_t dijkstra(vector<vector<int>> &map, int minSteps = 0, int maxSteps = 3)
{
    auto pqCmp = [](const State &a, const State &b) { return a.cost > b.cost; };
    auto setHash = [](const State &a) { return a.r << 16 | a.c << 8 | a.dir; };

    priority_queue<State, vector<State>, decltype(pqCmp)> pq(pqCmp);
    unordered_set<State, decltype(setHash)>               seen;

    pq.push(State(0, 0, 'v', 0, 0));
    pq.push(State(0, 0, '>', 0, 0));

    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();

        if (cur.r == (int)map.size() - 1 && cur.c == (int)map[0].size() - 1 &&
            cur.steps >= minSteps)
            return cur.cost;

        if (seen.contains(cur))
            continue;

        seen.insert(cur);
        // counter-clockwise
        if (State left = move(cur, map, "Left");
            !left.isEmpty() && cur.steps >= minSteps)
            pq.push(left);
        // clockwise
        if (State right = move(cur, map, "right");
            !right.isEmpty() && cur.steps >= minSteps)
            pq.push(right);
        // move forward
        if (State forward = move(cur, map, "Forward");
            !forward.isEmpty() && cur.steps < maxSteps)
            pq.push(forward);
    }
    cerr << "Failed to find solution!!\n";
    return -1;
}

static uint64_t solve_1(const string &input)
{
    stringstream        ss(input);
    string              line;
    vector<vector<int>> map;

    while (getline(ss, line))
    {
        vector<int> tmp;
        for (char c : line)
            tmp.push_back(c - '0');
        map.push_back(tmp);
    }

    return dijkstra(map);
}

static uint64_t solve_2(const string &input)
{
    stringstream        ss(input);
    string              line;
    vector<vector<int>> map;

    while (getline(ss, line))
    {
        vector<int> tmp;
        for (char c : line)
            tmp.push_back(c - '0');
        map.push_back(tmp);
    }

    return dijkstra(map, 4, 10);
}

TEST(Aoc2023Test_day17, Problem1)
{
    string testStr = "2413432311323\n3215453535623\n3255245654254\n344658584545"
                     "2\n4546657867536\n1438598798454\n4457876987766\n363787797"
                     "9653\n4654967986887\n4564679986453\n1224686865563\n254654"
                     "8887735\n4322674655533\n";
    EXPECT_EQ(102, solve_1(testStr));
    testStr = "11199\n12199\n99199\n99131\n99111\n";
    EXPECT_EQ(9, solve_1(testStr));
}

TEST(Aoc2023Test_day17, Problem2)
{
    string testStr = "111111111111\n999999999991\n999999999991\n999999999991\n9"
                     "99999999991\n";
    EXPECT_EQ(71, solve_2(testStr));
}

int day17(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day17.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
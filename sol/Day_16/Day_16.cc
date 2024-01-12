#include "Day_16.hh"

class Beam
{
  private:
    int  r, c;
    char dir;

    bool validPos(vector<string> &map)
    {
        return r >= 0 && r < (int)map.size() && c >= 0 &&
               c < (int)map[0].size();
    }

    void move(vector<string> &map, unordered_set<string> &seen,
              unordered_set<string> &usedDirections)
    {
        char cur = map[r][c];
        if (dir == 'R')
        {
            if (cur == '.' || cur == '-')
            {
                // dir remains the same
                c++;
            }
            else if (cur == '|')
            {
                // split into two
                // create a new beam, going down
                Beam newB(r + 1, c, 'D');
                newB.work(map, seen, usedDirections);
                // original one goes up
                dir = 'U';
                r--;
            }
            else if (cur == '\\')
            {
                // goes down
                dir = 'D';
                r++;
            }
            else if (cur == '/')
            {
                // goes up
                dir = 'U';
                r--;
            }
        }
        else if (dir == 'L')
        {
            if (cur == '.' || cur == '-')
            {
                // dir remains the same
                c--;
            }
            else if (cur == '|')
            {
                // split into two
                // create a new beam, going down
                Beam newB(r + 1, c, 'D');
                newB.work(map, seen, usedDirections);
                // original one goes up
                dir = 'U';
                r--;
            }
            else if (cur == '\\')
            {
                // goes up
                dir = 'U';
                r--;
            }
            else if (cur == '/')
            {
                // goes down
                dir = 'D';
                r++;
            }
        }
        else if (dir == 'U')
        {
            if (cur == '.' || cur == '|')
            {
                // dir remains the same
                r--;
            }
            else if (cur == '-')
            {
                // split into two
                // create a new beam, going right
                Beam newB(r, c + 1, 'R');
                newB.work(map, seen, usedDirections);
                // original one goes left
                dir = 'L';
                c--;
            }
            else if (cur == '\\')
            {
                // goes left
                dir = 'L';
                c--;
            }
            else if (cur == '/')
            {
                // goes right
                dir = 'R';
                c++;
            }
        }
        else if (dir == 'D')
        {
            if (cur == '.' || cur == '|')
            {
                // dir remains the same
                r++;
            }
            else if (cur == '-')
            {
                // split into two
                // create a new beam, going right
                Beam newB(r, c + 1, 'R');
                newB.work(map, seen, usedDirections);
                // original one goes left
                dir = 'L';
                c--;
            }
            else if (cur == '\\')
            {
                // goes right
                dir = 'R';
                c++;
            }
            else if (cur == '/')
            {
                // goes left
                dir = 'L';
                c--;
            }
        }
    }

  public:
    Beam(int r, int c, char dir) : r(r), c(c), dir(dir)
    {
    }

    void work(vector<string> &map, unordered_set<string> &seen,
              unordered_set<string> &usedDirections)
    {
        while (true)
        {
            string k = to_string(r) + "," + to_string(c) + "," + dir;
            if (!validPos(map) || usedDirections.contains(k))
                break;

            usedDirections.insert(k);
            seen.insert(to_string(r) + "," + to_string(c));
            move(map, seen, usedDirections);
        }
    }
};

static uint64_t cal(int r, int c, char dir, vector<string> &map)
{
    unordered_set<string> seen;
    unordered_set<string> usedDirs;

    // wrapper for problem 2
    Beam b(r, c, dir);
    b.work(map, seen, usedDirs);

    return seen.size();
}

static uint64_t solve_1(const string &input)
{
    stringstream   ss(input);
    string         line;
    vector<string> map;

    while (getline(ss, line))
        map.push_back(line);

    return cal(0, 0, 'R', map);
}

static uint64_t solve_2(const string &input)
{
    stringstream   ss(input);
    string         line;
    vector<string> map;
    uint64_t       ans = 0;

    while (getline(ss, line))
        map.push_back(line);

    // generate all start points
    for (int c = 0; c < (int)map[0].size(); c++)
    {
        // goes down
        ans = max(ans, cal(0, c, 'D', map));
        // goes up
        ans = max(ans, cal((int)map.size() - 1, c, 'U', map));
    }
    for (int r = 0; r < (int)map.size(); r++)
    {
        // goes right
        ans = max(ans, cal(r, 0, 'R', map));
        // goes left
        ans = max(ans, cal(r, (int)map[0].size() - 1, 'L', map));
    }

    return ans;
}

static string testStr = ".|...\\....\n|.-.\\.....\n.....|-...\n........|.\n..."
                        "...."
                        "...\n.........\\\n..../.\\\\..\n.-.-/"
                        "..|..\n.|....-|.\\\n..//.|....\n";

TEST(Aoc2023Test_day16, Problem1)
{
    EXPECT_EQ(46, solve_1(testStr));
}

TEST(Aoc2023Test_day16, Problem2)
{
    EXPECT_EQ(51, solve_2(testStr));
}

int day16(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day16.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
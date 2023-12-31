#include "Day_12.hh"

uint64_t dfs(size_t pos, size_t currentRecord, int streak, const string &puzzle,
             const vector<int> &record, unordered_map<string, uint64_t> &cache)
{
    if (puzzle.empty() || record.empty())
        return 0; // sanity check

    if ((currentRecord == record.size()) ||
        (currentRecord == record.size() - 1 && record[currentRecord] == streak))
    {
        // done consuming all records, check if there are remaining #'s
        // if so, then the puzzle is invalid
        return (pos == puzzle.size() || puzzle.find("#", pos) == string::npos);
    }

    if (pos == puzzle.size()) // out of bounds and records not consumed yet
        return 0;

    vector<string> keyArr = {
        puzzle,
        to_string(*record.begin()),
        to_string(pos),
        to_string(currentRecord),
        to_string(streak),
    };

    string key;
    STRING_ARR_TO_KEY(keyArr, key);

    uint64_t ways = 0;

    if (cache.count(key))
        return cache[key];

    if (streak == record[currentRecord] &&
        (puzzle[pos] == '.' || puzzle[pos] == '?'))
    {
        // end of current record, move to next record
        ways = dfs(pos + 1, currentRecord + 1, 0, puzzle, record, cache);
    }
    else if (streak < record[currentRecord])
    {
        if (streak == 0)
        {
            if (puzzle[pos] == '?')
            {
                // set puzzle[pos] to '#' or move to next one
                ways = dfs(pos + 1, currentRecord, 1, puzzle, record, cache) +
                       dfs(pos + 1, currentRecord, 0, puzzle, record, cache);
            }
            else if (puzzle[pos] == '#')
                // just move to next one, and set streak to 1
                ways = dfs(pos + 1, currentRecord, 1, puzzle, record, cache);
            else if (puzzle[pos] == '.')
                ways = dfs(pos + 1, currentRecord, 0, puzzle, record, cache);
        }
        else if (puzzle[pos] == '#' || puzzle[pos] == '?')
        {
            // has streak, and can continue to use it
            ways = dfs(pos + 1, currentRecord, streak + 1, puzzle, record,
                       cache);
        }
    }

    return cache[key] = ways;
}

static uint64_t solve_1(const string &input)
{
    stringstream                      ss(input);
    string                            line;
    string                            puzzle, record, recTok;
    vector<pair<string, vector<int>>> springs;
    unordered_map<string, uint64_t>   cache;
    uint64_t                          ans = 0;

    while (getline(ss, line))
    {
        vector<int>  tmp;
        stringstream ssLine(line);
        ssLine >> puzzle >> record;

        stringstream ssRecord(record);
        ssRecord.str(record);
        while (getline(ssRecord, recTok, ','))
            tmp.push_back(stoi(recTok));
        springs.push_back({puzzle, tmp});
    }

    for (auto &[puz, rec] : springs)
        ans += dfs(0, 0, 0, puz, rec, cache);

    return ans;
}

string unfoldSprings(string s)
{
    string res = "";
    for (int i = 0; i < 5; i++)
        res += (i == 0 ? "" : "?") + s;

    return res;
}

vector<int> unfoldGroup(vector<int> v)
{
    vector<int> res;
    for (int i = 0; i < 5; i++)
    {
        for (auto x : v)
            res.push_back(x);
    }
    return res;
}

static uint64_t solve_2(const string &input)
{
    stringstream                      ss(input);
    string                            line;
    string                            puzzle, record, recTok;
    vector<pair<string, vector<int>>> springs;
    unordered_map<string, uint64_t>   cache;
    uint64_t                          ans = 0;

    while (getline(ss, line))
    {
        vector<int>  tmp;
        stringstream ssLine(line);
        ssLine >> puzzle >> record;

        stringstream ssRecord(record);
        ssRecord.str(record);
        while (getline(ssRecord, recTok, ','))
            tmp.push_back(stoi(recTok));

        springs.push_back({unfoldSprings(puzzle), unfoldGroup(tmp)});
    }

    for (auto &[puz, rec] : springs)
        ans += dfs(0, 0, 0, puz, rec, cache);

    return ans;
}

static string testStr = "???.### 1,1,3\n.??..??...?##. 1,1,3\n?#?#?#?#?#?#?#? "
                        "1,3,1,6\n????.#...#... 4,1,1\n????.######..#####. "
                        "1,6,5\n?###???????? 3,2,1\n";
TEST(Aoc2023Test_day12, Problem1)
{
    EXPECT_EQ(21, solve_1(testStr));
}

TEST(Aoc2023Test_day12, Problem2)
{
    EXPECT_EQ(525152, solve_2(testStr));
}

int day12(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day12.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
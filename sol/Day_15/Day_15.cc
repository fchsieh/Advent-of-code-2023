#include "Day_15.hh"
#include <sys/types.h>

static int day15Hash(string &s)
{
    // sanity check
    if (s.back() == '\n')
        s.erase(s.length() - 1);

    int res = 0;
    for (char c : s)
    {
        res += int(c);
        res = ((res % 256) * 17) % 256;
    }
    return res;
}

static uint64_t solve_1(const string &input)
{
    stringstream ss(input);
    string       line;
    uint64_t     ans = 0;

    while (getline(ss, line, ','))
        ans += day15Hash(line);

    return ans;
}

static vector<string> split(string s, char delim)
{
    stringstream   ss(s);
    vector<string> res;
    string         tok;
    while (getline(ss, tok, delim))
        res.push_back(tok);

    return res;
}

static uint64_t solve_2(const string &input)
{
    uint64_t                   ans = 0;
    stringstream               ss(input);
    string                     line;
    vector<vector<string>>     boxes(256, vector<string>{});
    string                     label;
    int                        box, focalLen;
    unordered_map<string, int> focalLenMap; // {label: focalLen}

    while (getline(ss, line, ','))
    {
        if (line.contains('-'))
        {
            label = line.substr(0, line.length() - 1);
            box   = day15Hash(label);
            // find-and-remove
            if (auto idx = find(boxes[box].begin(), boxes[box].end(), label);
                idx != boxes[box].end())
            {
                boxes[box].erase(idx);
            }
        }
        else if (line.contains('='))
        {
            auto tokens = split(line, '=');
            // sanity check
            assert(tokens.size() == 2);

            label              = tokens[0];
            focalLen           = stoi(tokens[1]);
            focalLenMap[label] = focalLen;

            box = day15Hash(label);
            // find-and-set
            if (auto idx = find(boxes[box].begin(), boxes[box].end(), label);
                idx != boxes[box].end())
            {
                int id         = idx - boxes[box].begin();
                boxes[box][id] = label;
            }
            else
            {
                boxes[box].push_back(label);
            }
        }
    }

    for (int boxIdx = 0; boxIdx < 256; boxIdx++)
    {
        for (int slotIdx = 0; slotIdx < (int)boxes[boxIdx].size(); slotIdx++)
        {
            label = boxes[boxIdx][slotIdx];
            ans += (boxIdx + 1) * (slotIdx + 1) * focalLenMap[label];
        }
    }

    return ans;
}

TEST(Aoc2023Test_day15, Problem1)
{
    string testStr = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n";
    EXPECT_EQ(1320, solve_1(testStr));
}

TEST(Aoc2023Test_day15, Problem2)
{
    string testStr = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7\n";
    EXPECT_EQ(145, solve_2(testStr));
}

int day15(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day15.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}

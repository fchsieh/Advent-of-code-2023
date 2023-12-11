#include "Day_03.hh"
#include "../../lib/helper.hh"
#include <cstdint>
#include <gtest/gtest.h>
using namespace std;

#define NUMBER_MAP vector<vector<Node *>>
#define INSERT_NUM_TO_MAP(_map, _line, _start_c, _end_c, _row)                 \
    int32_t _val = extractNum(_line, _start_c, _end_c);                        \
    insertNumToMap(_map, _val, _row, _start_c, _end_c);                        \
    _start_c = -1;

class Node
{
  public:
    Node(int v) : val(v)
    {
    }
    int32_t                val;
    vector<pair<int, int>> pos;
};

int32_t consumeNumFromMap(NUMBER_MAP &map, Node *node)
{
    if (!node)
    {
        cerr << "Node is not set!!";
        return -1;
    }

    int32_t                val = node->val;
    vector<pair<int, int>> pos = node->pos;
    for (auto &[r, c] : pos)
    {
        map[r][c] = NULL;
    }

    return val;
}

void insertNumToMap(NUMBER_MAP &map, int val, int row, int col, int end)
{
    int len = end - col + 1;
    // init val node
    Node *valNode = new Node(val);
    for (int c = col; c < col + len; c++)
        valNode->pos.push_back({row, c});
    // insert to map
    for (int c = col; c < col + len; c++)
        map[row][c] = valNode;
}

inline int32_t extractNum(const string &s, int start, int end)
{
    if (end < start)
    {
        cerr << "End is < start!!";
        return 1;
    }
    string n = s.substr(start, end - start + 1);
    return stoi(n);
}

int32_t solve_1(const string &input)
{
    int32_t                ans = 0;
    stringstream           ss(input);
    string                 line;
    NUMBER_MAP             map;
    int32_t                row = 0, start_c = -1;
    vector<pair<int, int>> symbols;

    while (ss >> line)
    {
        int32_t colLength = line.length();
        map.push_back(vector<Node *>(colLength, NULL));

        for (size_t c = 0; c < line.length(); c++)
        {
            if (isdigit(line[c]))
            {
                if (start_c == -1)
                    start_c = c;
                if (c == line.length() - 1)
                {
                    // end of current row
                    INSERT_NUM_TO_MAP(map, line, start_c, c, row);
                }
            }
            else
            {
                // if holding number: clear and insert to map
                if (start_c != -1)
                {
                    INSERT_NUM_TO_MAP(map, line, start_c, c - 1, row);
                }
                if (line[c] != '.') // should process later
                    symbols.push_back({row, c});
                start_c = -1;
            }
        }
        row++;
    }

    // start processing
    for (auto &[r, c] : symbols)
    {
        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                if (dr == 0 && dc == 0)
                    continue;

                int newr = r + dr, newc = c + dc;

                if (0 <= newr && newr < (int)map.size() && 0 <= newc &&
                    newc <= (int)map[0].size())
                {
                    if (map[newr][newc])
                    {
                        ans += consumeNumFromMap(map, map[newr][newc]);
                    }
                }
            }
        }
    }

#if FALSE
    for (size_t r = 0; r < map.size(); r++)
    {
        for (size_t c = 0; c < map[r].size(); c++)
        {
            if (map[r][c])
                printf("%03d,", map[r][c]->val);
            else
                cout << "  X,";
        }
        cout << '\n';
    }

    for (auto &[r, c] : symbols)
    {
        printf("(%d, %d), ", r, c);
    }
#endif

    return ans;
}

int64_t solve_2(const string &input)
{
    int64_t                               ans = 0;
    stringstream                          ss(input);
    string                                line;
    NUMBER_MAP                            map;
    int32_t                               row = 0, start_c = -1;
    vector<pair<int, int>>                symbols;
    unordered_map<string, vector<Node *>> GEAR_MAP;

    while (ss >> line)
    {
        int32_t colLength = line.length();
        map.push_back(vector<Node *>(colLength, NULL));

        for (size_t c = 0; c < line.length(); c++)
        {
            if (isdigit(line[c]))
            {
                if (start_c == -1)
                    start_c = c;
                if (c == line.length() - 1)
                {
                    // end of current row
                    INSERT_NUM_TO_MAP(map, line, start_c, c, row);
                }
            }
            else
            {
                // if holding number: clear and insert to map
                if (start_c != -1)
                {
                    INSERT_NUM_TO_MAP(map, line, start_c, c - 1, row);
                }
                if (line[c] == '*') // should process later
                    symbols.push_back({row, c});
                start_c = -1;
            }
        }
        row++;
    }

    // start processing
    for (auto &[r, c] : symbols)
    {
        for (int dr = -1; dr <= 1; dr++)
        {
            for (int dc = -1; dc <= 1; dc++)
            {
                if (dr == 0 && dc == 0)
                    continue;

                int newr = r + dr, newc = c + dc;

                if (0 <= newr && newr < (int)map.size() && 0 <= newc &&
                    newc <= (int)map[0].size())
                {
                    if (map[newr][newc])
                    {
                        GEAR_MAP[COORD_TO_KEY(r, c)].push_back(map[newr][newc]);
                        consumeNumFromMap(map, map[newr][newc]);
                    }
                }
            }
        }
    }

    for (auto &[k, v] : GEAR_MAP)
    {
        if (v.size() == 2) // exactly 2
        {
            int32_t first  = v[0]->val;
            int32_t second = v[1]->val;
            ans += first * second;
        }
    }

    return ans;
}

TEST(Aoc2023Test, Problem1)
{
    string testStr = "467..114..\n...*......\n..35..633.\n......#...\n617*....."
                     ".\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664."
                     "598..";
    EXPECT_EQ(4361, solve_1(testStr));
}

TEST(Aoc2023Test, Problem2)
{
    string testStr = "467..114..\n...*......\n..35..633.\n......#...\n617*....."
                     ".\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664."
                     "598..";
    EXPECT_EQ(467835, solve_2(testStr));
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
    string input = readFile("../../input/Day_03.txt");
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
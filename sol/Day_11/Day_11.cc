#include "Day_11.hh"
#include "../../lib/helper.cc"

struct Coord
{
    int x;
    int y;
};

bool operator==(const Coord &lhs, const Coord &rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

uint dist(Coord A, Coord B)
{
    return abs(A.x - B.x) + abs(A.y - B.y);
}

uint inRange(vector<int> &arr, int lo, int hi)
{
    if (lo > hi)
        swap(lo, hi);
    return ranges::count_if(
        arr, [&lo, &hi](int value) { return lo <= value && value <= hi; });
}

tuple<vector<Coord>, vector<int>, vector<int>> getData(const string &input)
{
    stringstream         ss(input), ssLine;
    string               line;
    char                 tok;
    vector<char>         currRow;
    vector<vector<char>> universe;
    bool                 hasGalaxy = false;
    int                  rowIdx = 0, colIdx = 0;
    // return values
    vector<Coord> galaxies;
    vector<int>   colsToExpand, rowsToExpand;

    while (getline(ss, line))
    {
        // init flags
        ssLine.clear();
        currRow.clear();
        hasGalaxy = false;
        colIdx    = 0;

        ssLine.str(line);
        while (ssLine >> tok)
        {
            currRow.push_back(tok);
            if (tok == '#')
            {
                galaxies.push_back(Coord{.x = rowIdx, .y = colIdx});
                hasGalaxy = true;
            }
            colIdx++;
        }
        if (!hasGalaxy)
            rowsToExpand.push_back(rowIdx);
        universe.push_back(currRow);
        rowIdx++;
    }

    // find colsToExpand
    for (size_t c = 0; c < universe[0].size(); c++)
    {
        hasGalaxy = false;
        for (size_t r = 0; r < universe.size(); r++)
        {
            if (universe[r][c] == '#')
            {
                hasGalaxy = true;
                break;
            }
        }
        if (!hasGalaxy)
            colsToExpand.push_back(c);
    }

    return {galaxies, rowsToExpand, colsToExpand};
}

uint64_t solve_1(const string &input)
{
    auto [galaxies, rowsToExpand, colsToExpand] = getData(input);
    uint64_t ans                                = 0;

    // for each pair, calculate the path and sum it up
    for (int i = 0; i < (int)galaxies.size(); i++)
        for (int j = i + 1; j < (int)galaxies.size(); j++)
            ans += dist(galaxies[i], galaxies[j]) +
                   inRange(rowsToExpand, galaxies[i].x, galaxies[j].x) +
                   inRange(colsToExpand, galaxies[i].y, galaxies[j].y);

    return ans;
}

uint64_t solve_2(const string &input, int expandTo = 1)
{
    auto [galaxies, rowsToExpand, colsToExpand] = getData(input);
    uint64_t ans                                = 0;

    // for each pair, calculate the path and sum it up
    for (int i = 0; i < (int)galaxies.size(); i++)
        for (int j = i + 1; j < (int)galaxies.size(); j++)
            ans += dist(galaxies[i], galaxies[j]) +
                   (inRange(rowsToExpand, galaxies[i].x, galaxies[j].x) +
                    inRange(colsToExpand, galaxies[i].y, galaxies[j].y)) *
                       (expandTo - 1); // 1 -> expandTo

    return ans;
}

string testStr = "...#......\n.......#..\n#.........\n..........\n......#.."
                 ".\n.#........\n.........#\n..........\n.......#..\n#...#."
                 "....\n";
TEST(Aoc2023Test, Problem1)
{
    EXPECT_EQ(374, solve_1(testStr));
}

TEST(Aoc2023Test, Problem2)
{
    EXPECT_EQ(1030, solve_2(testStr, 10));
    EXPECT_EQ(8410, solve_2(testStr, 100));
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
    string input = readFile("../../input/Day_11.txt");
    if (input.empty())
    {
        cerr << "ERROR: Input is empty! Check the input file again.\n";
        return ERROR;
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input, 1000000) << '\n';

    return OK;
}
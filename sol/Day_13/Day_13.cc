#include "Day_13.hh"

uint64_t hamming(const string &s1, const string &s2)
{
    uint64_t ans = 0;
    for (size_t i = 0; i < s1.size(); i++)
        ans += (s1[i] != s2[i]);
    return ans;
}

bool isVerticalReflect(vector<string> &mat, int start_c, int end_c, bool part2,
                       int &diff)
{
    int    mid = (start_c + end_c) / 2;
    string lhs, rhs;
    // check if # of cols is even
    if ((end_c - start_c) % 2 != 1)
        return false;

    for (size_t r = 0; r < mat.size(); r++)
    {
        lhs = mat[r].substr(start_c, mid - start_c + 1);
        rhs = mat[r].substr(mid + 1, end_c - mid);
        reverse(rhs.begin(), rhs.end());
        if (lhs != rhs)
        {
            if (part2 && diff == 0 && hamming(lhs, rhs) == 1)
                diff++;
            else
                return false;
        }
    }
    return true;
}

bool isHorizontalReflect(vector<string> &mat, int start_r, int end_r,
                         bool part2, int &diff)
{
    // check if # of rows is even
    if ((end_r - start_r) % 2 != 1)
        return false;

    for (size_t c = 0; c < mat[0].size(); c++)
    {
        int left = start_r, right = end_r;
        while (left < right)
        {
            if (mat[left++][c] != mat[right--][c])
            {
                if (part2 && diff == 0)
                    diff++;
                else
                    return false;
            }
        }
    }
    return true;
}

static uint64_t calculatePoints(vector<string> &mat, bool part2)
{
    uint64_t ans   = 0;
    bool     found = false;
    int      diff  = 0;

    // test row ([0, 1], [0, 2] ... [0, n])
    for (size_t end_r = mat.size() - 1; end_r > 0; end_r--)
    {
        diff = 0;
        if (isHorizontalReflect(mat, 0, end_r, part2, diff))
        {
            if (!part2 || (part2 && diff == 1))
            {
                ans += (end_r / 2 + 1) * 100;
                found = true;
                break;
            }
        }
    }
    // test row ([1, n], [2, n] ... [n-1, n])
    if (!found)
    {
        for (size_t start_r = 1; start_r < mat.size() - 1; start_r++)
        {
            diff = 0;
            if (isHorizontalReflect(mat, start_r, mat.size() - 1, part2, diff))
            {
                if (!part2 || (part2 && diff == 1))
                {
                    ans += ((mat.size() - 1 + start_r) / 2 + 1) * 100;
                    found = true;
                    break;
                }
            }
        }
    }
    // test col ([0, 1], [0, 2] ... [0, n])
    if (!found)
    {
        for (size_t end_c = mat[0].size() - 1; end_c > 0; end_c--)
        {
            diff = 0;
            if (isVerticalReflect(mat, 0, end_c, part2, diff))
            {
                if (!part2 || (part2 && diff == 1))
                {
                    ans += end_c / 2 + 1;
                    found = true;
                    break;
                }
            }
        }
    }
    // test col ([1, n], [2, n] ... [n-1, n])
    if (!found)
    {
        for (size_t start_c = 1; start_c < mat[0].size() - 1; start_c++)
        {
            diff = 0;
            if (isVerticalReflect(mat, start_c, mat[0].size() - 1, part2, diff))
            {
                if (!part2 || (part2 && diff == 1))
                {
                    ans += (mat[0].size() - 1 + start_c) / 2 + 1;
                    found = true;
                    break;
                }
            }
        }
    }

    return ans;
}

static uint64_t solve_1(const string &input, bool isPart2 = false)
{
    uint64_t       ans = 0;
    stringstream   ss(input);
    vector<string> mat;
    string         line;

    while (getline(ss, line))
    {
        if (line.empty())
        {
            ans += calculatePoints(mat, isPart2);
            mat.clear();
        }
        else
            mat.push_back(line);
    }
    // check last matrix
    ans += calculatePoints(mat, isPart2);

    return ans;
}

static uint64_t solve_2(const string &input)
{
    return solve_1(input, true);
}

static string
    testStr = "#.##..##.\n..#.##.#.\n##......#\n##......#\n..#.##.#.\n.."
              "##..##.\n#.#.##.#.\n\n#...##..#\n#....#..#\n..##..###\n##"
              "###.##.\n#####.##.\n..##..###\n#....#..#\n";
TEST(Aoc2023Test_day13, Problem1)
{
    EXPECT_EQ(405, solve_1(testStr));
}

TEST(Aoc2023Test_day13, Problem2)
{
    EXPECT_EQ(400, solve_2(testStr));
}

int day13(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day13.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
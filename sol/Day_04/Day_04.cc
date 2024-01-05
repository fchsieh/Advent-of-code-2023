#include "Day_04.hh"

using namespace std;

// for problem 2
vector<int> hitCount;

inline int winningNums(const unordered_set<string> &card, const string &cur)
{
    return card.contains(cur);
}

static int64_t solve_1(const string &input)
{
    stringstream          ss(input);
    string                line, tok;
    int64_t               ans    = 0;
    int64_t               score  = 0; // 0 -> 1 -> 2 -> 4 ...
    bool                  isCard = true;
    unordered_set<string> card;

    while (ss >> line)
    {
        stringstream ssLine(line);
        while (ssLine >> tok)
        {
            if (tok[tok.size() - 1] == ':') // New game
            {
                // for problem 2
                hitCount.push_back(0);

                card.clear();
                score  = 0;
                isCard = true;
            }
            else if (tok == "|")
            {
                isCard = false;
            }
            else if (isdigit(tok[tok.size() - 1])) // is number
            {
                if (isCard)
                {
                    card.insert(tok);
                }
                else
                {
                    int hit = winningNums(card, tok);
                    hitCount.back() += hit;
#if FALSE
                    printf("[DEBUG] Tok: %s, win = %d, score = %lu\n",
                           tok.c_str(), hit, score);
#endif
                    ans += hit * (score == 0 ? 1 : score);
                    score = hit ? ((score == 0) ? 1 : score * 2) : score;
                }
            }
        }
    }

    return ans;
}

static int64_t solve_2(const string &)
{
    int64_t     ans    = 0;
    int         idx    = 0;
    int         vecLen = hitCount.size();
    vector<int> cards(vecLen, 1);

    for (int count : hitCount)
    {
        for (int j = 0; j < cards[idx]; j++)
            for (int i = idx + 1; i <= min(vecLen - 1, idx + count); i++)
                cards[i]++;
        idx++;
    }

    for_each(cards.begin(), cards.end(), [&ans](int x) { ans += x; });
    return ans;
}

TEST(Aoc2023Test_day4, Problem1)
{
    string testStr = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\nCard "
                     "2: 13 32 20 16 61 |\n61 30 68 82 17 32 24 19 Card 3 : 1 "
                     "21 53 59 44 |\n69 82 63 72 16 21 14 1 Card 4  : 41 92 "
                     "73 "
                     "84 69 |\n59 84 76 51 58 5 54 83 Card 5  : 87 83 26 28 "
                     "32 "
                     "|\n88 30 70 12 93 22 82 36 Card 6 : 31 18 13 56 72 "
                     "|\n74 "
                     "77 10 23 35 67 36 11 ";
    EXPECT_EQ(13, solve_1(testStr));
}

TEST(Aoc2023Test_day4, Problem2)
{
    string testStr = ""; // not used
    EXPECT_EQ(30, solve_2(testStr));
}

int day4(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day4.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
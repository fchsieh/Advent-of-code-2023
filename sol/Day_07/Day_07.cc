#include "Day_07.hh"

unordered_map<char, int> LABEL_P1 = {
    {'2',  0},
    {'3',  1},
    {'4',  2},
    {'5',  3},
    {'6',  4},
    {'7',  5},
    {'8',  6},
    {'9',  7},
    {'T',  8},
    {'J',  9},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

unordered_map<char, int> LABEL_P2 = {
    {'J', -1},
    {'2',  0},
    {'3',  1},
    {'4',  2},
    {'5',  3},
    {'6',  4},
    {'7',  5},
    {'8',  6},
    {'9',  7},
    {'T',  8},
    {'Q', 10},
    {'K', 11},
    {'A', 12},
};

int getCardType(string &card, int part2)
{
    unordered_map<char, int> count;
    bool                     hasJoker = false;

    for (char c : card)
    {
        count[c]++;
        if (c == 'J')
            hasJoker = true;
    }
    // start parsing the card
    if (count.size() == 1)
        return FIVE_OF_A_KIND;
    if (count.size() == 5)
    {
        if (part2 && hasJoker)
            return ONE_PAIR;
        return HIGH_CARD;
    }
    if (count.size() == 2)
    {
        if (part2 && hasJoker)
            return FIVE_OF_A_KIND; // convert Joker to another card type

        int firstCount = count.begin()->second;
        if (firstCount == 2 || firstCount == 3)
            return FULL_HOUSE; // (2,3)
        return FOUR_OF_A_KIND; // (1,4)
    }
    if (count.size() == 3)
    {
        for (auto it : count)
        {
            if (it.second == 3)
            {
                if (part2 && hasJoker)
                    return FOUR_OF_A_KIND;
                return THREE_OF_A_KIND; // (1,1,3)
            }
        }
        if (part2) // 1,2,2
        {
            if (count['J'] == 1)
                return FULL_HOUSE;
            if (count['J'] == 2)
                return FOUR_OF_A_KIND;
        }

        return TWO_PAIR; // (1,2,2)
    }
    if (part2)
    {
        if (count['J'] == 1 || count['J'] == 2)
            return THREE_OF_A_KIND;
    }
    return ONE_PAIR; // (1,1,1,2)
}

uint64_t getResult(const string &input, unordered_map<char, int> &LABEL,
                   int part2)
{
    stringstream         ss(input);
    string               line, hand, bid;
    vector<vector<CARD>> cards(7);
    uint64_t             ans  = 0;
    int                  rank = 1;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        CARD         currCard;
        currCard.bid   = 0;
        currCard.value = vector<int>(5, 0);
        ssLine >> hand >> bid;
        for (int i = 0; i < 5; i++)
        {
            currCard.value[i] = LABEL[hand[i]];
        }
        currCard.bid = stoi(bid);
        cards[getCardType(hand, part2)].push_back(currCard);
    }

    // sort each card types to assign ranks
    for (auto &v_cards : cards)
    {
        sort(v_cards.begin(), v_cards.end(), [](auto &a, auto &b) {
            for (int i = 0; i < 4; i++)
            {
                if (a.value[i] != b.value[i])
                    return a.value[i] < b.value[i];
            }
            return a.value[4] < b.value[4];
        });
    }

    // get final answer
    for (auto v_cards : cards)
    {
        if (v_cards.empty())
            continue;

        for (auto card : v_cards)
        {
            ans += (card.bid * rank);
            rank++;
        }
    }

    return ans;
}

static uint64_t solve_1(const string &input)
{
    return getResult(input, LABEL_P1, FALSE);
}

static uint64_t solve_2(const string &input)
{
    return getResult(input, LABEL_P2, TRUE);
}

static string
    testStr = "32T3K 765\nT55J5 684\nKK677 28\nKTJJT 220\nQQQJA 483\n";
TEST(Aoc2023Test_day7, Problem1)
{
    EXPECT_EQ(6440, solve_1(testStr));
}

TEST(Aoc2023Test_day7, Problem2)
{
    EXPECT_EQ(5905, solve_2(testStr));
}

int day7(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day7.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}
#include "Day_20.hh"

enum MODULETYPE
{
    FLIPFLOP = 0,
    CONJUNCTION,
    BROADCASTER
};

enum PULSE
{
    LOW = 0, // equivalent to "OFF"
    HIGH     // equivalent to "ON"
};

#define OFF LOW
#define ON  HIGH

class Module
{

  public:
    // Module characteristics
    string     name;
    PULSE      state = LOW;
    MODULETYPE type;
    // from -> module -> sendTo
    vector<string> sendTo;
    set<string>    from;
    // runs when receiving input
    function<void(PULSE, unordered_map<string, any> &)> func;

    Module(string name, MODULETYPE type, vector<string> to)
    {
        this->name   = name;
        this->type   = type;
        this->sendTo = vector<string>(to);

        switch (type)
        {
        case FLIPFLOP:
            func = [this](PULSE input, unordered_map<string, any> &map) {
                if (input == LOW)
                {
                    if (this->state == ON)
                    {
                        // send low pulse
                        for (auto &dest : sendTo)
                            any_cast<Module>(&map[dest])->func(LOW, map);
                    }
                    else
                    {
                        // send high pulse
                        for (auto &dest : sendTo)
                            any_cast<Module>(&map[dest])->func(HIGH, map);
                    }
                    // flip current state
                    this->state = PULSE(!this->state);
                }
            };
            break;
        case CONJUNCTION:
            break;
        case BROADCASTER:
            func = [this](PULSE input, unordered_map<string, any> &map) {
                for (auto &dest : sendTo)
                    any_cast<Module>(&map[dest])->func(input, map);
            };
            break;
        }
    }
};

ostream &operator<<(ostream &out, Module &mod)
{
    string modType = (mod.type == FLIPFLOP
                          ? "Flip-flop"
                          : (mod.type == BROADCASTER ? "Broadcaster"
                                                     : "Conjunction"));
    out << "[" << modType << "], name '" << mod.name << "', send list = ";
    for (size_t i = 0; i < mod.sendTo.size(); i++)
        out << mod.sendTo[i] << ((i == mod.sendTo.size() - 1) ? "" : ", ");
    return out;
}

static uint64_t solve_1(const string &input)
{
    stringstream ss(input);
    string       line, tok;

    unordered_map<string, Module> modules;

    while (getline(ss, line))
    {
        // separate line into name, send list
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        regex  rgx("(.*)->(.*)");
        smatch matches;
        regex_search(line, matches, rgx);
        string         name        = matches[1].str();
        string         sendListStr = matches[2].str();
        stringstream   ssSendList(sendListStr);
        vector<string> sendList;
        while (getline(ssSendList, tok, ','))
            sendList.push_back(tok);

        // start pushing modules into table
        if (line.starts_with("%"))
            Module flipflop(name.substr(1), FLIPFLOP, sendList);
        else if (line.starts_with("&"))
            Module conjunction(name.substr(1), CONJUNCTION, sendList);
        else
            Module broadcast(name, BROADCASTER, sendList);
    }
    return 0;
}

static uint64_t solve_2(const string &input)
{
    return 0;
}

TEST(Aoc2023Test_day20, Problem1)
{
    string testStr = "broadcaster -> a, b, c\n%a -> b\n%b -> c\n%c -> "
                     "inv\n&inv -> a\n";
    EXPECT_EQ(32000000, solve_1(testStr));
    testStr = "broadcaster -> a\n%a -> inv, con\n&inv -> b\n%b -> "
              "con\n&con -> "
              "output\n";
    EXPECT_EQ(11687500, solve_1(testStr));
}

TEST(Aoc2023Test_day20, Problem2)
{
    string testStr = "test";
    EXPECT_EQ(0, solve_2(testStr));
}

int day20(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day20.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}

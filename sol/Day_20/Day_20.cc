#include "Day_20.hh"

// #define DEBUG

class Module
{
  public:
    string             name      = "";
    map<string, PULSE> registers = {}; // for conjunction: <from : recent pulse>
    PULSE              state     = STATE_OFF;
    vector<string>     to        = {};
    MODULETYPE         type      = BROADCASTER;

    Module() = default;

    Module(MODULETYPE t, string n, vector<string> sendList)
    {
        type = t;
        name = n;
        to   = vector<string>(sendList);
    }
};

ostream &operator<<(ostream &out, Module &mod)
{
    string modType = (mod.type == FLIPFLOP
                          ? "Flip-flop"
                          : (mod.type == BROADCASTER ? "Broadcaster"
                                                     : "Conjunction"));
    out << "=============  " << mod.name << "  =============\n";
    out << "Type:      " << modType << '\n';
    out << "State:     " << (mod.state == LOW ? "LOW" : "HIGH") << '\n';
    out << "SendList:  ";
    for (size_t i = 0; i < mod.to.size(); i++)
        out << mod.to[i] << ((i == mod.to.size() - 1) ? "" : ", ");
    out << "\nRegisters: ";
    for (auto [r, val] : mod.registers)
        out << "[" << r << ": " << (val == LOW ? "LO" : "HI") << "] ";
    out << '\n';
    return out;
}

tuple<MODULETYPE, string, vector<string>> parseLine(string line)
{
    const auto parse = [&](regex &reg) {
        return vector<string>(
            sregex_token_iterator(line.begin(), line.end(), reg),
            sregex_token_iterator());
    };

    string         tok, name, sendListStr;
    vector<string> sendList;
    MODULETYPE     type = BROADCASTER;
    size_t         idx  = 1;

    // separate line into name, send list
    regex rgx("[%]|[&]|[\\w]+");
    auto  tokens = parse(rgx);
    // set module type and name
    type = (tokens[0][0] == '%')   ? FLIPFLOP
           : (tokens[0][0] == '&') ? CONJUNCTION
                                   : BROADCASTER;
    name = (type != BROADCASTER) ? tokens[idx++] : "broadcaster";

    // push outgoing modules into send list
    for (; idx < tokens.size(); idx++)
        sendList.push_back(tokens[idx]);

    return {type, name, sendList};
}

unordered_map<string, Module> getModules(string input)
{
    stringstream                  ss(input);
    string                        line;
    unordered_map<string, Module> modules;

    while (getline(ss, line))
    {
        auto [type, from, to] = parseLine(line);
        modules[from]         = Module(type, from, to);
    }

    ss.clear();
    ss.str(input);
    while (getline(ss, line))
    {
        auto [type, from, to] = parseLine(line);
        for (auto sendTo : to)
            modules[sendTo].registers[from] = LOW;
    }

    return modules;
}

class ProcessQueue
{
  public:
    queue<tuple<PULSE, string, string>> q          = {};
    uint64_t                            LOW_COUNT  = 0;
    uint64_t                            HIGH_COUNT = 0;

    void push(tuple<PULSE, string, string> event)
    {
        auto [input, from, to] = event;
        (input == LOW) ? LOW_COUNT++ : HIGH_COUNT++;
        q.push({input, from, to});
    }

    uint64_t res()
    {
#ifdef DEBUG
        cout << "Low = " << LOW_COUNT << ", High = " << HIGH_COUNT << '\n';
#endif
        return LOW_COUNT * HIGH_COUNT;
    }
};

void process(unordered_map<string, Module> &modules, ProcessQueue &PQ,
             string from, PULSE input, string currMod)
{
    const auto flipflop = [&]() {
        if (input == LOW)
        {
            // flip state
            modules[currMod].state = (modules[currMod].state == STATE_OFF)
                                         ? STATE_ON
                                         : STATE_OFF;

            if (modules[currMod].state == STATE_OFF)
            {
                for (auto sendTo : modules[currMod].to)
                    PQ.push({LOW, currMod, sendTo});
            }
            else if (modules[currMod].state == STATE_ON)
            {
                for (auto sendTo : modules[currMod].to)
                    PQ.push({HIGH, currMod, sendTo});
            }
        }
    };

    const auto conjunction = [&]() {
        // update register
        modules[currMod].registers[from] = input;
        // check if all values are HI/LO
        bool all_high = all_of(modules[currMod].registers.begin(),
                               modules[currMod].registers.end(),
                               [](auto &p) { return p.second == HIGH; });

        if (all_high)
        {
            for (auto sendTo : modules[currMod].to)
                PQ.push({LOW, currMod, sendTo});
        }
        else
        {
            for (auto sendTo : modules[currMod].to)
                PQ.push({HIGH, currMod, sendTo});
        }
    };

    switch (modules[currMod].type)
    {
    case BROADCASTER:
        for (auto s : modules[currMod].to)
            PQ.push({input, "broadcaster", s});
        break;
    case FLIPFLOP:
        flipflop();
        break;
    case CONJUNCTION:
        conjunction();
        break;
    }
}

static uint64_t solve_1(const string &input)
{

    auto modules = getModules(input);

#ifdef DEBUG
    for (auto [k, v] : modules)
        cout << v << '\n';
#endif

    ProcessQueue processQueue;
    for (int i = 0; i < 1000; i++)
    {
        processQueue.push({LOW, "button", "broadcaster"});

        // Using a queue to process. We need to finish current jobs before
        // moving to next one
        while (!processQueue.q.empty())
        {
            auto [input, fromModule, toModule] = processQueue.q.front();
#ifdef DEBUG
            cout << fromModule << " -" << (input == LOW ? "low" : "high")
                 << "-> " << toModule << '\n';
#endif
            processQueue.q.pop();
            process(modules, processQueue, fromModule, input, toModule);
        }

#ifdef DEBUG
        cout << '\n';
#endif
    }

    return processQueue.res();
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

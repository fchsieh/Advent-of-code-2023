#include "Day_19.hh"

class Condition
{
  public:
    char     checkChar = '-';
    uint64_t condValue = 0;
    char     operand   = '-';
    string   retVal    = "-";

    function<string(unordered_map<char, uint64_t> &)> func;

    Condition(string retVal) : retVal(retVal)
    {
        func = [=](unordered_map<char, uint64_t> &) -> string {
            return retVal;
        };
    }

    Condition(char toCheck, char op, uint64_t checkVal, string retVal)
        : checkChar(toCheck), condValue(checkVal), operand(op), retVal(retVal)
    {
        func = [=](unordered_map<char, uint64_t> &m) -> string {
            if ((op == '<') ? m[toCheck] < checkVal : m[toCheck] > checkVal)
                return retVal;
            else
                return "false";
        };
    }
};

class Workflow
{
  private:
    // cond: returns "false" if not satisfied, else return "retVal"
    vector<Condition> conditions;

  public:
    string name;
    Workflow() = default;

    Workflow(string input)
    {
        string flow;
        char   cname[32], cflow[256];
        sscanf(input.c_str(), "%[a-z]{%[^}]}", cname, cflow);
        name = string(cname);
        flow = string(cflow);
        parseFlow(flow);
    }

    void parseFlow(string &flow)
    {
        stringstream ss(flow);
        string       rule;

        while (getline(ss, rule, ','))
        {
            char     toCheck, op;
            uint64_t checkVal;
            string   retVal;
            char     checkValStr[32], retValStr[32];

            if (rule.contains(':'))
            {
                sscanf(rule.c_str(), "%c%c%[^:]:%s", &toCheck, &op, checkValStr,
                       retValStr);
                retVal   = string(retValStr);
                checkVal = stoi(checkValStr);
                Condition c(toCheck, op, checkVal, retVal);

                conditions.push_back(c);
            }
            else
            {
                Condition c(rule);
                conditions.push_back(c);
            }
        }
    }

    tuple<uint64_t, char, char, string> getConditionValues(int condIdx)
    {
        return {conditions[condIdx].condValue, conditions[condIdx].checkChar,
                conditions[condIdx].operand, conditions[condIdx].retVal};
    }

    string run(unordered_map<char, uint64_t> &input)
    {
        string res     = "false";
        int    condIdx = 0;
        // return first satisfied condition
        while (res == "false")
            res = conditions[condIdx++].func(input);

        return res;
    }
};

unordered_map<char, uint64_t> parseParts(string s)
{
    s = s.substr(1, s.size() - 2);
    unordered_map<char, uint64_t> res;
    stringstream                  ss(s);
    string                        tok;
    int                           idx   = 0;
    vector<char>                  CHARS = {'x', 'm', 'a', 's'};

    while (getline(ss, tok, ','))
        res[CHARS[idx++]] = stoi(tok.substr(2));

    return res;
}

string getResult(unordered_map<string, Workflow> &rules,
                 unordered_map<char, uint64_t>   &input)
{
    string res = rules["in"].run(input);

    while (res != "A" && res != "R")
        res = rules[res].run(input);
    return res;
}

static uint64_t solve_1(const string &input)
{
    stringstream                          ss(input);
    string                                line;
    vector<unordered_map<char, uint64_t>> parts;
    unordered_map<string, Workflow>       rules;
    bool                                  isParts = false;
    uint64_t                              ans     = 0;

    while (getline(ss, line))
    {
        if (line.empty())
        {
            isParts = true;
            continue;
        }
        if (isParts)
            parts.push_back(parseParts(line));
        else
        {
            Workflow w(line);
            rules[w.name] = w;
        }
    }

    for (auto p : parts)
    {
        if (getResult(rules, p) == "A")
            ans += p['x'] + p['m'] + p['a'] + p['s'];
    }

    return ans;
}

class Range
{
  public:
    unordered_map<char, uint64_t> min;
    unordered_map<char, uint64_t> max;

    Range()
    {
        min['x'] = min['m'] = min['a'] = min['s'] = 1;
        max['x'] = max['m'] = max['a'] = max['s'] = 4000;
    }

    Range(char toSet, bool isMin, uint64_t val)
    {
        if (isMin)
            min[toSet] = val;
        else
            max[toSet] = val;
    }
};

ostream &operator<<(ostream &out, Range &r)
{
    out << "min: [" << r.min['x'] << ',' << r.min['m'] << ',' << r.min['a']
        << ',' << r.min['s'] << "], max: [" << r.max['x'] << ',' << r.max['m']
        << ',' << r.max['a'] << ',' << r.max['s'] << "]";
    return out;
}

// Find path to "A", while updating the range
static void DFS(unordered_map<string, Workflow> &rules, string name,
                int conditionIdx, Range &r, vector<Range> &acceptedRanges)
{
    auto [condVal, condChar, op,
          ret] = rules[name].getConditionValues(conditionIdx);
    if (condChar == '-' || conditionIdx > 3)
    {
        // terminal condition, this is the accepted range
        if (ret == "A")
        {
            acceptedRanges.push_back(r);
        }
        else if (ret != "A" && ret != "R") // has next rule, needs to continue
        {
            DFS(rules, ret, 0, r, acceptedRanges);
        }

        return;
    }
    // split current range into two half
    Range trueCond  = r;
    Range falseCond = r;
    if (op == '>')
    {
        trueCond.min[condChar]  = max(condVal + 1, trueCond.min[condChar]);
        falseCond.max[condChar] = min(condVal, falseCond.max[condChar]);
    }
    else if (op == '<')
    {
        trueCond.max[condChar]  = min(condVal - 1, trueCond.max[condChar]);
        falseCond.min[condChar] = max(condVal, falseCond.min[condChar]);
    }

    // get result of new rule
    if (ret == "A")
    {
        // accepted range found, add to ans
        acceptedRanges.push_back(trueCond);

        DFS(rules, name, conditionIdx + 1, falseCond, acceptedRanges);
    }
    else if (ret == "R")
    {
        // true condition has been rejected, continue on false condition
        DFS(rules, name, conditionIdx + 1, falseCond, acceptedRanges);
    }
    else
    {
        // jumps to new rule
        DFS(rules, ret, 0, trueCond, acceptedRanges);
        DFS(rules, name, conditionIdx + 1, falseCond, acceptedRanges);
    }
}

static uint64_t solve_2(const string &input)
{
    stringstream                    ss(input);
    string                          line;
    unordered_map<string, Workflow> rules;
    uint64_t                        ans = 0;
    vector<Range>                   ansRanges;

    while (getline(ss, line))
    {
        if (line.empty())
            break;

        Workflow w(line);
        rules[w.name] = w;
    }

    Range r;
    DFS(rules, "in", 0, r, ansRanges);
    for (auto &acceptedRange : ansRanges)
    {
        ans += (acceptedRange.max['x'] - acceptedRange.min['x'] + 1) *
               (acceptedRange.max['m'] - acceptedRange.min['m'] + 1) *
               (acceptedRange.max['a'] - acceptedRange.min['a'] + 1) *
               (acceptedRange.max['s'] - acceptedRange.min['s'] + 1);
    }

    return ans;
}

static string
    testStr = "px{a<2006:qkq,m>2090:A,rfg}\npv{a>1716:R,A}\nlnx{m>1548:"
              "A,A}\nrfg{s<537:gd,x>2440:R,A}\nqs{s>3448:A,lnx}\nqkq{x<"
              "1416:A,crn}\ncrn{x>2662:A,R}\nin{s<1351:px,qqz}\nqqz{s>"
              "2770:qs,m<1801:hdj,R}\ngd{a>3333:R,R}\nhdj{m>838:A,pv}"
              "\n\n{x=787,m=2655,a=1222,s=2876}\n{x=1679,m=44,a=2067,s="
              "496}\n{x=2036,m=264,a=79,s=2244}\n{x=2461,m=1339,a=466,"
              "s="
              "291}\n{x=2127,m=1623,a=2188,s=1013}\n";

TEST(Aoc2023Test_day19, Problem1)
{
    EXPECT_EQ(19114, solve_1(testStr));
}

TEST(Aoc2023Test_day19, Problem2)
{
    EXPECT_EQ(167409079868000, solve_2(testStr));
}

int day19(int argc, char **argv, string input, bool runTest)
{
    if (runTest)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        testing::GTEST_FLAG(filter) = "Aoc2023Test_day19.*";
        return RUN_ALL_TESTS();
    }

    cout << "==== Start solving today's problem...====\n";
    cout << "First answer is: " << solve_1(input) << '\n';
    cout << "Second answer is: " << solve_2(input) << '\n';

    return OK;
}

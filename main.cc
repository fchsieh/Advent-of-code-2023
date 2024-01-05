#include "sol.hh"

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

void usage(char *prog)
{
    printf("Usage: %s <day> [-t | -a]\n", prog);
    printf("    day         : run specific day\n");
    printf("    -t          : run test on day\n");
    printf("    -a          : run all tests\n");
}

void parseArg(int argc, char **argv, bool &isTest, bool &runAll, int &day,
              string &input)
{
    vector<string> arguments(argv, argv + argc);
    char          *file = new char[1024];

    for (auto arg : arguments)
    {
        if (arg == "-t")
            isTest = true;
        else if (arg == "-a")
        {
            runAll = true;
            return;
        }
        else if (stringIsNumber(arg))
            day = stoi(arg);
    }

    snprintf(file, 1024, "input/Day_%02d.txt", day);
    input = readFile(file);
}

int main(int argc, char *argv[])
{
    bool   runTest = false, runAll = false;
    int    day     = 1;
    int    res;
    string input;

    if (argc == 1 || argc > 3)
    {
        usage(argv[0]);
        return ERROR;
    }
    else if (argc == 2)
    {
        if (!stringIsNumber(string(argv[1])) && strcmp(argv[1], "-a") != 0)
        {
            usage(argv[0]);
            return ERROR;
        }
    }

    parseArg(argc, argv, runTest, runAll, day, input);

    if (runAll)
    {
        // run gtest
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    if (!dayMap.count(day))
    {
        printf("ERROR: Day %d doesn't exist\n", day);
        return ERROR;
    }

    printf(" ============= %s day %d ============= \n",
           (runTest ? "Testing" : "Solving"), day);
    res = dayMap[day](argc, argv, input, runTest);
    printf("\n =============  End of day %d ============= \n", day);

    return res;
}
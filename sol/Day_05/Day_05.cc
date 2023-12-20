#include "Day_05.hh"
using namespace std;

#define DATA_ENTRY vector<uint64_t>
#define MAP_TABLE  unordered_map<string, vector<DATA_ENTRY>>
ThreadPool POOL(12);

uint64_t lookupHelper(MAP_TABLE &map, string mapStr, uint64_t target)
{
    // do binary search
    DATA_ENTRY         searchEntry = {target, 0, 0};
    vector<DATA_ENTRY> currMap     = map[mapStr];
    uint64_t           src_start, dst_start;

    auto it = upper_bound(
        currMap.begin(), currMap.end(), searchEntry,
        [](const DATA_ENTRY &a, const DATA_ENTRY &b) { return a[0] < b[0]; });

    // check if src is within the range
    int idx = distance(currMap.begin(), prev(it));
    if (idx == -1)
    {
        // smaller than smallest src_start
        return target;
    }
    src_start = currMap[idx][0];
    dst_start = currMap[idx][2];
    if (currMap[idx][0] <= target && target <= currMap[idx][1])
    {
        return (target - src_start) + dst_start;
    }
    // not found
    return target;
}

uint64_t lookup(MAP_TABLE &map, uint64_t seed)
{
    uint64_t soil  = lookupHelper(map, "seed-to-soil", seed);
    uint64_t fert  = lookupHelper(map, "soil-to-fertilizer", soil);
    uint64_t water = lookupHelper(map, "fertilizer-to-water", fert);
    uint64_t light = lookupHelper(map, "water-to-light", water);
    uint64_t temp  = lookupHelper(map, "light-to-temperature", light);
    uint64_t humid = lookupHelper(map, "temperature-to-humidity", temp);
    uint64_t loc   = lookupHelper(map, "humidity-to-location", humid);
    return loc;
}

void insertToMapTable(MAP_TABLE &map, string &currentMap, string &line)
{
    string       strDst, strSrc, strRange;
    uint64_t     dst, src, rng;
    stringstream ss(line);
    ss >> strDst >> strSrc >> strRange;
    dst = stoull(strDst);
    src = stoull(strSrc);
    rng = stoull(strRange);

    // <Src_start, Src_end, Dst_start>
    map[currentMap].push_back(DATA_ENTRY{src, src + rng, dst});
    sort(map[currentMap].begin(), map[currentMap].end(),
         [](auto &a, auto &b) { return a[0] < b[0]; });
}

void p1_seed(vector<uint64_t> &seeds, stringstream &ssLine)
{
    string tok;
    while (ssLine >> tok)
    {
        if (stringIsNumber(tok))
            seeds.push_back(stoull(tok));
    }
}

void p2_seed(vector<uint64_t> &seeds, stringstream &ssLine)
{
    string   tok, strStart, strRange;
    uint64_t start, range;
    ssLine >> tok; // ignore first
    while (ssLine >> strStart >> strRange)
    {
        if (!isdigit(strStart[0]) && !isdigit(strRange[0])) // sanity check
        {
            cerr << "Failed to parse input!!\n";
            return;
        }
        start = stoull(strStart);
        range = stoull(strRange);
        for (uint64_t i = 0; i < range; i++)
            seeds.push_back(start + i);
    }
}

uint64_t findLocation(const string &input,
                      void (*getSeeds)(vector<uint64_t> &, stringstream &))
{
    stringstream     ss(input);
    string           line, currentMap;
    uint64_t         ans = UINT64_MAX;
    vector<uint64_t> seeds;
    MAP_TABLE        table;

    while (getline(ss, line))
    {
        stringstream ssLine(line);
        if (line.starts_with("seeds:"))
        {
            getSeeds(seeds, ssLine);
        }
        // start inserting values to map_table
        if (!isdigit(line[0]))
            currentMap = line.substr(0, line.find(' '));
        else
            insertToMapTable(table, currentMap, line);
    }

    for (auto &seed : seeds)
    {
        auto res = POOL.enqueue(lookup, table, seed);
        ans      = min(ans, res.get());
    }

    return ans;
}

uint64_t solve_1(const string &input)
{
    return findLocation(input, &p1_seed);
}

uint64_t solve_2(const string &input)
{
    return findLocation(input, &p2_seed);
}

const string
    testStr = "seeds: 79 14 55 13\n\nseed-to-soil map:\n50 98 2\n52 50 "
              "48\n\nsoil-to-fertilizer map:\n0 15 37\n37 52 2\n39 0 "
              "15\n\nfertilizer-to-water map:\n49 53 8\n0 11 42\n42 0 "
              "7\n57 7 4\n\nwater-to-light map:\n88 18 7\n18 25 "
              "70\n\nlight-to-temperature map:\n45 77 23\n81 45 19\n68 "
              "64 13\n\ntemperature-to-humidity map:\n0 69 1\n1 0 "
              "69\n\nhumidity-to-location map:\n60 56 37\n56 93 4\n";

TEST(Aoc2023Test, Problem1)
{
    EXPECT_EQ(35, solve_1(testStr));
}

TEST(Aoc2023Test, Problem2)
{
    EXPECT_EQ(46, solve_2(testStr));
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
    string input = readFile("../../input/Day_05.txt");
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

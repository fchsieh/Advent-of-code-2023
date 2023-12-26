#include "helper.hh"

inline bool stringIsNumber(const std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

std::string COORD_TO_KEY(const int r, const int c)
{
    char str[1024];
    snprintf(str, 1024, "(%c, %c)", r, c);
    return std::string(str);
}

inline uint64_t GCD(uint64_t a, uint64_t b)
{
    return b == 0 ? a : GCD(b, a % b);
}

inline uint64_t LCM(uint64_t a, uint64_t b)
{
    return a * b / LCM(a, b);
}

template <typename ELE_TYPE>
inline bool CHECK_ARR_IDENTITY(std::vector<ELE_TYPE> &arr)
{
    return std::ranges::adjacent_find(arr, std::ranges::not_equal_to()) ==
           arr.end();
}
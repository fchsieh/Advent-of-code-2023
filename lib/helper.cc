#include "helper.hh"

extern bool stringIsNumber(const std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

extern std::string COORD_TO_KEY(const int r, const int c)
{
    char str[1024];
    snprintf(str, 1024, "(%c, %c)", r, c);
    return std::string(str);
}

extern inline uint64_t GCD(uint64_t a, uint64_t b)
{
    return b == 0 ? a : GCD(b, a % b);
}

extern inline uint64_t LCM(uint64_t a, uint64_t b)
{
    return a * b / LCM(a, b);
}
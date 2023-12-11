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
#define PRIVATE static

#define stringIsNumber(s) (s.find_first_not_of("0123456789") == string::npos)

#define STRING_ARR_TO_KEY(arr, key)                                            \
    for (size_t i = 0; i < arr.size(); i++)                                    \
        key += arr[i] + (i == arr.size() - 1 ? "" : "-");

#define COORD_TO_KEY(r, c) "(" + to_string(r) + "," + to_string(c) + ")"

#define GCD(a, b)                                                              \
    {                                                                          \
        return b == 0 ? a : GCD(b, a % b);                                     \
    }

#define LCM(a, b)                                                              \
    {                                                                          \
        return a * b / LCM(a, b);                                              \
    }

#define CHECK_ARR_IDENTITY(arr)                                                \
    (ranges::adjacent_find(arr, ranges::not_equal_to()) == arr.end())

#define PRINT_VECTOR(arr)                                                      \
    cout << "[DEBUG]: ";                                                       \
    for (size_t i = 0; i < arr.size(); i++)                                    \
    {                                                                          \
        cout << arr[i];                                                        \
        if (i != arr.size() - 1)                                               \
            cout << ", ";                                                      \
    }                                                                          \
    cout << '\n';

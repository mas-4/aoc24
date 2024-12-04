#include "defs.h"

constexpr unsigned char raw[] = {
#embed "../data/03.txt" suffix(, )
    0};

int evaluate0301(size_t i)
{
    i++;
    if (raw[i] != 'u')
    {
        return 0;
    }
    i++;
    if (raw[i] != 'l')
    {
        return 0;
    }
    i++;
    if (raw[i] != '(')
    {
        return 0;
    }
    i++;
    if (raw[i] < '0' || raw[i] > '9')
    {
        return 0;
    }
    char *p;

    int first = strtol((char *)&raw[i], &p, 10);

    i = p - (char *)&raw;
    if (raw[i] != ',')
    {
        return 0;
    }
    i++;
    if (raw[i] < '0' || raw[i] > '9')
    {
        return 0;
    }
    int second = strtol((char *)&raw[i], &p, 10);
    i = p - (char *)&raw;

    if (raw[i] != ')')
    {
        return 0;
    }
    return first * second;
}

int ch0301()
{
    int64_t score = 0;
    for (size_t i = 0; i < sizeof(raw); i++)
    {
        if (raw[i] == 'm')
        {
            score += evaluate0301(i);
        }
    }
    return score;
}
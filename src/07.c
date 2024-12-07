#include "defs.h"
#include <string.h>
#include <math.h>

constexpr unsigned char raw[] = {
#embed "../data/07.txt" suffix(, )
    // #embed "../data/07-test.txt" suffix(, )
    0};

typedef struct
{
    size_t results[1000];
    size_t values[1000][20];
    size_t count;
} Data07;

void parse07(Data07 *data)
{
    char *p = (char *)*(&raw);
    size_t i = 0;
    while (*p)
    {
        data->results[i] = strtol(p, &p, 10);
        p++;
        size_t j = 0;
        memset(data->values[i], 0, sizeof(size_t) * 20);
        while (*p != '\n' && *p != '\r' && *p != '\0')
        {
            data->values[i][j] = strtol(p, &p, 10);
            j++;
        }
        i++;
    }
    data->count = i;
}

size_t arrlen(size_t *arr)
{
    size_t i = 0;
    while (arr[i])
    {
        i++;
    }
    return i;
}

size_t test07(size_t result, size_t values[20])
{
    size_t ops = arrlen(values) - 1;
    size_t perms = 1 << ops;
    for (size_t i = 0; i < perms; i++)
    {
        size_t calc = values[0];

        for (size_t j = 0; j < ops; j++)
        {
            if (i & (1 << j))
            {
                calc += values[j + 1];
            }
            else
            {
                calc *= values[j + 1];
            }
        }
        if (calc == result)
        {
            return result;
        }
    }
    return 0;
}

size_t ch0701()
{
    Data07 data;
    parse07(&data);
    size_t sum = 0;
    for (size_t i = 0; i < data.count; i++)
    {
        sum += test07(data.results[i], data.values[i]);
    }
    return sum;
}

size_t test0702(size_t result, size_t values[20])
{
    size_t ops = arrlen(values) - 1;
    size_t perms = 1;
    for (size_t i = 0; i < ops; i++)
    {
        perms *= 3; // 3 states
    }

    for (size_t i = 0; i < perms; i++)
    {
        size_t calc = values[0];

        for (size_t j = 0; j < ops; j++)
        {
            switch ((i / (size_t)pow(3, j)) % 3)
            {
            case 0:
                calc += values[j + 1];
                break;
            case 1:
                calc *= values[j + 1];
                break;
            case 2:
                calc = pow(10, (size_t)log10(values[j + 1]) + 1) * calc + values[j + 1];
                break;
            }
        }
        if (calc == result)
        {
            return result;
        }
    }

    return 0;
}

size_t ch0702()
{
    Data07 data;
    parse07(&data);
    size_t sum = 0;
    for (size_t i = 0; i < data.count; i++)
    {
        sum += test0702(data.results[i], data.values[i]);
    }
    return sum;
}
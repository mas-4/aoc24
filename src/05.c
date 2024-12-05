#include "defs.h"

constexpr unsigned char raw[] = {
#embed "../data/05.txt" suffix(, )
// #embed "../data/05-test.txt" suffix(, )
    0};

typedef struct
{
    int32_t first[1300];
    int32_t second[1300];
    size_t n_rules;
    int32_t updates[300][25];
    size_t n_updates;
} Data05;

void parse05(Data05 *data)
{
    data->n_rules = 0;
    data->n_updates = 0;
    for (size_t i = 0; i < 1300; i++)
    {
        data->first[i] = 0;
        data->second[i] = 0;
        if (i < 300)
        {
            for (size_t j = 0; j < 25; j++)
            {
                data->updates[i][j] = 0;
            }
        }
    }
    size_t i = 0;
    while (1)
    {
        char *p;
        data->first[data->n_rules] = strtol((char *)&raw[i], &p, 10);
        data->second[data->n_rules] = strtol(p + 1, &p, 10);
        data->n_rules++;
        i = p - (char *)raw;
        if (raw[i + 1] == '\r' || raw[i + 1] == '\n')
        {
            break;
        }
    }

    i++; // skip the newline

    while (raw[i] != 0)
    {
        // e.g.
        // 11,71,68,89,88,79,21,96,47,55,14,27,15,87,23,42,62,64,54,77,94,59,36
        // 87,89,59,36,96,71,44,19,47,55,11,25,54,64,88,14,42,27,97,24,21,77,15,23,79

        char *p;
        size_t j = 0;
        while (1)
        {
            data->updates[data->n_updates][j] = strtol((char *)&raw[i], &p, 10);
            j++;
            i = p - (char *)raw;
            if (raw[i] == ',')
            {
                i++;
            }
            else
            {
                break;
            }
        }
        data->n_updates++;
    }
}

int get_rule(Data05 *data, int8_t first)
{
    for (size_t i = 0; i < data->n_rules; i++)
    {
        if (data->first[i] == first)
        {
            return i;
        }
    }
    return -1;
}

bool rule_holds(Data05 *data, size_t update, size_t rule)
{
    bool first_seen = false;
    bool second_seen = false;
    int32_t first = data->first[rule];
    int32_t second = data->second[rule];

    for (size_t i = 0; i < 25; i++)
    {
        int32_t num = data->updates[update][i];
        if (num == first && second_seen)
        {
            return false; // if we see the first part after the second part, it breaks the rule
        }
        else if (num == first)
        {
            first_seen = true;
        }
        else if (num == second)
        {
            second_seen = true; // if we see the first part now, it breaks the rule
        }
        else if (num == 0)
        {
            break;
        }
    }
    return true;
}

bool is_valid(Data05 *data, size_t i)
{
    for (size_t j = 0; j < data->n_rules; j++)
    {
        if (!rule_holds(data, i, j))
        {
            return false;
        }
    }
    return true;
}

int8_t get_value(Data05 *data, size_t i)
{
    size_t end = 0;
    while (data->updates[i][end] != 0)
    {
        end++;
    }
    return data->updates[i][(size_t)(end / 2)]; // odd numbers halved are floored
}

int ch0501()
{
    Data05 data;
    parse05(&data);
    size_t sum = 0;
    for (size_t i = 0; i < data.n_updates; i++)
    {
        if (is_valid(&data, i))
        {
            sum += get_value(&data, i);
        }
    }

    return sum;
}
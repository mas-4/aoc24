#include "defs.h"
#include <string.h>
#include <math.h>

constexpr unsigned char raw[] = {
#embed "../data/08.txt" suffix(, )
    // #embed "../data/08-test.txt" suffix(, )
    // #embed "../data/08-test2.txt" suffix(, )
    // #embed "../data/08-test4.txt" suffix(, )
    // #embed "../data/08-test5.txt" suffix(, )
    0};

#define SZ 50
// #define SZ 12
// #define SZ 10

typedef struct
{
    size_t x;
    size_t y;
    char freq;
} Antenna;

typedef struct
{
    size_t count;
    Antenna antennas[2000];
} Data08;

void parse(Data08 *data)
{
    data->count = 0;
    for (size_t i = 0; i < SZ; i++)
    {
        for (size_t j = 0; j < SZ; j++)
        {
            if (raw[i * (SZ + 1) + j] != '.')
            {
                data->antennas[data->count].x = j;
                data->antennas[data->count].y = i;
                data->antennas[data->count].freq = raw[i * (SZ + 1) + j];
                data->count++;
            }
        }
    }
}

bool in_bounds(size_t x, size_t y)
{
    return x >= 0 && x < SZ && y >= 0 && y < SZ;
}

void print_node(Antenna a)
{
    printf("Antinode: %c at (%zu, %zu)\n", a.freq, a.x, a.y);
    for (size_t i = 0; i < SZ; i++)
    {
        for (size_t j = 0; j < SZ; j++)
        {
            if (i == a.y && j == a.x)
            {
                printf("#");
            }
            else
            {
                printf("%c", raw[i * (SZ + 1) + j]);
            }
        }
        printf("\n");
    }
}

int add_unique(Antenna *antinodes, size_t *count, Antenna a)
{
    for (size_t i = 0; i < *count; i++)
    {
        if (antinodes[i].x == a.x && antinodes[i].y == a.y)
        {
            return 0;
        }
    }
    antinodes[*count] = a;
    (*count)++;
    return 1;
}

size_t ch0801()
{
    Data08 data;
    parse(&data);
    Antenna antinodes[2000] = {0};
    size_t antinode_count = 0;

    for (size_t i = 0; i < data.count; i++)
    {
        for (size_t j = i + 1; j < data.count; j++)
        {
            if (data.antennas[i].freq != data.antennas[j].freq)
            {
                continue;
            }
            Antenna a = data.antennas[i];
            Antenna b = data.antennas[j];

            Antenna c = {0};
            c.x = 2 * a.x - b.x;
            c.y = 2 * a.y - b.y;
            if (in_bounds(c.x, c.y))
            {
                add_unique(antinodes, &antinode_count, c);
            }
            Antenna d = {0};
            d.x = 2 * b.x - a.x;
            d.y = 2 * b.y - a.y;
            if (in_bounds(d.x, d.y))
            {
                add_unique(antinodes, &antinode_count, d);
            }
        }
    }
    return antinode_count;
}

void antinode(Antenna *a, Antenna *b, Antenna *c)
{
    c->x = 2 * a->x - b->x;
    c->y = 2 * a->y - b->y;
    c->freq = a->freq;
}

void count_antinodes(Antenna *antinodes, size_t *antinode_count, Antenna a, Antenna b)
{
    Antenna nodes[500] = {0};
    nodes[0] = a;
    nodes[1] = b;

    for (size_t i = 2; i < 500; i++)
    {
        antinode(&nodes[i - 1], &nodes[i - 2], &nodes[i]);
        if (!in_bounds(nodes[i].x, nodes[i].y))
        {
            return;
        }
        add_unique(antinodes, antinode_count, nodes[i]);
    }
}

void printmap08(Antenna *antinodes, size_t antinode_count)
{
    for (size_t i = 0; i < SZ; i++)
    {
        for (size_t j = 0; j < SZ; j++)
        {
            bool found = false;
            for (size_t k = 0; k < antinode_count; k++)
            {
                if (antinodes[k].x == j && antinodes[k].y == i && raw[i * (SZ + 1) + j] == '.')
                {
                    printf("#");
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                printf("%c", raw[i * (SZ + 1) + j]);
            }
        }
        printf("\n");
    }
}

size_t ch0802()
{
    Data08 data;
    parse(&data);
    Antenna antinodes[2000] = {0};
    size_t antinode_count = 0;

    for (size_t i = 0; i < data.count; i++)
    {
        for (size_t j = i + 1; j < data.count; j++)
        {
            if (data.antennas[i].freq != data.antennas[j].freq)
            {
                continue;
            }
            add_unique(antinodes, &antinode_count, data.antennas[i]);
            add_unique(antinodes, &antinode_count, data.antennas[j]);
            count_antinodes(antinodes, &antinode_count, data.antennas[i], data.antennas[j]);
            count_antinodes(antinodes, &antinode_count, data.antennas[j], data.antennas[i]);
        }
    }
    printmap08(antinodes, antinode_count);
    return antinode_count;
}
#include "defs.h"
#include <string.h>

constexpr unsigned char raw[] = {
#embed "../data/06.txt" suffix(, )
    0};

#define SZ 130

enum Direction
{
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
};

typedef struct
{
    char map[SZ][SZ];
    size_t start_x;
    size_t start_y;
    enum Direction start_dir;
} Data06;

enum Direction get_direction(char dir)
{
    switch (dir)
    {
    case '^':
        return DIR_UP;
    case 'v':
        return DIR_DOWN;
    case '<':
        return DIR_LEFT;
    case '>':
        return DIR_RIGHT;
    default:
        return DIR_UP;
    }
}

bool is_obstacle(char map[][SZ], size_t x, size_t y)
{
    if (x < 0 || x >= SZ || y < 0 || y >= SZ)
    {
        return false;
    }
    bool ob = map[y][x] == '#';
    return ob;
}

enum Direction turn(enum Direction dir)
{
    return (dir + 1) % 4;
}

void move(size_t *x, size_t *y, enum Direction dir)
{
    switch (dir)
    {
    case DIR_UP:
        (*y)--;
        break;
    case DIR_DOWN:
        (*y)++;
        break;
    case DIR_LEFT:
        (*x)--;
        break;
    case DIR_RIGHT:
        (*x)++;
        break;
    default:
        break;
    }
}

void parse06(Data06 *data)
{
    size_t p = 0;
    for (size_t i = 0; i < SZ; i++)
    {
        for (size_t j = 0; j < SZ; j++)
        {
            data->map[i][j] = raw[i * 131 + j]; // Skip the newline/carriage return
            if (data->map[i][j] != '#' && data->map[i][j] != '.')
            {
                data->start_x = j;
                data->start_y = i;
                data->start_dir = get_direction(data->map[i][j]);
            }
        }
    }
}

size_t turns = 0;

void navigate(char map[][SZ], size_t *x, size_t *y, enum Direction *dir)
{
    // check foward
    size_t x1 = *x;
    size_t y1 = *y;
    move(&x1, &y1, *dir);
    if (!is_obstacle(map, x1, y1))
    {
        *x = x1;
        *y = y1;
        return;
    }
    turns++;
    // back to original position
    x1 = *x;
    y1 = *y;
    // turn right
    *dir = turn(*dir);
    move(&x1, &y1, *dir);
    if (!is_obstacle(map, x1, y1))
    {
        *x = x1;
        *y = y1;
        return;
    }
    // only valid direction left is back the way we came
    *dir = turn(*dir);
    move(x, y, *dir);
}

int ch0601()
{
    Data06 data;
    parse06(&data);

    size_t x = data.start_x;
    size_t y = data.start_y;
    enum Direction dir = data.start_dir;
    size_t count = 0;
    bool positions[SZ][SZ] = {0};
    while (1)
    {
        if (!positions[y][x])
        {
            positions[y][x] = true;
            count++;
        }
        navigate(data.map, &x, &y, &dir);
        if (x < 0 || x >= SZ || y < 0 || y >= SZ)
        {
            break;
        }
    }
    return count;
}

int test(Data06 *data, size_t x, size_t y, enum Direction dir, size_t x1, size_t y1, enum Direction dir1, bool positions[SZ][SZ][4])
{
    bool pos_track[SZ][SZ][4] = {0};
    memcpy(pos_track, positions, SZ * SZ * 4);

    char map[SZ][SZ] = {0};
    memcpy(map, data->map, SZ * SZ);
    map[y1][x1] = '#';

    while (1)
    {
        pos_track[y][x][dir] = true;
        navigate(data->map, &x, &y, &dir);

        if (pos_track[y][x][dir]) // we're cycling
        {
            return true;
        }
        else if (x < 0 || x >= SZ || y < 0 || y >= SZ)
        {
            return false;
        }
    }

    return -1; // not possible
}

int ch0602()
{
    Data06 data;
    parse06(&data);

    size_t count = 0;
    size_t x = data.start_x;
    size_t y = data.start_y;
    enum Direction dir = data.start_dir;
    bool positions[SZ][SZ][4] = {0};
    while (1)
    {
        positions[y][x][dir] = true;
        size_t x1 = x;
        size_t y1 = y;
        enum Direction dir1 = dir;
        navigate(data.map, &x1, &y1, &dir1);
        if (x < 0 || x >= SZ || y < 0 || y >= SZ)
        {
            break;
        }
        if (positions[y1][x1][0] || positions[y1][x1][1] || positions[y1][x1][2] || positions[y1][x1][3])
        {
            continue;
        }
        if (test(&data, x, y, dir, x1, y1, dir1, positions))
        {
            count++;
        }
    }
    return count;
}
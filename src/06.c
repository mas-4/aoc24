#include "defs.h"

constexpr unsigned char raw[] = {
#embed "../data/06.txt" suffix(, )
    0};

#define SZ 130

enum Direction
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

typedef struct
{
    char map[SZ][SZ];
    bool pos[SZ][SZ];
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

bool is_obstacle(Data06 *data, size_t x, size_t y)
{
    if (x < 0 || x >= SZ || y < 0 || y >= SZ)
    {
        return false;
    }
    bool ob = data->map[y][x] == '#';
    return ob;
}

enum Direction turn_right(enum Direction dir)
{
    switch (dir)
    {
    case DIR_UP:
        return DIR_RIGHT;
    case DIR_DOWN:
        return DIR_LEFT;
    case DIR_LEFT:
        return DIR_UP;
    case DIR_RIGHT:
        return DIR_DOWN;
    default:
        return DIR_UP;
    }
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
            data->pos[i][j] = false;
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

void navigate(Data06 *data, size_t *x, size_t *y, enum Direction *dir)
{
    // check foward
    size_t x1 = *x;
    size_t y1 = *y;
    move(&x1, &y1, *dir);
    if (!is_obstacle(data, x1, y1))
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
    *dir = turn_right(*dir);
    move(&x1, &y1, *dir);
    if (!is_obstacle(data, x1, y1))
    {
        *x = x1;
        *y = y1;
        return;
    }
    // only valid direction left is back the way we came
    *dir = turn_right(*dir);
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
    while (1)
    {
        if (!data.pos[y][x])
        {
            data.pos[y][x] = true;
            count++;
        }
        navigate(&data, &x, &y, &dir);
        if (x < 0 || x >= SZ || y < 0 || y >= SZ)
        {
            break;
        }
    }
    return count;
}
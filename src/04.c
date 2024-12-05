#include "defs.h"
#include <string.h>

constexpr unsigned char raw[] = {
#embed "../data/04.txt" suffix(, )
    0};

void parse04(char data[140][140])
{
    for (size_t i = 0; i < 140; i++)
    {
        for (size_t j = 0; j < 140; j++)
        {
            // 141 skips the \n at the end of each line
            data[i][j] = raw[i * 141 + j];
        }
    }
}

int evaluate0401(size_t i, size_t j, char data[140][140])
{
    size_t c = 0;
    // Check for XMAS up
    if (i > 2 && data[i - 1][j] == 'M' && data[i - 2][j] == 'A' && data[i - 3][j] == 'S')
    {
        c++;
    }
    // Check for XMAS down
    if (i < 137 && data[i + 1][j] == 'M' && data[i + 2][j] == 'A' && data[i + 3][j] == 'S')
    {
        c++;
    }
    // Check for XMAS left
    if (j > 2 && data[i][j - 1] == 'M' && data[i][j - 2] == 'A' && data[i][j - 3] == 'S')
    {
        c++;
    }
    // Check for XMAS right
    if (j < 137 && data[i][j + 1] == 'M' && data[i][j + 2] == 'A' && data[i][j + 3] == 'S')
    {
        c++;
    }
    // Check for XMAS up-left
    if (i > 2 && j > 2 && data[i - 1][j - 1] == 'M' && data[i - 2][j - 2] == 'A' && data[i - 3][j - 3] == 'S')
    {
        c++;
    }
    // Check for XMAS up-right
    if (i > 2 && j < 137 && data[i - 1][j + 1] == 'M' && data[i - 2][j + 2] == 'A' && data[i - 3][j + 3] == 'S')
    {
        c++;
    }
    // Check for XMAS down-left
    if (i < 137 && j > 2 && data[i + 1][j - 1] == 'M' && data[i + 2][j - 2] == 'A' && data[i + 3][j - 3] == 'S')
    {
        c++;
    }
    // Check for XMAS down-right
    if (i < 137 && j < 137 && data[i + 1][j + 1] == 'M' && data[i + 2][j + 2] == 'A' && data[i + 3][j + 3] == 'S')
    {
        c++;
    }

    return c;
}

int ch0401()
{
    char data[140][140];
    parse04(data);
    size_t count = 0;

    for (size_t i = 0; i < 140; i++)
    {
        for (size_t j = 0; j < 140; j++)
        {
            if (data[i][j] == 'X')
            {
                count += evaluate0401(i, j, data);
            }
        }
    }
    return count;
}

int check_top(size_t i, size_t j, char data[140][140])
{
    /*
    M M
     A
    S S
    where i, j is the position of A
    */
    return data[i - 1][j - 1] == 'M' && data[i - 1][j + 1] == 'M' && data[i + 1][j - 1] == 'S' && data[i + 1][j + 1] == 'S';
}

int check_left(size_t i, size_t j, char data[140][140])
{
    /*
    M S
     A
    M S
    where i, j is the position of A
    */
    return data[i - 1][j - 1] == 'M' && data[i + 1][j - 1] == 'M' && data[i - 1][j + 1] == 'S' && data[i + 1][j + 1] == 'S';
}

int check_right(size_t i, size_t j, char data[140][140])
{
    /*
    S M
     A
    S M
    where i, j is the position of A
    */
    return data[i - 1][j + 1] == 'M' && data[i + 1][j + 1] == 'M' && data[i - 1][j - 1] == 'S' && data[i + 1][j - 1] == 'S';
}

int check_bottom(size_t i, size_t j, char data[140][140])
{
    /*
    S S
     A
    M M
    where i, j is the position of A
    */
    return data[i + 1][j - 1] == 'M' && data[i + 1][j + 1] == 'M' && data[i - 1][j - 1] == 'S' && data[i - 1][j + 1] == 'S';
}

int evaluate0402(size_t i, size_t j, char data[140][140])
{
    if (i < 1 || i > 138 || j < 1 || j > 138)
    {
        return 0;
    }
    size_t c = 0;
    c += check_top(i, j, data);
    c += check_left(i, j, data);
    c += check_right(i, j, data);
    c += check_bottom(i, j, data);
    return c;
}

int ch0402()
{
    char data[140][140];
    parse04(data);
    size_t count = 0;

    for (size_t i = 0; i < 140; i++)
    {
        for (size_t j = 0; j < 140; j++)
        {
            if (data[i][j] == 'A')
            {
                count += evaluate0402(i, j, data);
            }
        }
    }
    return count;
}
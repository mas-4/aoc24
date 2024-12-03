#include <stdint.h>
#include <stdlib.h>

#include "defs.h"

constexpr unsigned char raw[] = {
#embed "../data/01.txt"
    // #embed "../data/01.txt"
};

typedef struct
{
    int32_t data1[1000];
    int32_t data2[1000];
    size_t size;
} Data;


void parse(Data *data)
{
    char *p = (char *)raw;
    uint32_t i = 0;
    while (*p && i < 1000)
    {
        data->data1[i] = strtol(p, &p, 10);
        data->data2[i] = strtol(p, &p, 10);
        i++;
    }
    data->size = i;
}

int compare( const void* a, const void* b)
{
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

int ch01()
{
    Data data;
    parse(&data);
    qsort(data.data1, data.size, sizeof(uint32_t), compare);
    qsort(data.data2, data.size, sizeof(uint32_t), compare);
    size_t dist = 0;
    for (size_t i = 0; i < data.size; i++)
    {
        dist += abs(data.data1[i] - data.data2[i]);
    }
    return (int)dist;
}

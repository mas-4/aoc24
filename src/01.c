#include "defs.h"

constexpr unsigned char raw[] = {
#embed "../data/01.txt"
    // #embed "../data/01-test.txt"
};

typedef struct
{
  int32_t data1[1000];
  int32_t data2[1000];
  size_t size;
} Data01;

void parse01(Data01 *data)
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

int compare01(const void *a, const void *b)
{
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b)
    return 0;
  else if (int_a < int_b)
    return -1;
  else
    return 1;
}

int ch0101()
{
  Data01 data;
  parse01(&data);
  qsort(data.data1, data.size, sizeof(uint32_t), compare01);
  qsort(data.data2, data.size, sizeof(uint32_t), compare01);
  size_t dist = 0;
  for (size_t i = 0; i < data.size; i++)
  {
    dist += abs(data.data1[i] - data.data2[i]);
  }
  return (int)dist;
}

int ch0102()
{
  Data01 data;
  parse01(&data);

  size_t score = 0;
  for (size_t i = 0; i < data.size; i++)
  {
    int32_t seen = 0;
    for (size_t j = 0; j < data.size; j++)
    {
      if (data.data2[j] == data.data1[i])
      {
        seen++;
      }
    }
    score += seen * data.data1[i];
  }
  return (int)score;
}

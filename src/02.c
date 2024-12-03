#include "defs.h"

constexpr unsigned char raw[] = {
// #embed "../data/02-test.txt"
#embed "../data/02.txt" \
  suffix(,)
  0
};

typedef struct {
  int32_t data[1000][10];
  size_t size;
} Data02;

void parse02(Data02 *data) {
  char *p = (char *)raw;
  uint32_t i = 0;
  while (*p) {
    for (int j = 0; j < 10; j++) {
      data->data[i][j] = 0;
    }

    for (uint32_t j = 0; j < 10; j++) {
      data->data[i][j] = strtol(p, &p, 10);
      if (*p == '\n' || *p == 13 || *p == '\0') {
        break;
      }
    }
    i++;
  }
  data->size = i;
}

int evaluate(const int32_t *data) {
  int sign = (data[1] - data[0]) > 0 ? 1 : -1;
  for (size_t i = 0; i < 10; i++) {
    if (data[i+1] == 0) {
      break;
    }
    int diff = data[i+1] - data[i];
    if ((diff > 0 ? 1 : -1) != sign) {
      return 0;
    }
    if (abs(diff) < 1 || abs(diff) > 3) {
      return 0;
    }
  }
  return 1;
}

int ch0201() {
  Data02 data;
  parse02(&data);
  uint32_t score = 0;
  for (size_t i = 0; i < data.size; i++) {
    score += evaluate(data.data[i]);
  }
  return (int32_t)score;
}

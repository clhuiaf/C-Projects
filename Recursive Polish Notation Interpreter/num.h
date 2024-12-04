#ifndef __NUM_H__
#define __NUM_H__

constexpr unsigned int MAX_NUM_LEN = 241 * sizeof(int) / 100 + 2;

int to_num(const char s[]);

#endif

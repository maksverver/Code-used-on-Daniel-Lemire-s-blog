#ifndef DIGITCOUNT_H
#define DIGITCOUNT_H

#include <cstdint>

int int_log2(uint64_t x) { return 63 - __builtin_clzll(x | 1); }

int digit_count(uint32_t x) {
   static uint32_t table[] = {9, 99, 999, 9999, 99999,
    999999, 9999999, 99999999, 999999999};
    int y = (9 * int_log2(x)) >> 5;
    y += x > table[y];
    return y + 1;
}

int digit_count(uint64_t x) {
  static uint64_t table[] = {9,
                             99,
                             999,
                             9999,
                             99999,
                             999999,
                             9999999,
                             99999999,
                             999999999,
                             9999999999,
                             99999999999,
                             999999999999,
                             9999999999999,
                             99999999999999,
                             999999999999999ULL,
                             9999999999999999ULL,
                             99999999999999999ULL,
                             999999999999999999ULL,
                             9999999999999999999ULL};
  int y = (19 * int_log2(x) >> 6);
  y += x > table[y];
  return y + 1;
}

int alternative_digit_count(uint32_t x) {
  static uint64_t table[] = {
      4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
      12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
      21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
      25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
      34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
      38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
      42949672960, 42949672960};
  return (x + table[int_log2(x)]) >> 32;
}

int alternative_digit_count(uint64_t x) {
  static uint64_t table[64][2] = {
    { 0x01, 0xfffffffffffffff6ULL },
    { 0x01, 0xfffffffffffffff6ULL },
    { 0x01, 0xfffffffffffffff6ULL },
    { 0x01, 0xfffffffffffffff6ULL },
    { 0x02, 0xffffffffffffff9cULL },
    { 0x02, 0xffffffffffffff9cULL },
    { 0x02, 0xffffffffffffff9cULL },
    { 0x03, 0xfffffffffffffc18ULL },
    { 0x03, 0xfffffffffffffc18ULL },
    { 0x03, 0xfffffffffffffc18ULL },
    { 0x04, 0xffffffffffffd8f0ULL },
    { 0x04, 0xffffffffffffd8f0ULL },
    { 0x04, 0xffffffffffffd8f0ULL },
    { 0x04, 0xffffffffffffd8f0ULL },
    { 0x05, 0xfffffffffffe7960ULL },
    { 0x05, 0xfffffffffffe7960ULL },
    { 0x05, 0xfffffffffffe7960ULL },
    { 0x06, 0xfffffffffff0bdc0ULL },
    { 0x06, 0xfffffffffff0bdc0ULL },
    { 0x06, 0xfffffffffff0bdc0ULL },
    { 0x07, 0xffffffffff676980ULL },
    { 0x07, 0xffffffffff676980ULL },
    { 0x07, 0xffffffffff676980ULL },
    { 0x07, 0xffffffffff676980ULL },
    { 0x08, 0xfffffffffa0a1f00ULL },
    { 0x08, 0xfffffffffa0a1f00ULL },
    { 0x08, 0xfffffffffa0a1f00ULL },
    { 0x09, 0xffffffffc4653600ULL },
    { 0x09, 0xffffffffc4653600ULL },
    { 0x09, 0xffffffffc4653600ULL },
    { 0x0a, 0xfffffffdabf41c00ULL },
    { 0x0a, 0xfffffffdabf41c00ULL },
    { 0x0a, 0xfffffffdabf41c00ULL },
    { 0x0a, 0xfffffffdabf41c00ULL },
    { 0x0b, 0xffffffe8b7891800ULL },
    { 0x0b, 0xffffffe8b7891800ULL },
    { 0x0b, 0xffffffe8b7891800ULL },
    { 0x0c, 0xffffff172b5af000ULL },
    { 0x0c, 0xffffff172b5af000ULL },
    { 0x0c, 0xffffff172b5af000ULL },
    { 0x0d, 0xfffff6e7b18d6000ULL },
    { 0x0d, 0xfffff6e7b18d6000ULL },
    { 0x0d, 0xfffff6e7b18d6000ULL },
    { 0x0d, 0xfffff6e7b18d6000ULL },
    { 0x0e, 0xffffa50cef85c000ULL },
    { 0x0e, 0xffffa50cef85c000ULL },
    { 0x0e, 0xffffa50cef85c000ULL },
    { 0x0f, 0xfffc72815b398000ULL },
    { 0x0f, 0xfffc72815b398000ULL },
    { 0x0f, 0xfffc72815b398000ULL },
    { 0x10, 0xffdc790d903f0000ULL },
    { 0x10, 0xffdc790d903f0000ULL },
    { 0x10, 0xffdc790d903f0000ULL },
    { 0x10, 0xffdc790d903f0000ULL },
    { 0x11, 0xfe9cba87a2760000ULL },
    { 0x11, 0xfe9cba87a2760000ULL },
    { 0x11, 0xfe9cba87a2760000ULL },
    { 0x12, 0xf21f494c589c0000ULL },
    { 0x12, 0xf21f494c589c0000ULL },
    { 0x12, 0xf21f494c589c0000ULL },
    { 0x13, 0x7538dcfb76180000ULL },
    { 0x13, 0x7538dcfb76180000ULL },
    { 0x13, 0x7538dcfb76180000ULL },
    { 0x13, 0x7538dcfb76180000ULL },
};
  int log = int_log2(x);
  uint64_t low = table[log][1];
  uint64_t high = table[log][0];
  return (x + low < x ) + high;
}

// Exactly equal to alternative_digit_count, except instead of an array of
// uint64_t[64][2], we declare uint64_t[64][2]
int split_table_digit_count(uint64_t x) {
  static uint64_t table1[64] = {
    0xfffffffffffffff6ULL,
    0xfffffffffffffff6ULL,
    0xfffffffffffffff6ULL,
    0xfffffffffffffff6ULL,
    0xffffffffffffff9cULL,
    0xffffffffffffff9cULL,
    0xffffffffffffff9cULL,
    0xfffffffffffffc18ULL,
    0xfffffffffffffc18ULL,
    0xfffffffffffffc18ULL,
    0xffffffffffffd8f0ULL,
    0xffffffffffffd8f0ULL,
    0xffffffffffffd8f0ULL,
    0xffffffffffffd8f0ULL,
    0xfffffffffffe7960ULL,
    0xfffffffffffe7960ULL,
    0xfffffffffffe7960ULL,
    0xfffffffffff0bdc0ULL,
    0xfffffffffff0bdc0ULL,
    0xfffffffffff0bdc0ULL,
    0xffffffffff676980ULL,
    0xffffffffff676980ULL,
    0xffffffffff676980ULL,
    0xffffffffff676980ULL,
    0xfffffffffa0a1f00ULL,
    0xfffffffffa0a1f00ULL,
    0xfffffffffa0a1f00ULL,
    0xffffffffc4653600ULL,
    0xffffffffc4653600ULL,
    0xffffffffc4653600ULL,
    0xfffffffdabf41c00ULL,
    0xfffffffdabf41c00ULL,
    0xfffffffdabf41c00ULL,
    0xfffffffdabf41c00ULL,
    0xffffffe8b7891800ULL,
    0xffffffe8b7891800ULL,
    0xffffffe8b7891800ULL,
    0xffffff172b5af000ULL,
    0xffffff172b5af000ULL,
    0xffffff172b5af000ULL,
    0xfffff6e7b18d6000ULL,
    0xfffff6e7b18d6000ULL,
    0xfffff6e7b18d6000ULL,
    0xfffff6e7b18d6000ULL,
    0xffffa50cef85c000ULL,
    0xffffa50cef85c000ULL,
    0xffffa50cef85c000ULL,
    0xfffc72815b398000ULL,
    0xfffc72815b398000ULL,
    0xfffc72815b398000ULL,
    0xffdc790d903f0000ULL,
    0xffdc790d903f0000ULL,
    0xffdc790d903f0000ULL,
    0xffdc790d903f0000ULL,
    0xfe9cba87a2760000ULL,
    0xfe9cba87a2760000ULL,
    0xfe9cba87a2760000ULL,
    0xf21f494c589c0000ULL,
    0xf21f494c589c0000ULL,
    0xf21f494c589c0000ULL,
    0x7538dcfb76180000ULL,
    0x7538dcfb76180000ULL,
    0x7538dcfb76180000ULL,
    0x7538dcfb76180000ULL,
};
static uint64_t table2[64] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x03,
    0x03,
    0x03,
    0x04,
    0x04,
    0x04,
    0x04,
    0x05,
    0x05,
    0x05,
    0x06,
    0x06,
    0x06,
    0x07,
    0x07,
    0x07,
    0x07,
    0x08,
    0x08,
    0x08,
    0x09,
    0x09,
    0x09,
    0x0a,
    0x0a,
    0x0a,
    0x0a,
    0x0b,
    0x0b,
    0x0b,
    0x0c,
    0x0c,
    0x0c,
    0x0d,
    0x0d,
    0x0d,
    0x0d,
    0x0e,
    0x0e,
    0x0e,
    0x0f,
    0x0f,
    0x0f,
    0x10,
    0x10,
    0x10,
    0x10,
    0x11,
    0x11,
    0x11,
    0x12,
    0x12,
    0x12,
    0x13,
    0x13,
    0x13,
    0x13,
  };
  int log = int_log2(x);
  return (x + table1[log] < x ) + table2[log];
}

int fast_digit_count(uint64_t x) {
  // table[i] is 1 less than the smallest power of 10 greater than 2 to the power of i.
  //
  // For example:
  //
  //  2^3 =  8   ->  table[3] =  10 - 1 =  9
  //  2^4 = 16   ->  table[4] = 100 - 1 = 99
  //
  static uint64_t table[64] = {
                        9ull,  //  0
                        9ull,  //  1
                        9ull,  //  2
                        9ull,  //  3
                       99ull,  //  4
                       99ull,  //  5
                       99ull,  //  6
                      999ull,  //  7
                      999ull,  //  8
                      999ull,  //  9
                     9999ull,  // 10
                     9999ull,  // 11
                     9999ull,  // 12
                     9999ull,  // 13
                    99999ull,  // 14
                    99999ull,  // 15
                    99999ull,  // 16
                   999999ull,  // 17
                   999999ull,  // 18
                   999999ull,  // 19
                  9999999ull,  // 20
                  9999999ull,  // 21
                  9999999ull,  // 22
                  9999999ull,  // 23
                 99999999ull,  // 24
                 99999999ull,  // 25
                 99999999ull,  // 26
                999999999ull,  // 27
                999999999ull,  // 28
                999999999ull,  // 29
               9999999999ull,  // 30
               9999999999ull,  // 31
               9999999999ull,  // 32
               9999999999ull,  // 33
              99999999999ull,  // 34
              99999999999ull,  // 35
              99999999999ull,  // 36
             999999999999ull,  // 37
             999999999999ull,  // 38
             999999999999ull,  // 39
            9999999999999ull,  // 40
            9999999999999ull,  // 41
            9999999999999ull,  // 42
            9999999999999ull,  // 43
           99999999999999ull,  // 44
           99999999999999ull,  // 45
           99999999999999ull,  // 46
          999999999999999ull,  // 47
          999999999999999ull,  // 48
          999999999999999ull,  // 49
         9999999999999999ull,  // 50
         9999999999999999ull,  // 51
         9999999999999999ull,  // 52
         9999999999999999ull,  // 53
        99999999999999999ull,  // 54
        99999999999999999ull,  // 55
        99999999999999999ull,  // 56
       999999999999999999ull,  // 57
       999999999999999999ull,  // 58
       999999999999999999ull,  // 59
      9999999999999999999ull,  // 60
      9999999999999999999ull,  // 61
      9999999999999999999ull,  // 62
      9999999999999999999ull,  // 63
  };
  // 77/256 = 0.30078125 is an approximation of log(2)/log(10) = 0.30102999566398114
  unsigned log = int_log2(x);
  return ((77 * log) >> 8) + 1 + (x > table[log]);
}

// 32-bit version of fast_digit_count()
int fast_digit_count_32(uint32_t x) {
  // It's also possible to reuse the table from fast_digit_count_64, since the
  // first 32 entries match, and the fact that elements are 64 instead of 32 bit
  // wide doesn't seem to affect performance.
  static uint32_t table[32] = {
             9ul,  //  0
             9ul,  //  1
             9ul,  //  2
             9ul,  //  3
            99ul,  //  4
            99ul,  //  5
            99ul,  //  6
           999ul,  //  7
           999ul,  //  8
           999ul,  //  9
          9999ul,  // 10
          9999ul,  // 11
          9999ul,  // 12
          9999ul,  // 13
         99999ul,  // 14
         99999ul,  // 15
         99999ul,  // 16
        999999ul,  // 17
        999999ul,  // 18
        999999ul,  // 19
       9999999ul,  // 20
       9999999ul,  // 21
       9999999ul,  // 22
       9999999ul,  // 23
      99999999ul,  // 24
      99999999ul,  // 25
      99999999ul,  // 26
     999999999ul,  // 27
     999999999ul,  // 28
     999999999ul,  // 29
    4294967295ul,  // 30
    4294967295ul,  // 31
  };
  unsigned log = int_log2(x);
  return ((77 * log) >> 8) + 1 + (x > table[log]);
}

#endif

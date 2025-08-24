#pragma once

#define RIBBON_1 16
#define RIBBON_2 17
#define RIBBON_3 18
#define RIBBON_4 19
#define RIBBON_5 20
#define RIBBON_6 21
#define RIBBON_7 15
#define RIBBON_8 14
#define RIBBON_9 13
#define RIBBON_10 12
#define RIBBON_11 11
#define RIBBON_12 10
#define RIBBON_13 8
#define RIBBON_14 9
#define RIBBON_15 6
#define RIBBON_16 7
#define RIBBON_17 4
#define RIBBON_18 5

const int cols[] = {
  RIBBON_17, RIBBON_8, RIBBON_6, RIBBON_15, RIBBON_12, RIBBON_11, RIBBON_9, RIBBON_7, RIBBON_5, RIBBON_4, RIBBON_3, RIBBON_2, RIBBON_1
};
const int COLS = countof(cols);

const int rows[] = {
  RIBBON_10, RIBBON_13, RIBBON_14, RIBBON_16, RIBBON_18
};
const int ROWS = countof(rows);

const int MATRIX_SIZE = COLS * ROWS;

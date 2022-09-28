#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  ERROR = -1,
  NUMBE = 0,
  X = 1, // 0
  PLUS = 2,
  MINUS = 3, // 1
  DIVIDE = 4,
  MULTIPLY = 5, // 2
  POWER = 6,
  MODULATE = 7, // 3
  UNMINUS = 10,
  COS = 11,
  SIN = 12,
  TAN = 13,
  ACOS = 14,
  ASIN = 15,
  ATAN = 16,
  SQRT = 17,
  LN = 18,
  LOG = 19, // 4
  LEFT_BRACKET = 20,
  RIGHT_BRACKET = 21,
  END = 22
} element_type;

typedef struct my_struct {
  double num;
  element_type type;
  struct my_struct *next;
} my_struct;

double number_parser(char **pointer);
my_struct find_lexema(char **pointer);
my_struct *postfix(char *ex);
double polish(my_struct *ex, double x);
int validation(my_struct *ex);
void* s21_to_lower(const char *str);

#endif // S21_SMARTCALC_H

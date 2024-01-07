#ifndef SMARTCALC_MODEL_H
#define SMARTCALC_MODEL_H

#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <cmath>


typedef enum
{
  ERRO = -1,
  NUMB = 0,
  NUM_X = 1,          // 0
  Z_PLUS = 2,
  Z_MINUS = 3,        // 1
  Z_DIVIDE = 4,
  Z_MULTIPLY = 5,     // 2
  Z_POWER = 6,
  Z_MODULATE = 7,     // 3
  Z_UNMINUS = 10,
  Z_COS = 11,
  Z_SIN = 12,
  Z_TAN = 13,
  Z_ACOS = 14,
  Z_ASIN = 15,
  Z_ATAN = 16,
  Z_SQRT = 17,
  Z_LN = 18,
  Z_LOG = 19,          // 4
  Z_LEFT_BRACKET = 20,
  Z_RIGHT_BRACKET = 21,
} element_typee;

class Notation
{
public:
  struct Lexema
  {
    double num;
    element_typee type;
    Lexema() {}
    Lexema(double num_) : num(num_), type(NUMB) {}
    Lexema(element_typee type_) : num(0), type(type_) {}
  };

  std::list<Lexema> *expr;
  bool is_x = false;

  Notation() {
    expr = new std::list<Lexema>;
  }

  ~Notation() {
    delete expr;
  }

  bool inp(char * s);
  int get_postfix(char** expression);
  void print_list();
  double find_number(char ** expr);
  Lexema find_lexema(char **pointer);
  double polish(double x);
  bool validation();
};

#endif  // SMARTCALC_CONTROLLER_H

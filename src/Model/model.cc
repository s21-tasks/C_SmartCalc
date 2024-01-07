#include "model.h"

// Notation::Notation(std::string expression) {

// }

double Notation::polish(double x)
{
  double buff = 0;
  auto iter = expr->begin();
  std::stack<double> st;
  while (iter != expr->end())
  {
    switch (iter->type)
    {
    case 0:
      st.push(iter->num);
      break;
    case 1:
      st.push(x);
      break;
    case Z_PLUS:
      buff = st.top();
      st.pop();
      buff += st.top();
      st.pop();
      st.push(buff);
      break;
    case Z_MINUS:
      buff = st.top();
      st.pop();
      buff = st.top() - buff;
      st.pop();
      st.push(buff);
      break;
    case Z_MULTIPLY:
      buff = st.top();
      st.pop();
      buff *= st.top();
      st.pop();
      st.push(buff);
      break;
    case Z_DIVIDE:
      buff = st.top();
      st.pop();
      buff = st.top() / buff;
      st.pop();
      st.push(buff);
      break;
    case Z_POWER:
      buff = st.top();
      st.pop();
      buff = pow(st.top(), buff);
      st.pop();
      st.push(buff);
      break;
    case Z_MODULATE:
      buff = st.top();
      st.pop();
      buff = fmod(st.top(), buff);
      st.pop();
      st.push(buff);
      break;
    case Z_UNMINUS:
      buff = st.top();
      st.pop();
      buff *= -1;
      st.push(buff);
      break;
    case Z_COS:
      buff = st.top();
      st.pop();
      buff = cos(buff);
      st.push(buff);
      break;
    case Z_SIN:
      buff = st.top();
      st.pop();
      buff = sin(buff);
      st.push(buff);
      break;
    case Z_TAN:
      buff = st.top();
      st.pop();
      buff = tan(buff);
      st.push(buff);
      break;
    case Z_ACOS:
      buff = st.top();
      st.pop();
      buff = acos(buff);
      st.push(buff);
      break;
    case Z_ASIN:
      buff = st.top();
      st.pop();
      buff = asin(buff);
      st.push(buff);
      break;
    case Z_ATAN:
      buff = st.top();
      st.pop();
      buff = atan(buff);
      st.push(buff);
      break;
    case Z_SQRT:
      buff = st.top();
      st.pop();
      buff = sqrt(buff);
      st.push(buff);
      break;
    case Z_LN:
      buff = st.top();
      st.pop();
      buff = log(buff);
      st.push(buff);
      break;
    case Z_LOG:
      buff = st.top();
      st.pop();
      buff = log10(buff);
      st.push(buff);
      break;
    default:
      return -1;
    }
    ++iter;
  }
  return st.top();
}

Notation::Lexema Notation::find_lexema(char **pointer)
{
  char *buff = *pointer;
  if (*buff >= '0' && *buff <= '9')
  {
    double number = find_number(pointer);
    return Lexema(number);
  }
  else if (*buff == '+')
  {
    ++(*pointer);
    return Lexema(Z_PLUS);
  }
  else if (*buff == '-')
  {
    ++(*pointer);
    return Lexema(Z_MINUS);
  }
  else if (*buff == '*')
  {
    ++(*pointer);
    return Lexema(Z_MULTIPLY);
  }
  else if (*buff == '/')
  {
    ++(*pointer);
    return Lexema(Z_DIVIDE);
  }
  else if (*buff == 'x')
  {
    is_x = true;
    ++(*pointer);
    return Lexema(NUM_X);
  }
  else if (*buff == '^')
  {
    ++(*pointer);
    return Lexema(Z_POWER);
  }
  else if (!strncmp(buff, "mod", 3))
  {
    (*pointer) += 3;
    return Lexema(Z_MODULATE);
  }
  else if (!strncmp(buff, "cos", 3))
  {
    (*pointer) += 3;
    return Lexema(Z_COS);
  }
  else if (!strncmp(buff, "sin", 3))
  {
    (*pointer) += 3;
    return Lexema(Z_SIN);
  }
  else if (!strncmp(buff, "tan", 3))
  {
    (*pointer) += 3;
    return Lexema(Z_TAN);
  }
  else if (!strncmp(buff, "acos", 4))
  {
    (*pointer) += 4;
    return Lexema(Z_ACOS);
  }
  else if (!strncmp(buff, "asin", 4))
  {
    (*pointer) += 4;
    return Lexema(Z_ASIN);
  }
  else if (!strncmp(buff, "atan", 4))
  {
    (*pointer) += 4;
    return Lexema(Z_ATAN);
  }
  else if (!strncmp(buff, "sqrt", 4))
  {
    (*pointer) += 4;
    return Lexema(Z_SQRT);
  }
  else if (!strncmp(buff, "ln", 2))
  {
    (*pointer) += 2;
    return Lexema(Z_LN);
  }
  else if (!strncmp(buff, "log", 3))
  {
    (*pointer) += 3;
    return Lexema(Z_LOG);
  }
  else if (*buff == '(')
  {
    ++(*pointer);
    return Lexema(Z_LEFT_BRACKET);
  }
  else if (*buff == ')')
  {
    ++(*pointer);
    return Lexema(Z_RIGHT_BRACKET);
  }
  else
  {
    return Lexema(ERRO);
  }
}

double Notation::find_number(char **expr)
{
  double sol = 0;
  double sol_dop = -1;
  char *q = *expr;
  for (; *q >= 48 && *q <= 57; q++)
  {
    sol *= 10;
    sol += (*q) - 48;
  }
  if (*q == '.')
  {
    q++;
    for (; *q >= 48 && *q <= 57; q++)
    {
      sol += (*q - 48) * pow(10, sol_dop);
      sol_dop--;
    }
    sol_dop /= 10;
  }
  *expr = q;
  return sol;
}

int Notation::get_postfix(char **expression)
{
  expr->clear();
  std::stack<Lexema> st;
  int unmin = 1;
  while (**expression)
  {
    while (**expression == ' ')
      ++(*expression);
    Lexema lex = find_lexema(expression);
    if (lex.type == ERRO)
    {
      return -1;
    }
    if (lex.type == Z_MINUS && unmin)
      lex.type = Z_UNMINUS;
  std::cout << "ok11" << std::endl;
    if (lex.type < 2)
    {
      expr->push_back(lex);
      unmin = 0;
      std::cout << "ok_<2" << std::endl;
    }
    else if (lex.type < 10)
    {
      while (!st.empty() && st.top().type / 2 >= lex.type / 2 && st.top().type != 20)
      {
        expr->push_back(st.top());
        st.pop();
      }
      unmin = 1;
      st.push(lex);
    }
    else if (lex.type == 21)
    {
      while (!st.empty() && st.top().type != 20)
      {
        expr->push_back(st.top());
        st.pop();
      }
      if (st.empty())
        return -1; // check
      st.pop();
      unmin = 0;
    }
    else
    {
      st.push(lex);
      unmin = 1;
    }
    while (**expression == ' ')
      (*expression)++;
  }
  while (!st.empty())
  {
    expr->push_back(st.top());
    st.pop();
  }
  return 0;
}

void Notation::print_list()
{
  auto iter = expr->begin();
  while (iter != expr->end())
  {
    std::cout << "type is " << iter->type << std::endl;
    std::cout << "number is " << iter->num << std::endl
              << std::endl;
    ++iter;
  }
}

bool Notation::validation() {
  int sol = 0;
  auto iter = expr->begin();
  while(iter != expr->end()) {
    if (iter->type <2) {
      sol++;
    } else if (iter->type < 8) {
      sol--;
    } else if (iter->type == 20) {
      return false;
    }
    ++iter;
  }
  if (sol !=1) return false;

  return true;
}

bool Notation::inp(char * s) {
  // char * e = (char *)s.c_str();
  if (get_postfix(&s)) return false;
  std::cout << "ok3" << std::endl;
  if (!validation()) return false;
  return true;
}

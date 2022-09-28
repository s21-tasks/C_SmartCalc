#include "s21_smartcalc.h"

double number_parser(char **pointer) {
  double sol = 0;
  double sol_dop = -1;
  char *q = *pointer;
  for (; *q >= 48 && *q <= 57; q++) {
    sol *= 10;
    sol += (*q) - 48;
  }
  if (*q == '.') {
    q++;
    for (; *q >= 48 && *q <= 57; q++) {
      sol += (*q - 48) * pow(10, sol_dop);
      sol_dop--;
    }
    sol_dop /= 10;
  }
  *pointer = q;
  return sol;
}

my_struct find_lexema(char **pointer) {
  my_struct sol = {0};
  char *buff = *pointer;
  if (*buff >= '0' && *buff <= '9') {
    double number = number_parser(pointer);
    sol.type = 0;
    sol.num = number;
  } else if (*buff == '+') {
    sol.type = 2;
    *pointer = buff + 1;
  } else if (*buff == '-') {
    sol.type = 3;
    *pointer = buff + 1;
  } else if (*buff == '*') {
    sol.type = 4;
    *pointer = buff + 1;
  } else if (*buff == '/') {
    sol.type = 5;
    *pointer = buff + 1;
  } else if (*buff == 'x') {
    sol.type = 1;
    *pointer = buff + 1;
  } else if (*buff == '^') {
    sol.type = 6;
    *pointer = buff + 1;
  } else if (!strncmp(buff, "mod", 3)) {
    sol.type = 7;
    *pointer = buff + 3;
  } else if (!strncmp(buff, "cos", 3)) {
    sol.type = 11;
    *pointer = buff + 3;
  } else if (!strncmp(buff, "sin", 3)) {
    sol.type = 12;
    *pointer = buff + 3;
  } else if (!strncmp(buff, "tan", 3)) {
    sol.type = 13;
    *pointer = buff + 3;
  } else if (!strncmp(buff, "acos", 4)) {
    sol.type = 14;
    *pointer = buff + 4;
  } else if (!strncmp(buff, "asin", 4)) {
    sol.type = 15;
    *pointer = buff + 4;
  } else if (!strncmp(buff, "atan", 4)) {
    sol.type = 16;
    *pointer = buff + 4;
  } else if (!strncmp(buff, "sqrt", 4)) {
    sol.type = 17;
    *pointer = buff + 4;
  } else if (!strncmp(buff, "ln", 2)) {
    sol.type = 18;
    *pointer = buff + 2;
  } else if (!strncmp(buff, "log", 3)) {
    sol.type = 19;
    *pointer = buff + 3;
  } else if (*buff == '(') {
    sol.type = 20;
    *pointer = buff + 1;
  } else if (*buff == ')') {
    sol.type = 21;
    *pointer = buff + 1;
  } else {
    sol.type = -1;
    *pointer = buff + 1;
  }
  return sol;
}

void push(my_struct **head, my_struct new) {
  my_struct *up = (my_struct *)malloc(sizeof(my_struct));
  up->next = *head;
  up->num = new.num;
  up->type = new.type;
  *head = up;
}

my_struct pop(my_struct **head) {
  my_struct *buff = (*head)->next;
  my_struct res = {0};
  res.num = (*head)->num;
  res.type = (*head)->type;
  free(*head);
  *head = buff;
  return res;
}

my_struct *postfix(char *ex) {
  int cou = 0;
  int perem = 1;
  my_struct *sol = (my_struct *)malloc(sizeof(my_struct) * cou);
  my_struct *stack1 = NULL, st = {0};
  while (*ex) {
    while (*ex == ' ')
      ex++;
    st = find_lexema(&ex);
    if (st.type == -1) {
      free(sol);
      return NULL;
    }
    if (st.type == MINUS && perem)
      st.type = UNMINUS;
    if (st.type < 2) {
      cou++;
      sol = (my_struct *)realloc(sol, sizeof(my_struct) * cou);
      sol[cou - 1] = st;
      perem = 0;
    } else if (st.type < 10) {
      while (stack1 != NULL && stack1->type / 2 >= st.type / 2 &&
             stack1->type != 20) {
        cou++;
        if (stack1 != NULL) {
          sol = (my_struct *)realloc(sol, sizeof(my_struct) * cou);
          sol[cou - 1] = pop(&stack1);
        } else {
          free(sol);
          return NULL;
        }
      }
      perem = 1;
      push(&stack1, st);
    } else if (st.type == 21) {
      while (stack1 != NULL && stack1->type != 20) {
        cou++;
        sol = (my_struct *)realloc(sol, sizeof(my_struct) * (cou + 1));
        sol[cou - 1] = pop(&stack1);
      }
      if (stack1 == NULL) {
        free(sol);
        return NULL;
      }
      pop(&stack1);
      perem = 0;
    } else {
      push(&stack1, st);
      if (st.type != UNMINUS) {
        perem = 1;
      } else {
        perem = 0;
      }
    }
    while (*ex == ' ')
      ex++;
  }
  while (stack1) {
    cou++;
    sol = (my_struct *)realloc(sol, sizeof(my_struct) * cou);
    sol[cou - 1] = pop(&stack1);
  }
  sol = (my_struct *)realloc(sol, sizeof(my_struct) * (cou + 1));
  st.num = 0;
  st.type = END;
  sol[cou] = st;
  push(&stack1, st);
  sol[cou] = pop(&stack1);
  if (stack1 != NULL) {
    while (stack1 != NULL)
      pop(&stack1);
    free(sol);
    return NULL;
  }
  return sol;
}

int validation(my_struct *ex) {
  int sol = 1, i = 0, counter = 0;
  if (ex == NULL) {
    sol = 0;
  } else {
    while (ex[i].type != END) {
      if (ex[i].type < 2 && ex[i].type >= 0) {
        counter++;
      } else if (ex[i].type < 8) {
        counter--;
      } else if (ex[i].type == 20) {
        sol = 0;
      }
      i++;
    }
    if (counter != 1)
      sol = 0;
  }
  return sol;
}

double polish(my_struct *ex, double x) {
  double sol = 0, buff = 0;
  my_struct *stack = NULL;
  my_struct elembuff = {0};
  if (ex == NULL) {
    return 0;
  }
  int cou = 0;
  while (ex[cou].type != END) {
    elembuff.num = ex[cou].num;
    elembuff.type = ex[cou].type;
    switch (elembuff.type) {
    case 0:
      push(&stack, elembuff);
      break;
    case 1:
      ex[cou].num = x;
      elembuff.num = ex[cou].num;
      push(&stack, elembuff);
      break;
    case 2:
      buff = stack->num;
      pop(&stack);
      stack->num += buff;
      break;
    case 3:
      buff = stack->num;
      pop(&stack);
      stack->num -= buff;
      break;
    case 4:
      buff = stack->num;
      pop(&stack);
      stack->num *= buff;
      break;
    case 5:
      buff = stack->num;
      pop(&stack);
      stack->num /= buff;
      break;
    case 6:
      buff = stack->num;
      pop(&stack);
      stack->num = pow(stack->num, buff);
      break;
    case 7:
      buff = stack->num;
      pop(&stack);
      stack->num = fmod(stack->num, buff);
      break;
    case 10:
      stack->num = -1 * stack->num;
      break;
    case 11:
      stack->num = cos(stack->num);
      break;
    case 12:
      stack->num = sin(stack->num);
      break;
    case 13:
      stack->num = tan(stack->num);
      break;
    case 14:
      stack->num = acos(stack->num);
      break;
    case 15:
      stack->num = asin(stack->num);
      break;
    case 16:
      stack->num = atan(stack->num);
      break;
    case 17:
      stack->num = sqrt(stack->num);
      break;
    case 18:
      stack->num = log(stack->num);
      break;
    case 19:
      stack->num = log10(stack->num);
      break;
    default:
      break;
    }
    cou++;
  }
  sol = stack->num;
  pop(&stack);
  return sol;
}

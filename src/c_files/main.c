#include "s21_smartcalc.h"

int main() {
  char *e = "2+2";
  double x = 1;
  my_struct *q = NULL;
  q = postfix(e);
  printf("%d\n", validation(q));
  int i = 0;
  while (q[i].type != END) {
    printf("%d %f\n", q[i].type, q[i].num);
    i++;
  }
  printf("%f\n", polish(q, x));
  free(q);
  return 0;
}

#include "s21_smartcalc.h"
#include <check.h>
#include <math.h>

START_TEST(calc_errors) {
  int error = 0;
  my_struct *a = postfix("-");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("sin()");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("5-xe");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("-123.123.123");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("ln(x-1");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("aer");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix(" /");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("1-5+18x");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("sin(x)");
  error = validation(a);
  ck_assert_int_eq(error, 1);
  free(a);

  a = postfix("100sin(x)");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("5 + 1e400");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);

  a = postfix("--12");
  error = validation(a);
  ck_assert_int_eq(error, 0);
  free(a);
}
END_TEST

START_TEST(calc_1) {
  my_struct *po = postfix("1+5");
  double x = 0;
  double ans = polish(po, x);
  double correct = 6;
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("sin(x)");
  x = 12.3;
  ans = polish(po, x);
  correct = sin(x);
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("ln(-x)/(-5)");
  x = -0.1;
  ans = polish(po, x);
  correct = log(-x) / (-5);
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("sqrt(-10-2+15)");
  x = 12.3;
  ans = polish(po, x);
  correct = sqrt(-10 - 2 + 15);
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("sqrt(x-1+1)");
  x = 12.3;
  ans = polish(po, x);
  correct = sqrt(x-1+1);
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("10 mod 2");
  x = 12.3;
  ans = polish(po, x);
  correct = 10 % 2;
  ck_assert_double_eq_tol(ans, correct, 1e-7);

  po = postfix("atan(x)");
  x = 0.5;
  ans = polish(po, x);
  correct = atan(x);
  ck_assert_double_eq_tol(ans, correct, 1e-7);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *suite;

  suite = suite_create("s21_calc");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, calc_errors);
  tcase_add_test(tcase_core, calc_1);
  
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *calc = s21_calc_suite();
  SRunner *calc_runner = srunner_create(calc);
  srunner_run_all(calc_runner, CK_VERBOSE);
  srunner_free(calc_runner);

  return 0;
}
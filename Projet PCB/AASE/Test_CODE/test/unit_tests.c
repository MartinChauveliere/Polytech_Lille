#include <check.h>
#include <stdlib.h>
#include <stdint.h>

#include "../src/functions.h"

START_TEST (test_init_LED) {
  uint32_t value_GPIO_MODER = 0x48000140;
  ck_assert_int_eq(value_GPIO_MODER,Init_LED());
}
END_TEST

START_TEST (test_delay) {
  uint32_t ms = 1000;
  ck_assert_int_eq(ms,delay(ms));
}
END_TEST

START_TEST (test_LED1_on) {
  uint32_t value_LED1_on = 0x4800001C;
  ck_assert_int_eq(value_LED1_on,LED1_on());
}
END_TEST

START_TEST (test_LED2_on) {
  uint32_t value =  0x48000014; //Base value because of GPIOA Offset
  ck_assert_int_eq(value,LED2_on());
}
END_TEST

START_TEST (test_LED1_off) {
  uint32_t value_LED1_off = 0x48000014; //Value of GPIOA_ODR when LED1 is off
  ck_assert_int_eq(value_LED1_off,LED1_off());
}
END_TEST

START_TEST (test_LED2_off) {
  uint32_t value_LED2_off = 0x48000004;  //Value of GPIOA_ODR when LED1 is off
  ck_assert_int_eq(value_LED2_off,LED2_off()); //Base value because of GPIOA Offset - 0x10 (pin 4=16=0x010)
}
END_TEST


Suite *suite(void)
{
    Suite *s       = suite_create ("STM32_LED_test");
    TCase *tc_core = tcase_create ("Core");
    tcase_add_test (tc_core, test_init_LED);
    tcase_add_test (tc_core, test_delay);
    tcase_add_test (tc_core, test_LED1_on);
    tcase_add_test (tc_core, test_LED2_on);
    tcase_add_test (tc_core, test_LED1_off);
    tcase_add_test (tc_core, test_LED2_off);
    suite_add_tcase (s, tc_core);
    return s;
}

int main (void)
{
    int      no_failed = 0;
    Suite   *s         = suite();
    SRunner *runner    = srunner_create (s);
    srunner_run_all (runner, CK_NORMAL);
    no_failed = srunner_ntests_failed (runner);
    srunner_free (runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

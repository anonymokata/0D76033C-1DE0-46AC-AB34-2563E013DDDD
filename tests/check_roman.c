#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/roman.h"

void setup(void)
{

}

void teardown(void)
{

}

START_TEST(test_sanity)
{
    ck_assert_int_eq(42, 42);
}
END_TEST


START_TEST(test_1_1_I)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("I");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("IA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_V)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("V");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("VA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_X)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("X");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("XA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_L)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("L");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("LA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_C)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("C");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("CA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_D)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("D");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("DA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST

START_TEST(test_1_1_M)
{
    uint8_t is_valid;
    is_valid = is_valid_numeral("M");
    ck_assert_int_eq(VALID_NUMERAL, is_valid);
    is_valid = is_valid_numeral("MA");
    ck_assert_int_eq(INVALID_NUMERAL, is_valid);
}
END_TEST


Suite * Roman_Suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_int_conv;
    
    s = suite_create("Roman");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_sanity);
    suite_add_tcase(s, tc_core);
    
    /* Validation test case */
    tc_int_conv = tcase_create("Validation Conversions");
    tcase_add_checked_fixture(tc_int_conv, setup, teardown);
    tcase_add_test(tc_int_conv, test_1_1_I);
    tcase_add_test(tc_int_conv, test_1_1_V);
    tcase_add_test(tc_int_conv, test_1_1_X);
    tcase_add_test(tc_int_conv, test_1_1_L);
    tcase_add_test(tc_int_conv, test_1_1_C);
    tcase_add_test(tc_int_conv, test_1_1_D);
    tcase_add_test(tc_int_conv, test_1_1_M);
    suite_add_tcase(s, tc_int_conv);

    

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = Roman_Suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

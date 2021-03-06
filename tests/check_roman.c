#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/roman.h"

Roman* r;

void setup(void)
{
    r = roman_create();
}

void teardown(void)
{
    roman_free(r);
}

START_TEST(test_sanity)
{
    ck_assert_int_eq(42, 42);
}
END_TEST

START_TEST(test_roman_numeral_subtraction_simple_req_3_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "II", "I", result);
    ck_assert_str_eq("I", result);
}
END_TEST

START_TEST(test_roman_numeral_subtraction_borrow_chain_req_3_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "MM", "I", result);
    ck_assert_str_eq("MCMXCIX", result);
}
END_TEST

START_TEST(test_roman_numeral_subtraction_le_zero_req_3_2)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "I", "II", result);
    ck_assert_str_eq("", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "I", "X", result);
    ck_assert_str_eq("", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "I", "M", result);
    ck_assert_str_eq("", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "I", "I", result);
    ck_assert_str_eq("", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "X", "X", result);
    ck_assert_str_eq("", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "M", "M", result);
    ck_assert_str_eq("", result);
}
END_TEST

START_TEST(test_roman_numeral_subtraction_invalid_inputs_req_3_1)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "BAD", "XLII", result);
    ck_assert_str_eq("Invalid Input", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_subtract(r, "XLII", "BAD", result);
    ck_assert_str_eq("Invalid Input", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);
    roman_subtract(r, "XLII", "XLII", result);
    ck_assert_str_ne("Invalid Input", result);
}
END_TEST

START_TEST(test_random_additions)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XIV", "LX", result);
    ck_assert_str_eq("LXXIV", result);
}
END_TEST

START_TEST(test_addition_out_of_range)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "MM", "MM", result);
    ck_assert_str_eq("Out of Range", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "MMI", "MM", result);
    ck_assert_str_eq("Out of Range", result);
}
END_TEST

START_TEST(test_roman_numeral_addition_simple_req_2_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 

    // Basic test
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "II", "I", result);
    ck_assert_str_eq("III", result);
}
END_TEST

START_TEST(test_roman_numeral_addition_expansion_required_req_2_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "IV", "I", result);
    ck_assert_str_eq("V", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "IX", "I", result);
    ck_assert_str_eq("X", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XL", "X", result);
    ck_assert_str_eq("L", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XC", "X", result);
    ck_assert_str_eq("C", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "CD", "C", result);
    ck_assert_str_eq("D", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "CM", "C", result);
    ck_assert_str_eq("M", result);
}
END_TEST

START_TEST(test_roman_numeral_addition_compacting_result_req_2_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 

    // We need to make sure that the results are being compacted properly 
    // meaning things like IIII -> IV  and VIIII -> IX
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "II", "II", result);
    ck_assert_str_eq("IV", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "VII", "II", result);
    ck_assert_str_eq("IX", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XX", "XX", result);
    ck_assert_str_eq("XL", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "LXX", "XX", result);
    ck_assert_str_eq("XC", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "CC", "CC", result);
    ck_assert_str_eq("CD", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "DCC", "CC", result);
    ck_assert_str_eq("CM", result);
}
END_TEST

START_TEST(test_roman_numeral_addition_simple_magnitue_req_2_3)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 

    // Basic test that increases the magnigtue of numeral
    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "III", "III", result);
    ck_assert_str_eq("VI", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "III", "II", result);
    ck_assert_str_eq("V", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "V", "V", result);
    ck_assert_str_eq("X", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XXX", "XX", result);
    ck_assert_str_eq("L", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "L", "L", result);
    ck_assert_str_eq("C", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "CC", "CCC", result);
    ck_assert_str_eq("D", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "D", "D", result);
    ck_assert_str_eq("M", result);
}
END_TEST

START_TEST(test_roman_numeral_addition_invalid_inputs_req_2_1)
{
    uint8_t result[MAX_ROMAN_LENGTH]; 

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "BAD", "XLII", result);
    ck_assert_str_eq("Invalid Input", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);    
    roman_add(r, "XLII", "BAD", result);
    ck_assert_str_eq("Invalid Input", result);

    memset(result, '\0', MAX_ROMAN_LENGTH);
    roman_add(r, "XLII", "XLII", result);
    ck_assert_str_ne("Invalid Input", result);
}
END_TEST

START_TEST(test_max_roman_numeral_less_than_4000_req_1_7)
{
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("M"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("MM"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("MMM"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("MMMCMXCIX"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("MMMM"));
}
END_TEST

START_TEST(test_V_L_D_repeats_no_more_than_one_time_req_1_6)
{
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("V"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("VV"));

    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("L"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("LL"));

    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("D"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("DD"));
}
END_TEST

START_TEST(test_I_X_C_repeats_no_more_than_three_times_req_1_5)
{
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("I"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("II"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("III"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("IIII"));

    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("X"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("XX"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("XXX"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("XXXX"));

    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("C"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("CC"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("CCC"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("CCCC"));
}
END_TEST


START_TEST(test_valid_roman_letters_req_1_1)
{
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("I"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("V"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("X"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("L"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("C"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("D"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("M"));
    ck_assert_int_eq(VALID_NUMERAL, is_valid_numeral("MDCLXVI"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("MDCLXVIA"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("9MDCLXVI"));
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("MDCTLXVI"));
}
END_TEST

START_TEST(test_seg_fault_protection)
{   
    // Make sure long - normal looking - numerals are filtered out
    ck_assert_int_eq(INVALID_NUMERAL, is_valid_numeral("XXXXXXXXXXXXXXXXXXXXXXXXX"));
}
END_TEST

Suite * Roman_Suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_int_conv;
    TCase *tc_add;
    TCase *tc_sub;
    
    s = suite_create("Roman");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_sanity);
    tcase_add_test(tc_core, test_seg_fault_protection);
    suite_add_tcase(s, tc_core);
    
    /* Validation test case */
    tc_int_conv = tcase_create("Validation Conversions");
    tcase_add_checked_fixture(tc_int_conv, setup, teardown);
    tcase_add_test(tc_int_conv, test_valid_roman_letters_req_1_1);
    tcase_add_test(tc_int_conv, test_I_X_C_repeats_no_more_than_three_times_req_1_5);
    tcase_add_test(tc_int_conv, test_V_L_D_repeats_no_more_than_one_time_req_1_6);
    tcase_add_test(tc_int_conv, test_max_roman_numeral_less_than_4000_req_1_7);
    suite_add_tcase(s, tc_int_conv);

    /* Addition test case */
    tc_add = tcase_create("Addition");
    tcase_add_checked_fixture(tc_add, setup, teardown);
    tcase_add_test(tc_add, test_roman_numeral_addition_invalid_inputs_req_2_1);
    tcase_add_test(tc_add, test_roman_numeral_addition_simple_req_2_3);
    tcase_add_test(tc_add, test_roman_numeral_addition_simple_magnitue_req_2_3);
    tcase_add_test(tc_add, test_roman_numeral_addition_compacting_result_req_2_3);
    tcase_add_test(tc_add, test_roman_numeral_addition_expansion_required_req_2_3);
    tcase_add_test(tc_add, test_random_additions);
    tcase_add_test(tc_add, test_addition_out_of_range);
    suite_add_tcase(s, tc_add);
    
    /* Subtraction test case */
    tc_sub = tcase_create("Subtraction");
    tcase_add_checked_fixture(tc_sub, setup, teardown);
    tcase_add_test(tc_sub, test_roman_numeral_subtraction_invalid_inputs_req_3_1);
    tcase_add_test(tc_sub, test_roman_numeral_subtraction_simple_req_3_3);
    tcase_add_test(tc_sub, test_roman_numeral_subtraction_borrow_chain_req_3_3);
    tcase_add_test(tc_sub, test_roman_numeral_subtraction_le_zero_req_3_2);
    suite_add_tcase(s, tc_sub);
    
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

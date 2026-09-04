#ifndef UNIT_TEST_H 
#define UNIT_TEST_H 
#include "my_string.h" 
 
Status test_init_default_returns_nonNULL(char* buffer, int length); 

Status test_get_size_on_init_default_returns_0(char* buffer, int length);

Status test_ssaid_my_string_destroy_sets_string_to_null(char* buffer, int length);

Status test_ssaid_my_string_destroy_makes_empty_string(char* buffer, int length);

Status test_ssaid_check_for_capacity_my_string_init_c_string(char* buffer, int length);

Status test_ssaid_my_string_get_capacity_returns_int(char* buffer, int length);

Status test_ssaid_my_string_get_size_returns_int(char* buffer, int length);

Status test_ssaid_my_string_compare_returns_even(char* buffer, int length);

Status test_ssaid_my_string_compare_returns_left_bigger(char* buffer, int length);

Status test_ssaid_my_string_compare_returns_right_bigger(char* buffer, int length);

Status test_ssaid_my_string_extraction_returns_success(char* buffer, int length);

Status test_ssaid_my_string_insertion_returns_success(char* buffer, int length);

Status test_ssaid_my_string_push_back_returns_success(char* buffer, int length);

Status test_ssaid_my_string_pop_back_returns_success(char* buffer, int length);

Status test_ssaid_my_string_at_returns_char_address(char* buffer, int length);

Status test_ssaid_my_string_c_str_returns_string(char* buffer, int length);

Status test_ssaid_my_string_concat_returns_success(char* buffer, int length);

Status test_ssaid_my_string_empty_returns_true(char* buffer, int length);

Status test_ssaid_my_string_empty_returns_false(char* buffer, int length);
 
#endif

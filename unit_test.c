#include <stdio.h> 
#include "unit_test.h"

int main(int argc, char* argv[]) 
{
	Status (*tests[])(char*, int) = 
	{
		test_init_default_returns_nonNULL,
                test_get_size_on_init_default_returns_0,
                test_ssaid_my_string_destroy_sets_string_to_null,
                test_ssaid_check_for_capacity_my_string_init_c_string,
                test_ssaid_my_string_get_capacity_returns_int,
                test_ssaid_my_string_get_size_returns_int,
                test_ssaid_my_string_compare_returns_even,
                test_ssaid_my_string_extraction_returns_success,
                test_ssaid_my_string_insertion_returns_success,
		test_ssaid_my_string_push_back_returns_success,
		test_ssaid_my_string_pop_back_returns_success,
		test_ssaid_my_string_at_returns_char_address,
		test_ssaid_my_string_c_str_returns_string,
		test_ssaid_my_string_concat_returns_success,
		test_ssaid_my_string_empty_returns_true,
		test_ssaid_my_string_empty_returns_false,
		test_ssaid_my_string_destroy_makes_empty_string,
		test_ssaid_my_string_compare_returns_right_bigger,
		test_ssaid_my_string_compare_returns_left_bigger
	}; 
	int number_of_functions = sizeof(tests) / sizeof(tests[0]); 
	int i; 
	char buffer[500]; 
	int success_count = 0; 
	int failure_count = 0; 

	for(i=0; i<number_of_functions; i++) 
	{ 
		if(tests[i](buffer, 500) == FAILURE)
		{ 
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			// printf("PASS: Test %d passed\n", i); 
			// printf("\t%s\n", buffer);
			success_count++;
		}
	} 
	printf("Total number of tests: %d\n", number_of_functions); 
	printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count, number_of_functions);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length) 
{ 
   MY_STRING hString = NULL; 
 
   hString = my_string_init_default(); 
 
   if(hString == NULL) 
   { 
      strncpy(buffer, "test_init_default_returns_nonNULL\n" 
                   "my_string_init_default returns NULL", length); 
      return FAILURE; 
   } 
   else 
   { 
      my_string_destroy(&hString); 
      strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length); 
      return SUCCESS; 
   } 
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_get_size(hString) != 0)
   {
      status = FAILURE;
      printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                   "Did not receive 0 from get_size after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                   , length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_ssaid_my_string_destroy_sets_string_to_null(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	my_string_destroy(&hString);

	if(hString == NULL)
	{
		strncpy(buffer, "test_ssaid_my_string_destroy_sets_string_to_null\n"
                   "my_string_destroy sets string to NULL", length);
		status = SUCCESS;
	}
	else
	{
		strncpy(buffer, "test_ssaid_my_string_destroy_sets_string_to_null\n"
                   "my_string_destroy doesn't set string to NULL", length);
		status = FAILURE;
	}

	return status;
}

Status test_ssaid_my_string_destroy_makes_empty_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	hString = my_string_init_c_string("Hello");
	my_string_destroy(&hString);

	if(my_string_empty(hString) == TRUE)
	{
		strncpy(buffer, "test_ssaid_my_string_destroy_makes_empty_string\n"
                   "my_string_destroy makes an empty string", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_destroy_makes_empty_string\n"
                   "my_string_destroy doesn't make an empty string", length);
                status = FAILURE;
        }

	return status;
}

Status test_ssaid_check_for_capacity_my_string_init_c_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	int string_size;

	hString = my_string_init_c_string("Hello");
	string_size = my_string_get_capacity(hString);

	if(string_size != 6)
	{
		strncpy(buffer, "test_ssaid_check_for_capacity_my_string_init_c_string\n"
                   "my_string_init_c_string doesn't increase capacity correctly", length);
                status = FAILURE;
	}
	else
	{
		strncpy(buffer, "test_ssaid_check_for_capacity_my_string_init_c_string\n"
                   "my_string_init_c_string increases capacity correctly", length);
                status = SUCCESS;
	}
	
	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_get_capacity_returns_int(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	int capacity;

	hString = my_string_init_c_string("Hello");
	capacity = my_string_get_capacity(hString);

	if(capacity == 6)
	{
		strncpy(buffer, "test_ssaid_my_string_get_capacity_returns_int\n"
                   "my_string_get_capacity returns correct capacity", length);
                status = SUCCESS;
	}
	else
	{
		printf("expected capacity 6, but returned capacity %d\n", capacity);
		strncpy(buffer, "test_ssaid_my_string_get_capacity_returns_int\n"
                   "my_string_get_capacity did not return correct capacity", length);
                status = FAILURE;
	}

	my_string_destroy(&hString);
	return status;

}

Status test_ssaid_my_string_get_size_returns_int(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	int size;

	hString = my_string_init_c_string("Hello");
	size = my_string_get_size(hString);

	if(size == 5)
	{
		 strncpy(buffer, "test_ssaid_my_string_get_size_returns_int\n"
                   "my_string_get_size returns correct size", length);
                status = SUCCESS;
	}
	else
	{
		printf("expected size 5, but returned size %d\n", size);
                strncpy(buffer, "test_ssaid_my_string_get_size_returns_int\n"
                   "my_string_get_size did not return correct size", length);
                status = FAILURE;
	}

	my_string_destroy(&hString);
	return status;

}

Status test_ssaid_my_string_compare_returns_even(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	hString1 = my_string_init_default();
	hString2 = my_string_init_default();
	Status status;
	int compare_value;

	hString1 = my_string_init_c_string("Hello");
	hString2 = my_string_init_c_string("Hello");

	compare_value = my_string_compare(hString1, hString2);

	if(compare_value == 0)
	{
		strncpy(buffer, "test_ssaid_my_string_compare_returns_int\n"
                   "my_string_compare returns the correct integer", length);
                status = SUCCESS;
	}
	else
	{
		printf("expected value 0, but returned value %d\n", compare_value);
                strncpy(buffer, "test_ssaid_my_string_compare_returns_int\n"
                   "my_string_compare did not return correct output", length);
                status = FAILURE;
	}

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_ssaid_my_string_compare_returns_left_bigger(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
        MY_STRING hString2 = NULL;
        hString1 = my_string_init_default();
        hString2 = my_string_init_default();
        Status status;
        int compare_value;

        hString1 = my_string_init_c_string("Helloo");
        hString2 = my_string_init_c_string("Hello");

        compare_value = my_string_compare(hString1, hString2);

	if(compare_value == 1)
        {
                strncpy(buffer, "test_ssaid_my_string_compare_returns_left_bigger\n"
                   "my_string_compare returns the correct integer", length);
                status = SUCCESS;
        }
        else
        {
                printf("expected value 1, but returned value %d\n", compare_value);
                strncpy(buffer, "test_ssaid_my_string_compare_returns_left_bigger\n"
                   "my_string_compare did not return correct output", length);
                status = FAILURE;
        }

        my_string_destroy(&hString1);
        my_string_destroy(&hString2);
        return status;
}

Status test_ssaid_my_string_compare_returns_right_bigger(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
        MY_STRING hString2 = NULL;
        hString1 = my_string_init_default();
        hString2 = my_string_init_default();
        Status status;
        int compare_value;

        hString1 = my_string_init_c_string("Hello");
        hString2 = my_string_init_c_string("Helloo");

	compare_value = my_string_compare(hString1, hString2);

	if(compare_value == -1)
	{
		strncpy(buffer, "test_ssaid_my_string_compare_returns_right_bigger\n"
                   "my_string_compare returns the correct integer", length);
                status = SUCCESS;
	}
	else
        {
                printf("expected value -1, but returned value %d\n", compare_value);
                strncpy(buffer, "test_ssaid_my_string_compare_returns_right_bigger\n"
                   "my_string_compare did not return correct output", length);
                status = FAILURE;
        }

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_ssaid_my_string_extraction_returns_success(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	FILE* fp;

	fp = fopen("simple.txt", "r");

	if(my_string_extraction(hString, fp) == SUCCESS)
	{
		strncpy(buffer, "test_ssaid_my_string_extraction_returns_success\n"
                   "my_string_extraction returns the correct status", length);
                status = SUCCESS;
	}
	else
	{
		strncpy(buffer, "test_ssaid_my_string_extraction_returns_success\n"
                   "my_string_extraction did not return correct status", length);
                status = FAILURE;
	}

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_insertion_returns_success(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	hString = my_string_init_c_string("Hello");
	
	if(my_string_insertion(hString, stdout) == SUCCESS)
	{
		printf("\n");
		strncpy(buffer, "test_ssaid_my_string_insertion_returns_success\n"
                   "my_string_insertion returns the correct status", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_insertion_returns_success\n"
                   "my_string_insertion did not return correct status", length);
                status = FAILURE;
        }

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_push_back_returns_success(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	hString = my_string_init_c_string("Hell");

	if(my_string_push_back(hString, 'o') == SUCCESS)
	{
		strncpy(buffer, "test_ssaid_my_string_push_back_returns_success\n"
                   "my_string_push_back returns the correct status", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_push_back_returns_success\n"
                   "my_string_push_back did not return correct status", length);
                status = FAILURE;
        }

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_pop_back_returns_success(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	hString = my_string_init_c_string("Helloo");
	
	if(my_string_pop_back(hString) == SUCCESS)
	{
		strncpy(buffer, "test_ssaid_my_string_pop_back_returns_success\n"
                   "my_string_pop_back returns the correct status", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_pop_back_returns_success\n"
                   "my_string_pop_back did not return correct status", length);
                status = FAILURE;
        }

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_at_returns_char_address(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	char c;

	hString = my_string_init_c_string("Hello");
	c = *my_string_at(hString, 0);

	if(c == 'H')
	{
		strncpy(buffer, "test_ssaid_my_string_at_returns_char_address\n"
                   "my_string_at returns the correct character address", length);
                status = SUCCESS;
	}
	else
	{
		printf("expected character H, but returned value %c\n", c);
                strncpy(buffer, "test_ssaid_my_string_at_returns_char_address\n"
                   "my_string_at did not return correct character address", length);
                status = FAILURE;
	}

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_c_str_returns_string(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;
	char* c;

	hString = my_string_init_c_string("Hello");
	c = my_string_c_str(hString);

	if(c[0] == 'H')
	{
		strncpy(buffer, "test_ssaid_my_string_c_str_returns_string\n"
                   "my_string_c_str returns the correct character address", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_c_str_returns_char_string\n"
                   "my_string_c_str did not return correct character string", length);
                status = FAILURE;
        }

	my_string_destroy(&hString);
	return status;
}

Status test_ssaid_my_string_concat_returns_success(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	hString1 = my_string_init_default();
	hString2 = my_string_init_default();
	Status status;

	hString1 = my_string_init_c_string("Hello ");
	hString2 = my_string_init_c_string("World");

	if(my_string_concat(hString1, hString2) == SUCCESS)
	{
		strncpy(buffer, "test_ssaid_my_string_concat_returns_success\n"
                   "my_string_concat returns the correct status", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_concat_returns_success\n"
                   "my_string_concat did not return correct status", length);
                status = FAILURE;
        }

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status test_ssaid_my_string_empty_returns_true(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;

	if(my_string_empty(hString) == TRUE)
	{
		strncpy(buffer, "test_ssaid_my_string_empty_returns_true\n"
                   "my_string_empty returns the correct result", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_empty_returns_true\n"
                   "my_string_empty did not return the correct result", length);
                status = FAILURE;
        }

	return status;
}

Status test_ssaid_my_string_empty_returns_false(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	hString = my_string_init_c_string("Hello");

	if(my_string_empty(hString) == FALSE)
	{
		strncpy(buffer, "test_ssaid_my_string_empty_returns_false\n"
                   "my_string_empty returns the correct result", length);
                status = SUCCESS;
	}
	else
        {
                strncpy(buffer, "test_ssaid_my_string_empty_returns_false\n"
                   "my_string_empty did not return the correct result", length);
                status = FAILURE;
        }

	my_string_destroy(&hString);
	return status;
}

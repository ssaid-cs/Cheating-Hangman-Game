#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
	int size;
	int capacity;
	char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pstring = NULL;	
	pstring = (My_string*)malloc(sizeof(My_string));
	if (pstring == NULL)
	{
		printf("error initializing data - exiting program...");
		free(pstring);
		pstring = NULL;
		exit(1);
	}

	else
	{
		pstring->capacity = 7;
		pstring->size = 0;
		pstring->data = (char*)malloc(sizeof(char)*pstring->capacity);
		if(pstring->data == NULL)
		{
			printf("error initializing data - exiting program...");
			free(pstring);
			exit(1);
		}
	}
	
	return pstring;
}


MY_STRING my_string_init_c_string(const char* c_string)
{
	int i;
	int count = 0;

	count = (int)strlen(c_string);

	My_string* pstring = NULL;

	pstring = (My_string*)malloc(sizeof(My_string));                
	if (pstring == NULL) 
	{  
		printf("error initializing data - exiting program...");
                free(pstring);
                pstring = NULL;
                exit(1);
        }

	else
	{
		pstring->capacity = (count + 1);
		pstring->size = count;
		pstring->data = (char*)malloc(sizeof(char)*pstring->capacity);
		if(pstring->data == NULL)
		{
			free(pstring);
			return NULL;
		}

		i = 0;
		while (c_string[i] != '\0')
		{
			pstring->data[i] = c_string[i];
			i++;
		}
	}

	return pstring;
}


int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string* pstring = (My_string*) hMy_string;
	return pstring->capacity;
}


int my_string_get_size(MY_STRING hMy_string)
{
	My_string* pstring = (My_string*) hMy_string;
	return pstring->size;
}


int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* lpstring = (My_string*) hLeft_string;
    	My_string* rpstring = (My_string*) hRight_string;

    	int min = (lpstring->size < rpstring->size) ? lpstring->size : rpstring->size;

    	for (int i = 0; i < min; i++)
    	{
        	if (lpstring->data[i] < rpstring->data[i]) 
			return -1;
        	if (lpstring->data[i] > rpstring->data[i]) 
			return 1;
    	}

    	if (lpstring->size < rpstring->size) return -1;
    	if (lpstring->size > rpstring->size) return 1;

    	return 0;
}


void my_string_destroy(MY_STRING* phMy_string)
{
	My_string* pstring = (My_string*) *phMy_string;
	free(pstring->data);
	free(pstring);
	*phMy_string = NULL;

	return;
}


Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	int noc;
	My_string* pstring = (My_string*) hMy_string;

	if(pstring == NULL || fp == NULL)
		return FAILURE;
	
	pstring->size = 0;

	do
	{
		noc = fgetc(fp);
		if (noc == EOF)
			return FAILURE;
	} while (isspace(noc));
	
	while(noc != EOF && !isspace(noc))
	{	
		
		if(pstring->size >= pstring->capacity)
		{
			int new_cap = pstring->capacity * 2;
    			char* new_data = (char*) realloc(pstring->data, sizeof(char) * new_cap);

    			if (new_data == NULL)
        			return FAILURE;

    			pstring->data = new_data;
			pstring->capacity = new_cap;
		}

		pstring->data[pstring->size++] = (char)noc;
		noc = fgetc(fp);
	}	

	if(noc != EOF && isspace(noc))
		ungetc(noc, fp);

	return SUCCESS;
	
}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	int i;
	My_string* pstring = (My_string*) hMy_string;
	
	if(pstring == NULL || fp == NULL)
		return FAILURE;

	for(i = 0; i < pstring->size; i++)
	{
		fputc(pstring->data[i], fp);
	}
	return SUCCESS;
}


Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pstring = (My_string*) hMy_string;
	if(pstring == NULL)
		return FAILURE;

	if(pstring->size >= pstring->capacity)
	{
		int new_cap = pstring->capacity * 2;
		char* new_data = (char*) realloc(pstring->data, sizeof(char) * new_cap);
		if (new_data == NULL)
			return FAILURE;
		
		pstring->data = new_data;
		pstring->capacity = new_cap;    
	}

	pstring->data[pstring->size] = item;
	pstring->size += 1;
	return SUCCESS;
}


Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pstring = (My_string*)hMy_string;
	if(pstring == NULL)
		return FAILURE;
	if(pstring->size <= 0)
		return FAILURE;
	pstring->size--;

	return SUCCESS;
}


char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pstring = (My_string*) hMy_string;
	if(index < 0 || index >= pstring->capacity)
	       return NULL;	
	return &pstring->data[index];
}


char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pstring = (My_string*) hMy_string;
	if(pstring == NULL)
		return FAILURE;

	if(pstring->size >= pstring->capacity)
        {
		int new_cap = pstring->capacity + 1;
                char* new_data = (char*) realloc(pstring->data, sizeof(char) * new_cap);
                if(new_data == NULL)
                        return FAILURE;

                pstring->data = new_data;
		pstring->capacity = new_cap;
        }

	pstring->data[pstring->size] = '\0';
	return pstring->data;
}


Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* presult = (My_string*) hResult;
	if(presult == NULL)
		return FAILURE;

	My_string* pappend = (My_string*) hAppend;
	if(pappend == NULL)
		return FAILURE;

	if((presult->size + pappend->size) >= (presult->capacity + 1))
	{
                int new_cap = presult->capacity * 2;
                char* new_data = (char*) realloc(presult->data, sizeof(char) * new_cap);
                if (new_data == NULL)
                        return FAILURE;
			
                presult->data = new_data;
                presult->capacity = new_cap;
	}
	
	presult->data[presult->size] = ' ';
	presult->size += 1;
	for(int i=0; i<pappend->size; i++)
	{
		presult->data[presult->size] = pappend->data[i];
		presult->size += 1;
	}

	return SUCCESS;
}


Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pstring = (My_string*)hMy_string;
	if(pstring == NULL)
		return TRUE;
	else
		return FALSE;
}


Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight)
{
	int i;
	My_string* plstring = (My_string*) hLeft;
	if(plstring == NULL)
	{
		return FAILURE;
	}

	My_string* prstring = (My_string*) hRight;
	if(prstring == NULL)
	{
		return FAILURE;
	}

	if(prstring->size >= plstring->capacity)
	{
		int new_cap = plstring->capacity * 2;
                char* new_data = (char*) realloc(plstring->data, sizeof(char) * new_cap);
                if (new_data == NULL)
                        return FAILURE;

                plstring->data = new_data;
                plstring->capacity = new_cap;
	}

	for(i = 0; i < prstring->size; i++)
	{
		plstring->data[i] = prstring->data[i];
	}

	plstring->size = prstring->size;

	return SUCCESS;
}


MY_STRING my_string_init_copy(MY_STRING hMy_string)
{
	int i;
	My_string* pstring = (My_string*) hMy_string;
	if(pstring == NULL)
	{
		return NULL;
	}

	My_string* pstring_copy = (My_string*)malloc(sizeof(My_string) * pstring->capacity);
	if(pstring_copy == NULL)
	{
		free(pstring_copy);
		pstring_copy = NULL;
		return NULL;
	}
	else
	{
		pstring_copy->size = pstring->size;
		pstring_copy->capacity = pstring->capacity;
		pstring_copy->data = (char*)malloc(sizeof(char) * pstring->capacity);
		for(i = 0; i < pstring->size; i++)
		{
			pstring_copy->data[i] = pstring->data[i];
		}
	}

	return pstring_copy;
}


void my_string_swap(MY_STRING hLeft, MY_STRING hRight)
{
	My_string* plstring = (My_string*)hLeft;
	if(plstring == NULL)
	{
		return;
	}

	My_string* prstring = (My_string*)hRight;
	if(prstring == NULL)
	{
		return;
	}

	My_string* temp = NULL;
	temp->size = plstring->size;
	temp->capacity = plstring->capacity;
	temp->data = plstring->data;

	plstring->size = prstring->size;
	plstring->capacity = prstring->capacity;
	plstring->data = prstring->data;

	prstring->size = temp->size;
	prstring->capacity = temp->capacity;
	prstring->data = temp->data;

	free(temp->data);
	free(temp);
	temp = NULL;
}

void clear_keyboard_buffer(void)
{
	char c = 'A';
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}

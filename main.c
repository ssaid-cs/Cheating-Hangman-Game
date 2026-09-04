#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"

struct family
{
	char* pattern;
	GENERIC_VECTOR words;
};
typedef struct family Family;


char* make_pattern(MY_STRING word, char guess, int length, char* masked_word);

int same_pattern(const char* a, const char* b);

int update_masked_word(char* masked, const char* pattern, int length);

int is_complete(const char* masked);

int main(int argc, char* argv[]) 
{ 
  GENERIC_VECTOR buckets[30];
  MY_STRING word = NULL;
  FILE* fp;
  int length;
  int guesses;
  int running_total;
  int noc;
  int i;
  int j;

  //this section of code is for reading the words in the dictionary
  fp = fopen("dictionary.txt", "r");

  for(i = 0; i < 30; i++)
  {
	  buckets[i] = generic_vector_init_default(my_string_init_copy,
    my_string_destroy);
  }

  word = my_string_init_default();

  while(my_string_extraction(word, fp) == SUCCESS)
  {
	  length = my_string_get_size(word);

	  if(length > 0 && length <= 29)
	  {
		  generic_vector_push_back(buckets[length], word);
	  }
  }

  my_string_destroy(&word);
  fclose(fp);



  //this is the prompt section
  printf("What length word do you want to play with: ");
  noc = scanf("%d", &length);
  while(noc != 1 || length < 1 || length > 29 || generic_vector_get_size(buckets[length]) == 0)
  {
	  clear_keyboard_buffer();
	  printf("Please type a valid response: ");
	  noc = scanf("%d", &length);
  }

  printf("How many guesses would you like to have: ");
  noc = scanf("%d", &guesses);
  while(noc != 1 || guesses < 1)
  {
	  clear_keyboard_buffer();
          printf("Please type a valid response: ");
          noc = scanf("%d", &guesses);
  }

  printf("Would you like a running total of words remaining in the word list? Type 1 for yes or 0 for no: ");
  noc = scanf("%d", &running_total);
  while(noc != 1 || (running_total != 1 && running_total != 0))
  {
	  clear_keyboard_buffer();
	  printf("Please type a valid response: ");
	  noc = scanf("%d", &running_total);
  }



  //this is the section that sorts into families
  char* masked_word;
  char c;
  char guessed_letters[26] = {0};
  GENERIC_VECTOR current_vec = buckets[length];
  int current_size = generic_vector_get_size(current_vec);

  masked_word = malloc(length + 1);
  for(i=0;i<length;i++)
	  masked_word[i] = '_';

  masked_word[length] = '\0';

  while(guesses > 0)
  {
	  printf("\n\n\nYou have %d guesses left.", guesses);
	  printf("%s\n", masked_word);

	  if(running_total == 1)
	  {
		printf("Words remaining: %d\n", current_size);
	  }

	  printf("Enter guess: ");
	  noc = scanf(" %c", &c);
	  while(noc != 1 || !isalpha(c) || guessed_letters[tolower(c) - 'a'] == 1)
	  {
		  clear_keyboard_buffer();
		  printf("Please enter a valid response: ");
		  scanf(" %c", &c);
	  }

	  c = tolower(c);

	  guessed_letters[c - 'a'] = 1;


	  Family families[2000];
	  int family_count = 0;

	  for(i=0; i<current_size; i++)
	  {
		  MY_STRING* pstring = generic_vector_at(current_vec, i);
		  MY_STRING string = *pstring;

		  char* pattern = make_pattern(string, c, length, masked_word);

		  int found = -1;
		  for(j=0;j<family_count;j++)
		  {
			  if(same_pattern(families[j].pattern, pattern))
			  {
				  found = j;
				  break;
			  }
		  }

		  if(found == -1)
		  {
			  families[family_count].pattern = pattern;
			  families[family_count].words = generic_vector_init_default(my_string_init_copy,
                my_string_destroy);

			  generic_vector_push_back(families[family_count].words, string);
			  family_count++;
		  }

		  else
		  {
			  generic_vector_push_back(families[found].words, string);
			  free(pattern);
		  }
	  }

	  //this section of the program chooses the largest family
	  int best = 0;
	  int best_size = generic_vector_get_size(families[0].words);

	  for(i=1;i<family_count;i++)
	  {
		  int size = generic_vector_get_size(families[i].words);
		  if(size > best_size)
		  {
			  best = i;
			  best_size = size;
		  }
	  }



	  //this section is for updating the masked word
	  int revealed = update_masked_word(masked_word, families[best].pattern, length);

	  free(families[best].pattern);
	  families[best].pattern = NULL;

	  if(revealed != 1)
		  guesses--;




	  //updating the current vector and families
	  generic_vector_destroy(&current_vec);
	  current_vec = families[best].words;
	  current_size = best_size;

	  for(i=0;i<family_count;i++)
	  {
		  if(i != best)
		  {
			  free(families[i].pattern);
			  generic_vector_destroy(&families[i].words);
		  }
	  }


	  if(is_complete(masked_word) == 1)
	  {
		  printf("\n\nYou won! The word was %s\n", masked_word);
		  break;
	  }


	  if(guesses == 0)
	  {
		  MY_STRING* pstring = generic_vector_at(current_vec, 0);
		  printf("\n\nYou lose... The word was ");
		  my_string_insertion(*pstring, stdout);
		  printf("\n");
	  }
  }

  generic_vector_destroy(&current_vec);
  free(masked_word);
  for(i = 0; i < 30; i++)
  {
	  generic_vector_destroy(&buckets[i]);
  }

}


char* make_pattern(MY_STRING word, char guess, int length, char* masked_word)
{
	int i;
	char* pattern = malloc(length + 1);

	for(i=0;i<length;i++)
	{
		char c = *my_string_at(word, i);

		if(masked_word[i] != '_')
			pattern[i] = masked_word[i];
		else if(c == guess)
			pattern[i] = guess;
		else
			pattern[i] = '_';
	}

	pattern[length] = '\0';
	return pattern;
}

int same_pattern(const char* a, const char* b)
{
	return strcmp(a, b) == 0;
}

int update_masked_word(char* masked, const char* pattern, int length)
{
    int revealed = 0;

    for (int i = 0; i < length; i++) {
        if (pattern[i] != '_' && masked[i] == '_') {
            masked[i] = pattern[i];
            revealed = 1;
        }
    }

    return revealed;
}

int is_complete(const char* masked)
{
	for (int i = 0; masked[i] != '\0'; i++) {
        if (masked[i] == '_')
            return 0;
    }
    return 1;
}

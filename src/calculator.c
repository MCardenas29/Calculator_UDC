#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

const char *black_list = " \n";
const char *separators = "+-*/^()%[],|";

int main(void) 
{
	char input[MAX_INPT], **arr;
	size_t len;

	printf("> ");
	fgets(input, MAX_INPT, stdin);
	arr = parse_input(input, &len);
	for(size_t i = 0; i < len; i++)
		printf("%s\n", arr[i]);
	return 0;
}

int str_inside(char _char, char* str)
{
	size_t len = strlen(str);
	for(size_t i = 0; i < len; i++)
		if(_char == str[i]) return 1;
	return 0;
}

char **parse_input(char *input, size_t *length_out)
{
	char **arr = NULL,
		 *cut = NULL;
	size_t inpt_len = strlen(input),
			cut_len = 0;
	*length_out = 0;

	for(size_t i = 0; i < inpt_len; i++) {
		if(!str_inside(input[i], black_list)) {
			if(str_inside(input[i], separators)) {
				*length_out += 2;
				arr = realloc(arr, *length_out * sizeof(char*));
				arr[*length_out-2] = cut;
				cut = malloc(sizeof(char));
				cut[0] = input[i];
				arr[*length_out-1] = cut;
				cut_len = 0;
				cut = NULL;
			} else {
				cut_len++;
				cut = realloc(cut, cut_len * sizeof(char));
				cut[cut_len-1] = input[i];
			}
		}
	}

	(*length_out)++;
	arr = realloc(arr, *length_out * sizeof(char*));
	arr[*length_out-1] = cut;

	return arr;
}

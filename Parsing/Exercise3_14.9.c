#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int main_3()
{
	char str[100];
	printf("Please enter last + first name seperated by space\n");
	gets(str);

	char* token = strtok(str, " ");

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, "\n");
	}

	return 0;
}
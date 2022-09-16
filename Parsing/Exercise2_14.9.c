#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int main_2()
{
	char str[100];
	printf("Please enter first + last name seperated by space\n");
	gets(str);

	char* token = strtok(str, " ");

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}

	return 0;
}
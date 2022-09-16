#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int main_1()
{
	char str[100] = "123,456,789,1,2,3,4,5,6,7,2000";
	char* token = strtok(str, ",");

	int sum = 0;

	while (token != NULL)
	{
		sum = sum + atoi(token);
		token = strtok(NULL, ",");
	}

	printf("%d", sum);


	return 0;
}

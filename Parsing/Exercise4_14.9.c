#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

int main_4()
{
	FILE* f = fopen("C:\\Users\\97252\\source\\repos\\Parsing\\Parsing\\oscar_age_female.txt", "r");

	char str[1000];
	char name[1000];
	char year[1000];
	char movie[1000];
	fgets(str, 1000, f);
	char* token;

	while (fgets(str, 1000, f) != NULL)
	{
		token = strtok(str, ",");
		token = strtok(NULL, ",");
		strcpy(year, token);
		token = strtok(NULL, ",");
		token = strtok(NULL, ",");
		strcpy(name, token);
		token = strtok(NULL, "", "");
		strcpy(movie, token);

		printf("The Oskar Goes to:%s at:%s Movie:%s\n", name, year, movie);
	}

	fclose(f);

}
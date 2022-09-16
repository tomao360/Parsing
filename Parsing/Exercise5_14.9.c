#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

struct OscarActor
{
	int index;
	int year;
	char age;
	char movie[1000];
	char name[1000];
	int popularity;
	struct OscarActor* next;
	struct OscarActor* prev;
};
struct OscarActor* Head = NULL;
struct OscarActor* Tail = NULL;

struct OscarActor_Header
{
	int version;
	int itemsCount;
	char reserved[1000];
};
struct OscarActor_Header fileHeader;

//A function to create a linked list
void Add(int index, int year, char age, char movie[1000], char name[1000])
{
	struct OscarActor* currentActor;
	currentActor = (struct OscarActor*)malloc(sizeof(struct OscarActor));
	if (currentActor == NULL)
	{
		printf("Memory allocation peoblem");
		return;
	}
	else
	{
		currentActor->index = index;
		currentActor->year = year;
		currentActor->age = age;
		strcpy(currentActor->movie, movie);
		strcpy(currentActor->name, name);

		currentActor->popularity = 0;

		if (Head == NULL)
		{
			Head = currentActor;
			Tail = currentActor;
			currentActor->next = NULL;
			currentActor->prev = NULL;
		}
		else
		{
			Tail->next = currentActor;
			currentActor->prev = Tail;
			Tail = currentActor;
			currentActor->next = NULL;
		}
	}
}

//Creates a linked list from the data that gets from function Load (using this function to add the popularity field) 
void AddFromFile(int index, int year, char age, char movie[1000], char name[1000], int popularity)
{
	struct OscarActor* currentActor;
	currentActor = (struct OscarActor*)malloc(sizeof(struct OscarActor));
	if (currentActor == NULL)
	{
		printf("Memory allocation peoblem");
		return;
	}
	else
	{
		currentActor->index = index;
		currentActor->year = year;
		currentActor->age = age;
		strcpy(currentActor->movie, movie);
		strcpy(currentActor->name, name);
		currentActor->popularity = popularity;

		if (Head == NULL)
		{
			Head = currentActor;
			Tail = currentActor;
			currentActor->next = NULL;
			currentActor->prev = NULL;
		}
		else
		{
			Tail->next = currentActor;
			currentActor->prev = Tail;
			Tail = currentActor;
			currentActor->next = NULL;
		}
	}
}

//A function to read the file
void LoadFile()
{
	FILE* f = fopen("C:\\Users\\97252\\source\\repos\\Parsing\\Parsing\\oscar_age_female.txt", "r");
	if (f == NULL)
	{
		printf("Error opening the file");
		return;
	}

	char str[1000];
	int index, year;
	char age;
	char name[1000];
	char movie[1000];
	char* token;

	fgets(str, 1000, f);

	while (fgets(str, 1000, f) != NULL) //Reads the file line after line and parsing it
	{
		token = strtok(str, ",");
		index = atoi(token);
		token = strtok(NULL, ",");
		year = atoi(token);
		token = strtok(NULL, ",");
		age = atoi(token);
		token = strtok(NULL, ",");
		strcpy(name, token);
		token = strtok(NULL, "", "");
		strcpy(movie, token);

		Add(index, year, age, movie, name); //Send to Add function to create the linked list
	}

	fclose(f);
}

//A function to free the linked list
void FreeList()
{
	struct OscarActor* currentActor = Head;
	struct OscarActor* release;

	while (currentActor != NULL)
	{
		release = currentActor;
		currentActor = currentActor->next;
		free(release);
	}

	Head = NULL;
	Tail = NULL;
}

//A function to print the linked list
void PrintList()
{
	struct OscarActor* currentActor = Head;

	while (currentActor != NULL)
	{
		printf("The Oscar Goes to:\nIndex:%d Name:%s Year:%d Age:%d Movie:%s Popularity:%d\n", currentActor->index, currentActor->name, currentActor->year, currentActor->age, currentActor->movie, currentActor->popularity);
		currentActor = currentActor->next;
	}
}

//A function that prints the actors who received an Oscar that year
void PrintAllMoviesForYear(int Year)
{
	struct OscarActor* currentActor = Head;

	while (currentActor != NULL)
	{
		if (currentActor->year == Year)
		{
			printf("The actors who received an Oscar in:%d are: Name:%s Age:%d Movie:%s\n",Year, currentActor->name, currentActor->age, currentActor->movie);
		}

		currentActor = currentActor->next;
	}
}

//A function that receives an index and prints its data
void GetMovieByIndex(int Index)
{
	struct OscarActor* currentActor = Head;

	while (currentActor != NULL)
	{
		if (currentActor->index == Index)
		{
			printf("Index:%d Year:%d Age:%d Movie:%s Name:%s\n", currentActor->index, currentActor->year, currentActor->age, currentActor->movie, currentActor->name);
		}

		currentActor = currentActor->next;
	}
}


void Switch(struct OscarActor* item)
{
	if (item == NULL) //No Items in the list
	{
		printf("No need to swap. There is no Items in the list");
		return;
	}
	else if (item->next == NULL) //One Item in the list
	{
		printf("No need to swap. There is only 1 Item in the list.");
		return;
	}
	else if (item == Head && item->next == Tail) //2 Items in the list: Head and Tail
	{
		item->prev = Tail;
		item->next = NULL;
		Tail->prev = NULL;
		Tail->next = item;
		Tail = item;
		Head = item->prev;
	}
	else if (item == Head && item->next != NULL) //2 first Items in the list
	{
		item->next = item->next->next;
		item->next->prev->next = item;
		item->next->prev->prev = NULL;
		item->prev = item->next->prev;
		item->next->prev = item;
		Head = item->prev;
	}
	else if (item->next == Tail && item->prev != NULL) //2 last Items in the list
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
		item->next->next = item;
		item->prev = item->next;
		item->next = NULL;
		Tail = item;
	}
	else //2 middle Items
	{
		item->prev->next = item->next;
		item->next = item->next->next;
		item->next->prev->prev = item->prev;
		item->prev = item->next->prev;
		item->next->prev->next = item;
		item->next->prev = item;
	}
}

//Sort the list by Age
void BubbleSort()
{
	struct OscarActor* currentActor = Head;
	if (currentActor == NULL)
	{
		printf("The list is empty");
		return;
	}

	int counter = 1;
	while (counter != 0)
	{
		counter = 0;
		currentActor = Head;

		while (currentActor != NULL)
		{
			if (currentActor->next != NULL && currentActor->age > currentActor->next->age)
			{
				Switch(currentActor);
				counter++;
				currentActor = currentActor->prev;
			}

			currentActor = currentActor->next;
		}
	}
}

//A function that counts how many items are in the list
int GetItemCount()
{
	struct OscarActor* currentActor = Head;
	int count = 0;

	while (currentActor != NULL)
	{
		count = count + 1;
		currentActor = currentActor->next;
	}

	return count;
}

//Adds popularity to the actor
void UpdatePopularity(int Inedx)
{
	struct OscarActor* currentActor = Head;

	while (currentActor != NULL)
	{
		if (currentActor->index == Inedx)
		{
			currentActor->popularity = currentActor->popularity + 1;
			//printf("Index:%d-Popularity:%d\n", currentActor->index, currentActor->popularity);
			return; //As soon as you find the index, you exit the loop
		}

		currentActor = currentActor->next;
	}
}

//A function that grills random numbers and updates the actor's popularity
void Run()
{
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		UpdatePopularity(rand() % 89 + 1); //לקבל מספרים רנדומליים בטווח של כמות הפריטים ברשימה 
	}
}

//A function that saves the linked list to a file
void Save(char filename[100])
{
	struct OscarActor* currentActor = Head;

	FILE* f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("Error opening the file");
		return;
	}
	else
	{
		fwrite(&fileHeader, sizeof(struct OscarActor_Header), 1, f); //Write the header into the file

		for (int i = 0; i < fileHeader.itemsCount; i++) //write the struct OscarActor into the file
		{
			fwrite(currentActor, sizeof(struct OscarActor), 1, f);
			currentActor = currentActor->next;
		}

		fclose(f);
	}
}

//A function that reads the linked list from a file
void Load(char filename[100])
{
	FILE* f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("Error opening the file");
		return;
	}
	else
	{
		int read = fread(&fileHeader, sizeof(struct OscarActor_Header), 1, f); //Read the header from the file
		if (read == 0)
		{
			printf("ERROR");
			return;
		}

		for (int i = 0; i < fileHeader.itemsCount; i++) //Read the struct OscarActor from the file
		{
			struct OscarActor* currentActor = (struct OscarActor*)malloc(sizeof(struct OscarActor));
			if (currentActor == NULL)
			{
				printf("Memory allocation peoblem");
				return;
			}

			read = fread(currentActor, sizeof(struct OscarActor), 1, f);
			AddFromFile(currentActor->index, currentActor->year, currentActor->age, currentActor->movie, currentActor->name, currentActor->popularity); //Build the list
			free(currentActor);
		}

		fclose(f);

	}
}

//A function that prints the most popular win
void mostPopular()
{
	struct OscarActor* currentActor = Head;
	struct OscarActor* mostPopular = Head;

	while (currentActor != NULL)
	{
		if (currentActor->popularity > mostPopular->popularity)
		{
			mostPopular = currentActor;
		}

		currentActor = currentActor->next;
	}

	printf("The most popular Actor is: %s", mostPopular->name);
}



int main()
{
	//LoadFile();
	//PrintList();
	//PrintAllMoviesForYear(1963);
	//GetMovieByIndex(23);
	//BubbleSort();
	//GetItemCount();
	//UpdatePopularity(29);
	//Run();
	//PrintList();
	//mostPopular();
	//FreeList();

	LoadFile();
	Run();
	Run();
	Run();
	PrintList();
	mostPopular();

	fileHeader.itemsCount = GetItemCount();
	fileHeader.version = 1;

	char fileName[100];
	printf("Please enter file name to save: ");
	scanf("%s", fileName);
	Save(fileName);
	FreeList();
	Load(fileName);
	PrintList();
	
	return 0;
}
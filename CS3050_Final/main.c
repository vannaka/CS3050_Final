//This file contains the main method
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINELENGTH 80

typedef struct capitalNode {
	char* cityName;
	int visited;
	struct capitalNode *parent;
	char* stateName;
	struct capitalListNode* neighborCities;
}capitalNode;

typedef struct capitalListNode {
	capitalNode* city;
	int dist;
	struct capitalListNode* next;
}capitalListNode;


//functions
void inputCapitals(char*);

int isDigit(char* );
capitalNode* newCapital(char* token, char* token2);
capitalListNode* newCapitalListNode(char* token, int);

//global variables
capitalNode** cities;


int main(int argc,  char* argv[]) {

	cities = malloc(sizeof(capitalNode*) * 50);

	//inputCapitals(argv[1]);
	inputCapitals("capitalsnum.txt");

	scanf("%d");
	return 0;
}

void inputCapitals(char* inputFile)
{
	FILE* input;
	if ((input = fopen(inputFile, "r")) == NULL)
	{
		perror("\nUnable to open file %s", inputFile);
		exit(0);
	}

	char inputLine[MAXLINELENGTH];
	char* token;
	char* token2;
	capitalNode* capital = NULL;
	int capitalNumber = 0;

	//parse out input file
	while (fgets(inputLine, MAXLINELENGTH, input) != NULL)
	{
		token = strtok(inputLine, "-");
		token2 = strtok(NULL, "\n");

		//token2 is a city name
		if (isDigit(token2) == 0) 
		{
			if (capital != NULL)
			{
				cities[capitalNumber] = capital;
				capital = NULL;
				
				capitalNumber++;
			}
			capital = newCapital(token, token2);

		}
		// token2 is a distance
		else
		{
			//create capital list node
			int distance = atoi(token2);
			capitalListNode* newNeighbor = newCapitalListNode(token, distance);
			if (capital->neighborCities == NULL) 
			{
				capital->neighborCities = newNeighbor;
			}
			else 
			{
				capitalListNode* curr = capital->neighborCities;
				while (curr->next != NULL)
				{
					curr = curr->next;
				}
				curr->next = newNeighbor;
			}
		}
	}
}

capitalNode* newCapital(char* token, char* token2)
{
	//copy strings over to new strings to be used in the node
	char* stateName = malloc(sizeof(char) * 50);
	char* cityName = malloc(sizeof(char) * 50);
	strcpy(stateName, token);
	strcpy(cityName, token2);

	capitalNode* newNode = malloc(sizeof(capitalNode));
	newNode->stateName = stateName;
	newNode->cityName = cityName;
	newNode->neighborCities = NULL;

	return newNode;
}
capitalListNode* newCapitalListNode(char* token, int distance)
{
	char* cityName = malloc(sizeof(char) * 50);
	strcpy(cityName, token);

	capitalListNode* newNode = malloc(sizeof(capitalListNode));
	newNode->city = cityName;
	newNode->dist = distance;
	newNode->next = NULL;

	return newNode;
}

int isDigit(char* input)
{
	int digit = 0;
	unsigned int i = 0;

	while (i < strlen(input))
	{
		digit = isdigit(input[i]);
	
		if (digit == 0)
			return digit;
		i++;
	}
	return digit;
}
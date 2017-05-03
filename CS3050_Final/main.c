//This file contains the main method
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

#define MAXLINELENGTH 80
#define HASHSIZE 100

typedef struct capitalNode {
	char cityName[50];
	char stateName[50];
	int visited;
	struct capitalNode *parent;
	struct capitalListNode* neighborCities;
	struct capitalNode *nextHash;
}capitalNode;

typedef struct capitalListNode {
	capitalNode city[50];
	int dist;
	struct capitalListNode* next;
}capitalListNode;


//functions
void inputCapitals(char*);
capitalNode* newCapital(char* token, char* token2);
capitalListNode* newCapitalListNode(char* token, int);
int isNumber(char* input);
capitalNode* getCapital(char* cityName);
void insertHash(capitalNode* capital);
int calcHash(char* city);
void printAdjCities(capitalNode *capital);

//global variables
capitalNode* cities[HASHSIZE];


int main(int argc,  char* argv[]) {
	//inputCapitals(argv[1]);
	inputCapitals("capitalsnum.txt");

	capitalNode *hold = getCapital("Jefferson City");
	printAdjCities(hold);

	getc(stdin);

	return 0;
}

// used to test hash table
void printAdjCities(capitalNode *capital) {
	capitalListNode *hold = capital->neighborCities;

	while (hold != NULL) {
		printf("\n%s, %d", hold->city, hold->dist);
		hold = hold->next;
	}

	printf("\n");
}

// build graph
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

	// parse out input file
	while (fgets(inputLine, MAXLINELENGTH, input) != NULL)
	{
		token = strtok(inputLine, "-");
		token2 = strtok(NULL, "\n");

		// token2 is a city name
		if (isNumber(token2) == 0)
		{
			if (capital != NULL)
			{
				// add capitol to graph once all its adjacent nodes are read in
				insertHash(capital);
				//cities[capitalNumber] = capital;
				capital = NULL;
				
				capitalNumber++;
			}
			capital = newCapital(token, token2);

		}
		// token2 is a distance
		else
		{
			// create capital list node
			int distance = atoi(token2);
			capitalListNode* newNeighbor = newCapitalListNode(token, distance);

			// add city to adjacent list
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

capitalNode* newCapital(char* state, char* city)
{
	capitalNode* newNode = malloc(sizeof(capitalNode));
	strcpy(newNode->stateName, state);
	strcpy(newNode->cityName, city);
	newNode->neighborCities = NULL;
	newNode->nextHash = NULL;

	return newNode;
}
capitalListNode* newCapitalListNode(char* city, int distance)
{
	capitalListNode* newNode = malloc(sizeof(capitalListNode));
	strcpy(newNode->city, city);
	newNode->dist = distance;
	newNode->next = NULL;

	return newNode;
}

// check if all the chars in a string are numbers
// return 0 if any part of the string contains something other than a number, else return 1
int isNumber(char* input) {
	int len = strlen(input);
	int i;

	for (i = 0; i < len; i++) {
		if (isdigit(input[i]) == 0) // the char is not a digit
			return 0;
	}

	return 1;
}

// calculate the hash index for a city
int calcHash(char* city) {
	int len = strlen(city);
	int i, hold = 0;

	for (i = 0; i < len; i++) {
		hold += (int)city[i];
	}

	return hold % HASHSIZE;
}

// insert a city into the hash table
void insertHash(capitalNode* capital) {
	int hash = calcHash(capital->cityName);
	capitalNode *hold;

	// check if spot is empty
	if (cities[hash] == NULL) {
		cities[hash] = capital;
	}
	// if not add to end of linked list
	else {
		hold = cities[hash];
		while (hold->nextHash != NULL) {
			hold = hold->nextHash;
		}
		hold->nextHash = capital;
	}
}

// search hash table for a city, return null if it doesnt exist
capitalNode* getCapital(char* cityName) {
	int hash = calcHash(cityName);
	capitalNode *hold;

	// check if spot is empty
	if (cities[hash] == NULL) {
		return NULL;	// the city is not in the table (graph)
	}
	// if not add to end of linked list
	else {
		hold = cities[hash];
		while (hold->nextHash != NULL) {
			hold = hold->nextHash;
		}
		return hold;	// we found the city we are looking for
	}
}

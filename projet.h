#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

char * strcat1(char * dest, char * nom, char * prenom);
long long unsigned int power(int a, int b);
int ascii(char c);
int indexer(char * name, char * firstname, int B, int N);
void blackScreen();
int menu();
void load(llist ** table, int number, int B, int N, char * filename);
int display_salary();
void display_between(int start, int end, llist ** table);
int conflict_number(llist ** table, int N);
double conflict_average(llist ** table, int N);
int delete_node(char * lastname, char * firstname, llist ** table, int N, int B);
void delete_index(llist ** table, int k);
void generate_random(int tables[], int n, int p);
int best_index_size(char * filename, int tables[], int B);
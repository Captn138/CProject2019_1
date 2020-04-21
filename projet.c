#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.h"

char * strcat1(char * dest, char * nom, char * prenom){
	// Adds the 4 first characters of the last name and
	// the 2 first characters of the first name to a new
	// 7-character long string.
	for(int i=0; i<4; i++){
		if(nom[i] == '\0'){
			dest[i] = '_';
		}else{
			dest[i] = nom[i];
		}
	}
	for(int i=0; i<2; i++){
		if(prenom[i] == '\0'){
			dest[i+4] = '_';
		}else{
			dest[i+4] = prenom[i];
		}
	}
	return dest;
}

long long unsigned int power(int a, int b){
	// Computes a to the power b:
	// using a third variable (initial value : 1)
	// multiplicated b times by a
	long long unsigned int c = a;
	if(b==0){
		return 1;
	}else if(b==1){
		return a;
	}else{
		for(int i = 1; i<b; i++){
			c *= a;
		}
	}
	return c;
}

int ascii(char c){
	//returns the integer associated to an ascii character
	return c;
}

int indexer(char * name, char * firstname, int B, int N){
	// Computes the sum of the integer corresponding to a character times B to the power i,
	// then computes this sum modulo N.
	long long unsigned int sum = 0;
	char * str = malloc(7*sizeof(char));
	strcpy(str, "");
	strcat1(str, name, firstname);
	for(int i=0; i<6; i++){
		sum += ascii(str[i]) * power(B, i);
	}
	free(str);
	return sum%N;
}

void blackScreen(){
	// Clears the screen.
    printf("%c[2J", 0x1B);
    printf("%c[%d;%dH", 0x1B, 1, 1);
}

int menu(char * file){
	// Displays the menu and returns user's choice, which is limited by a loop.
    int res;
    char c;
	FILE *f = fopen(file, "r");
    blackScreen();
	while((c = fgetc(f)) != EOF){
		printf("%c", c);
	}
	fclose(f);
    while(scanf("%d", &res)==0 || res<1 || res>11){
		scanf("%*[^\n]");
		printf("Input error! Please, enter a valid number\n");
	}
    return res;
}

void load(llist ** table, int number, int B, int N, char * filename){
	int ind, population;
	FILE * f = fopen(filename, "r");
	fscanf(f, "%d", &population);
	if(number > population){
		number = population;
	}else if(number <= 0){
		return;
	}
	for(int k = 0; k<number; k++){
		person * newperson = malloc(sizeof(person));
		newperson->nom = malloc(25*sizeof(char));
		newperson->prenom = malloc(25*sizeof(char));
		fscanf(f, "%s", newperson->nom);
		fscanf(f, "%s", newperson->prenom);
		fscanf(f, "%d", &newperson->salaire);
		ind = indexer(newperson->nom, newperson->prenom, B, N);
		add_p(ind, newperson, table);
	}
	fclose(f);
}

int display_salary(llist * node, char * lastname, char * firstname){
	//Displays the salary of an employee, using their last name, first name and their indexed line.
	while(node !=  NULL){
		if(strcmp(lastname, node->cemec->nom) != 0 || strcmp(firstname, node->cemec->prenom) != 0){
			node = node->next;
		}
	}
	if(node == NULL){
		return -1;
	}else{
		return node->cemec->salaire;
	}
}

void display_between(int start, int end, llist ** table){
	// Displays index, names and salary of all the employees between two indices included.
	llist * now;
	for(int k=start; k<=end; k++){
		now = table[k];
		while(now != NULL){
			printf("Index %3d : %s %s %d\n", k, now->cemec->nom, now->cemec->prenom, now->cemec->salaire);
			now = now->next;
		}
	}
}

int conflict_number(llist ** table, int N){
	// Displays the number of conflicts in the table, i.e. the nodes which aren't alone for an index.
	int global = 0;
	for(int k = 0; k<N; k++){
		if(table[k] != NULL && table[k]->next != NULL){
			global ++;
		}
	}
	return global;
}

double conflict_average(llist ** table, int N){
	// Displays the average conflict size: number of total conflicts / number of indices where there are conflicts.
	int global = 0, sum = 0;
	double average;
	llist * now;
	for(int k = 0; k<N; k++){
		if(table[k]->next != NULL){
			global ++;
			sum++;
			now = table[k];
			while(now != NULL){
				sum ++;
				now = now->next;
			}
		}
	}
	average = sum/global;
	return average;
}

int delete_node(char * lastname, char * firstname, llist ** table, int N, int B){
	// Deletes a certain node:
	// Searches the selected one with last name and first name.
	// Links what was before with what was after.
	// Frees all the memory space used by the node
	int ind = indexer(lastname, firstname, B, N);
	llist * now = table[ind];
	llist * prev = table[ind];
	while(now != NULL && (strcmp(lastname, now->cemec->nom) != 0 || strcmp(firstname, now->cemec->prenom) != 0)){
		prev = now;
		now = now->next;
	}
	if(now == NULL){ //case when we reached the end
		return 0;
	}else{
		if(prev == now){ //case when we found the node at position 1
			table[ind] = now->next;
		}else{ //case when we found the node somewhere else
			prev->next = now->next;
		}
		free(now->cemec->prenom);
		free(now->cemec->nom);
		free(now->cemec);
		free(now);
	}
	return 1;
		
}

void delete_index(llist ** table, int k){
	// Frees all the memory space used by all the nodes for a certain index
	llist * now;
	while(table[k] != NULL){
		now = table[k];
		table[k] = now->next;
		free(now->cemec->prenom);
		free(now->cemec->nom);
		free(now->cemec);
		free(now);
	}
}

void generate_random(int tables[], int n, int p){
	for(int k = 0; k < n; k++){
		tables[k] = rand()%p;
		for(int i = 0; i < k; i++){
			if(tables[k] == tables[i]){
				k--;
			}
		}
	}
}

int best_index_size(char * filename, int tables[], int B){
	double conflicts[10];
	for(int k = 0; k < 10; k++){
		tables[k] = -1;
	}
	generate_random(tables, 10, 100);
	for(int k = 0; k < 10; k++){
		llist ** temptable = malloc((50 + tables[k])*sizeof(llist*));
		for(int i = 0; i < 50 + tables[k]; i++){
			temptable[i] = NULL;
		}
		load(temptable, 1500, B, 50 + tables[k], filename);
		conflicts[k] = conflict_average(temptable, 50 + tables[k]);
		for(int i = 0; i < 50 + tables[k]; i++){
			delete_index(temptable, i);
		}
		free(temptable);
	}
	int best = 0;
	for(int k = 1; k < 10; k++){
		if(conflicts[best] > conflicts[k]){
			best = k;
		}
	}
	return best;
}
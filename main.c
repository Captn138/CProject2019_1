#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "projet.h"

int main(int argc, char ** argv){
	srand(time(NULL));
	int N = 100;
	int B = 83;
	llist ** table = malloc(N*sizeof(llist*));
	for(int k=0; k<N; k++){
		table[k] = NULL;
	}
	char * stop = malloc(50*sizeof(char));
	while(1){
		int c = menu(argv[2]);
		if(c == 1){ //index
			blackScreen();
			char * firstname = malloc(25*sizeof(char));
			char * lastname = malloc(25*sizeof(char));
			printf("Enter employee's last name: ");
			scanf("%s", lastname);
			printf("Enter employee's first name: ");
			scanf("%s", firstname);
			printf("Index is : %d.\n", indexer(lastname, firstname, B, N));
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 2){ //add
			blackScreen();
			char * firstname = malloc(25*sizeof(char));
			char * lastname = malloc(25*sizeof(char));
			int salary, ind;
			printf("Enter employee's last name: ");
			scanf("%s", lastname);
			printf("Enter employee's first name: ");
			scanf("%s", firstname);
			printf("Enter employee's salary: ");
			if(scanf("%d", &salary)!=1){
				printf("Wrong value for salary.\n");
			}
			ind = indexer(lastname, firstname, B, N);
			person * newboii = newperson(lastname, firstname, salary);
			add_p(ind, newboii, table);
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 3){ //load
			blackScreen();
			printf("Please, enter the number of employees to load to the database: ");
			int number;
			while(scanf("%d", &number) != 1){
				scanf("%*[^\n]");
				printf("Input error\n");
			}
			load(table, number, B, N, argv[1]);
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 4){ //display salary
			blackScreen();
			char * firstname = malloc(25*sizeof(char));
			char * lastname = malloc(25*sizeof(char));
			printf("Enter employee's last name: ");
			scanf("%s", lastname);
			printf("Enter employee's first name: ");
			scanf("%s", firstname);
			int ind = indexer(lastname, firstname, B, N), sal = display_salary(table[ind], lastname, firstname);
			if(sal == -1){
				printf("This person isn't in the database.\n");
			}else{
				printf("Salary of %s %s is %d.\n", lastname, firstname, sal);
			}
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 5){ //display between
			blackScreen();
			int start, end, a, b;
			printf("Please enter starting index (included): ");
			a = scanf("%d", &start);
			printf("Please enter ending index (included): ");
			b = scanf("%d", &end);
			if(a != 1 || b != 1 || start < 0 || end >=N || start > end){
				printf("Wrong values for start or/and end.\n");
			}else{
				display_between(start, end, table);
			}
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 6){ //conflicts number
			blackScreen();
			printf("There are %d conflicted indices.\n", conflict_number(table, N));
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 7){ //conflict average size
			blackScreen();
			printf("Average conflicts is : %lf.\n", conflict_average(table, N));
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 8){ //delete
			blackScreen();
			char * firstname = malloc(25*sizeof(char));
			char * lastname = malloc(25*sizeof(char));
			printf("Enter employee's last name: ");
			scanf("%s", lastname);
			printf("Enter employee's first name: ");
			scanf("%s", firstname);
			if(delete_node(lastname, firstname, table, N, B) == 0){
				printf("User has not been found.\n");
			}else{
				printf("User has been deleted.\n");
			}
			free(firstname);
			free(lastname);
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 9){ //delete between
			blackScreen();
			int start, end, a, b;
			printf("Select start and end indices : ");
			a = scanf("%d", &start);
			b = scanf("%d", &end);
			if(a != 1 || b != 1 || start < 0 || end >= N || start > end){
				printf("Wrong values for start or/and end.\n");
			}else{
				for(int k = start; k <= end; k++){
					delete_index(table, k);
				}
			}
		}else if(c == 10){ //best index size
			int tables[10];
			int best = best_index_size(argv[1], tables, B);
			printf("Best conflict average size is for a size of %d\n", 50 + tables[best]);
			printf("Type anything to exit: ");
			scanf("%s", stop);
		}else if(c == 11){ //exit
			blackScreen();
			return 0;
		}
	}
	return -1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person{
	char * prenom;
	char * nom;
	int salaire;
}person;

typedef struct llist{
	struct llist * next;
	person * cemec;
}llist;




person * newperson(char * lastname, char * firstname, int salary);
int alphaordre(llist * a, llist * b);
void add_p(int index, person * lui, llist ** table);


//STRUCTURE VISUALISATION HELP

//structure llist : • structure llist pointer (name : next)
//					• structure person (name : cemec) : - character string (name : prenom)
//														- character string (name : nom)
//														- integer (name : salaire)
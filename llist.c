#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

person * newperson(char * lastname, char * firstname, int salary){
	// Creates a new person structure and fills it with the amployee's informations.
	person * new = malloc(sizeof(person));
	new->nom = malloc(25*sizeof(char));
	new->prenom = malloc(25*sizeof(char));
	new->salaire = salary;
	strcpy(new->nom, lastname);
	strcpy(new->prenom, firstname);
	return new;
}

int alphaordre(llist* a, llist* b){
	//Checks the alphabetical order for two nodes.
	//returns 1 if node a is before node b, 0 if node a is after node b, -1 if node a is node b;
    //NAME CHECK
	int i=0, k=0;
	//control key k will be equal to 1 if the two names are the same and 0 if there is a difference.
    while(a->cemec->nom[i]==b->cemec->nom[i] && k == 0){ //while same letter and control key null
        if(a->cemec->nom[i] == 0){ //if both end here, control = 1
            k = 1;
        }
		i++;
    }
    if(k == 0){  //if control = 0,
        if(a->cemec->nom[i]== 0){ return 1;}
        if(b->cemec->nom[i]== 0){ return 0;}
        if(a->cemec->nom[i]==95){ return 1;}
        if(b->cemec->nom[i]==95){ return 0;}
        if(a->cemec->nom[i]>b->cemec->nom[i]){ return 0;}
        else{ return 1;}
    }
	//SURNAME CHECK
    i=0;
    k=0;
    while(k == 0 && a->cemec->prenom[i]==b->cemec->prenom[i]){
        if(a->cemec->prenom[i] == 0){
            k = 1;
        }
		i++;
    }
    if(k == 0){
        if(a->cemec->prenom[i]== 0){ return 1;}
        if(b->cemec->prenom[i]== 0){ return 0;}
        if(a->cemec->prenom[i]==95){ return 1;}
        if(b->cemec->prenom[i]==95){ return 0;}
        if(a->cemec->prenom[i]>b->cemec->prenom[i]){ return 0;}
        else{ return 1;}
    }
    return -1;
}

void add_p(int index, person * lui, llist ** table){
	// Creates a new node, in which we will add the person structure given.
	// Then, we will search its place in the table and place it correctly.
	llist * luiliste = malloc(sizeof(llist));
	luiliste->cemec = lui;
	if(table[index] == NULL){
		table[index] = luiliste;
		luiliste->next = NULL;
	}else{
		llist * now = table[index];
		llist * prev = table[index];
		int alpha;
		while(now->next != NULL && (alpha = alphaordre(luiliste, now)) == 0){
			prev = now;
			now = now->next;
		}
		if(alpha == -1){
			free(luiliste->cemec->prenom);
			free(luiliste->cemec->nom);
			free(luiliste->cemec);
			free(luiliste);
			return;
		}else if(prev != now){
			prev->next = luiliste;
			luiliste->next = now;
		}else{
			table[index] = luiliste;
			luiliste->next = now;
		}
	}
}
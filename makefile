all: compile execute

compile: main.o projet.o llist.o
	gcc -Wall main.o projet.o llist.o -o exec

main.o: main.c
	gcc -Wall main.c -c

projet.o: projet.c
	gcc -Wall projet.c -c

llist.o: llist.c
	gcc -Wall llist.c -c

execute: exec chicago.txt menu
	./exec chicago.txt menu

clean:
	rm *.o exec
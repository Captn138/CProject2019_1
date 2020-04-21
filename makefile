compile: main.c projet.c llist.c
	gcc -Wall main.c projet.c llist.c -o exec
	./exec chicago.txt menu

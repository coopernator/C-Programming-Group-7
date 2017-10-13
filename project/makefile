#makefile for creating "project"

CC = gcc
CFLAGS = -Wall -ansi

File_Manager_5000.out : project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o
	$(CC) $(CFLAGS) -o File_Manager_5000.out project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o -lm

project_james.o : project_james.c file.h user.h helper.h
	$(CC) $(CFLAGS) -c -o project_james.o project_james.c -lm

project_hai.o : project_hai.c file.h user.h
	$(CC) -Wall -ansi -o project_hai.o project_hai.c -lm -c

project_huy.o : project_huy.c user.h file.h
	$(CC) $(CFLAGS) -c -o project_huy.o project_huy.c -lm

project_hoang.o : project_hoang.c user.h
	$(CC) $(CFLAGS) -c -o project_hoang.o project_hoang.c -lm

project_jonatan.o : project_jonatan.c user.h helper.h file.h
	$(CC) $(CFLAGS) -c -o project_jonatan.o project_jonatan.c -lm

clean :
	rm project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o DB_file DB_user

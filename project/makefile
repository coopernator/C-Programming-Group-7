#makefile for creating "project"

CC = gcc
CFLAGS = -Wall -ansi -lm

project.out : project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o
	$(CC) $(CFLAGS) -o project.out project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o

project_james.o : project_james.c file.h user.h helper.h
	$(CC) $(CFLAGS) -c -o project_james.o project_james.c

project_hai.o : project_hai.c file.h user.h
	$(CC) $(CFLAGS) -c -o project_hai.o project_hai.c

project_huy.o : project_huy.c user.h file.h
	$(CC) $(CFLAGS) -c -o project_huy.o project_huy.c

project_hoang.o : project_hoang.c user.h
	$(CC) $(CFLAGS) -c -o project_hoang.o project_hoang.c	

project_jonatan.o : project_jonatan.c helper.h
	$(CC) $(CFLAGS) -c -o project_jonatan.o project_jonatan.c

clean :
	rm project_james.o project_huy.o project_hoang.o project_jonatan.o project_hai.o
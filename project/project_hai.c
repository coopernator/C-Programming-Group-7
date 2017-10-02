#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "file.h"
#include "user.h"


/**********************************************************
getFileName
-This function returns the filename
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a string that contains the filename
**********************************************************
char *getFileName(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *namep =(char*) malloc(len + 1);
	strcpy(namep, filep->name);
	return namep;
} getFileName*/

int addFile(File_t* headFilep, char name[], char type[]){
	File_t *currentp = headFilep;
	int added = 0;

	/*loop each element in the linked list until nextp is NULL*/
	while(currentp->nextp != NULL){
		currentp = currentp->nextp;
	}
	/*after the loop, currentp now points to a node after the last
	element in the linked list*/
	
	if(checkDuplicateFile(headFilep, name) != 1){
		currentp->nextp = (File_t*) malloc(sizeof(File_t));
		strcpy(currentp->nextp->name, name);
		strcpy(currentp->nextp->type, type);
		currentp->nextp->size = 0;
/*		currentp->nextp->date = date;
*/		currentp->nextp->nextp = NULL;
		added = 1;
	}
	return added;
}

char *getFileType(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *typep =(char*) malloc(len + 1);
	strcpy(typep, filep->name);
	return typep;
}

int setFileName(File_t *filep, File_t *headFilep){
	char name[MAX_FILENAME_SIZE];
	
	printf("Please enter a filename:");
	fscanf(stdin, "%[MAX_FILE_NAME-1]s", name);
	
	if(!checkDuplicateFile(headFilep, name)){
		filep->name[0] = '\0';
		strcpy(filep->name, name);
		return 1;
	}
	
	printf("Filename already exists\n");
	return 0;
}

int deleteFile(File_t *headFilep, char name[]){ 
	File_t *foundp = NULL;
	File_t *currentp = headFilep;
	
	if(headFilep == NULL){
		printf("ERROR, THERE IS NO FILE TO DELETE.\n");
		return 0;
	}
	
	foundp = searchFilename(headFilep, name);
	if(foundp == NULL){
		printf("ERROR, FILE DOES NOT EXIST.\n");
		return 0;
	}
	else{
		while( strcmp(currentp->nextp->name, foundp->name) ){
				currentp = currentp->nextp;
		}
	}
	
	currentp->nextp = foundp->nextp;
	return 1;
}

File_t *searchFilename(File_t* headFilep, char name[]){
	File_t *currentp = headFilep;
	int check = 0;
	
	while( currentp != NULL ){
		if(strcmp(currentp->name, name) == 0){
			check =1;
		}
		else{
			currentp = currentp->nextp;
		}
		
		if(check)
			break;
	}
	
	return currentp;
}

/*
date_t getDate(File_t *filep){
	date_t date;
	
	date.day = filep->date.day;
	date.month = filep->date.month;
	date.year = filep->date.year;
	
	return date;
}*/

void displayUsers(User_t *headUserp){
	User_t *currentp = headUserp;
	
	if(currentp == NULL)
		printf("THERE IS NO ACCOUNT IN THIS LINKED LIST.\n");
	else{
		while(currentp != NULL){
			printf("%s\n", currentp->username);
			currentp = currentp->nextp;
		}
	}
}

void displayFiles(File_t *headFilep){
	/*First file is a placeholder*/
	File_t *currentp = headFilep->nextp;
	
	if(currentp == NULL)
		printf("THIS USER DOES NOT HAVE ANY FILES.\n");
	else{

			printf("%-10.10s %-10.10s %-12s %s\n", 
				"Name", "Type",
				"Date", "Size"
			);
		/*loop each element in the linked list until currentp is NULL*/
		while(currentp != NULL){
			printf("%-10.10s %-10.10s" /*%02d-%02d-%04d*/"   %.3f\n", 
				currentp->name, currentp->type,
				/*currentp->date.day, currentp->date.month,
				currentp->date.year,*/ currentp->size
			);
			currentp = currentp->nextp;
		}
	}
}

int checkDuplicateUser(User_t *headUserp, char name[]){
	int check = 0;
	User_t *currentp = headUserp;
	
	/*loop each element in the linked list until currentp is NULL*/
	while(currentp != NULL){
		if(strcmp(currentp->username, name) == 0){
			check = 1;
			break;
		}
		currentp = currentp->nextp;
	}	
	return check;
}

int checkDuplicateFile(File_t *headFilep, char name[]){
	int check = 0;
	File_t *currentp = headFilep;
	
	/*loop each element in the linked list until currentp is NULL*/
	while(currentp != NULL){
		if(strcmp(currentp->name, name) == 0){
			check = 1;
			break;
		}
		currentp = currentp->nextp;
	}
	return check;
}
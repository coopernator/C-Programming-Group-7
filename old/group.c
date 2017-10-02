#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FILENAME_SIZE 21
#define MAX_FILETYPE_SIZE 11
#define MAX_USERNAME_SIZE 21
#define MAX_PASSWORD_SIZE 16
#define MAX_STATUS_SIZE 6

struct date
{
	int day;
	int month;
	int year;
};
typedef struct date date_t;

struct File
{
	char name[MAX_FILENAME_SIZE];
	char type[MAX_FILETYPE_SIZE];
	double size;
	date_t date;
	struct File* nextp;
};
typedef struct File File_t;

struct User
{	
	char username[MAX_USERNAME_SIZE];
	char password[MAX_PASSWORD_SIZE];
	char status[MAX_STATUS_SIZE];
	/**/
};
typedef struct User User_t;



/**********Function prototype**********/
date_t getDate(File_t *filep);
char *getFileType(File_t *filep);
int setFileName(File_t *filep);
int deleteFile(File_t *filep);
int deleteDirectory(char *namep);
File_t *searchName(File_t* head, char name[]);
int addFile(File_t* head, char name[], char type[], date_t date);

/*int checkDuplicate(char name[]);*/

/**********Implement**********/
date_t getDate(File_t *filep){
	date_t date;
	
	date.day = filep->date.day;
	date.month = filep->date.month;
	date.year = filep->date.year;
	
	return date;
}

char *getFileType(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *typep =(char*) malloc(len + 1);
	strcpy(typep, filep->name);
	return typep;
}

int setFileName(File_t *filep){
	char name[MAX_FILENAME_SIZE];
	
	printf("Please enter a filename:");
	fscanf(stdin, "%[MAX_FILE_NAME-1]s", name);
	
	if(/*there is no other file has the same name, need a function to check for duplicate*/1==1){
		filep->name[0] = '\0';
		strcpy(filep->name, name);
		return 1;
	}
	
	printf("Filename already exists\n");
	return 0;
}

int deleteFile(File_t *head){ 
	char name[MAX_FILENAME_SIZE];
	File_t *filep = NULL;
	File_t *currentp = NULL;
	
	printf("Please enter the filename you want to delete:");
	fscanf(stdin, "%[MAX_FILE_NAME-1]s", name);
	filep = searchName(head, name);
	if(filep == NULL){
		printf("Error, file does not exist.\n");
		return 0;
	}
	else{
		while( (strcmp(currentp->name, name)!= 0 ) && (currentp->nextp != NULL) ){
			if(strcmp(currentp->nextp->name, name)!= 0)
				currentp = currentp->nextp;
			else
				break;
		}
	}
	
	currentp->nextp = filep->nextp;
	return 1;
}

File_t *searchName(File_t* head, char name[]){
	File_t *currentp = head;
	int check = 0;
	
	while( currentp->nextp != NULL ){
		if(strcmp(currentp->name, name) != 0){
			currentp = currentp->nextp;
		}
		else{
			check =1;
		}
		
		if(check)
			break;
	}
	
	if(!check){
		return NULL;
	}
	
	return currentp;
}

int addFile(File_t* head, char name[], char type[], date_t date){
	File_t *currentp = head;
	
	while(currentp->nextp != NULL){
		currentp = currentp->nextp;
	}
	currentp->nextp = (File_t*) malloc(sizeof(File_t));
	
	strcpy(currentp->name,name);
	strcpy(currentp->type,type);
	currentp->size = 0;
	currentp->date = date;
	currentp->nextp = NULL;
	
	return 1;
}

int main(void){
	
}
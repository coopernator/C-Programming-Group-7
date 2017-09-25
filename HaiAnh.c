#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FILENAME_SIZE 11
#define MAX_FILETYPE_SIZE 11
#define MAX_USERNAME_SIZE 11
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
	int status;
	File_t *headFilep;
	struct User* nextp;
};
typedef struct User User_t;



/**********Function prototype**********/
date_t getDate(File_t *filep);
char *getFileType(File_t *filep);
int setFileName(File_t *filep, File_t *headFilep);
File_t *searchFilename(File_t* head, char name[]);
int addFile(File_t* head, char name[], char type[], date_t date); /*worked*/
int deleteFile(File_t *headFilep, char name[]); /*worked*/
void displayUsers(User_t *headUserp); /*worked*/
void displayFiles(File_t *headFilep); /*worked*/
int checkDuplicateUser(User_t *headUser, char name[]); /*worked*/
int checkDuplicateFile(File_t *headFile, char name[]); /*worked*/

/**********TEST******************************
int main (void){
	char testName[MAX_USERNAME_SIZE] = "Anh";
	char testPass[MAX_PASSWORD_SIZE] = "123";
	date_t date;
	date.day = 30;
	date.month = 12;
	date.year = 1997;
	
	User_t *headUser = NULL;
	headUser = (User_t*) malloc(sizeof(User_t));
	strcpy(headUser->username, testName);
	strcpy(headUser->password, testPass);
	headUser->headFilep = (File_t*) malloc(sizeof(File_t));
	headUser->headFilep->name[0] = '\0';
	headUser->headFilep->type[0] = '\0';
	headUser->headFilep->size = 0;
	headUser->headFilep->date = date;
	headUser->headFilep->nextp = NULL;
	headUser->status = 1;
	headUser->nextp = NULL;
	
	displayUsers(headUser);
	
	char fname1[MAX_FILENAME_SIZE] = "file1";
	char ftype1[MAX_FILETYPE_SIZE] = "text1";
	char fname2[MAX_FILENAME_SIZE] = "file2";
	char ftype2[MAX_FILETYPE_SIZE] = "text2";
	
	addFile(headUser->headFilep, fname1, ftype1, date);
	addFile(headUser->headFilep, fname2, ftype2, date);
	
	displayFiles(headUser->headFilep->nextp);
	
	return 0;
}
**********************************************/


/**********IMPLEMENT**********/


/**********************************************************
getDate
-This function return the date of the file
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a date_t that contains the file date
***********************************************************/
date_t getDate(File_t *filep){
	date_t date;
	
	date.day = filep->date.day;
	date.month = filep->date.month;
	date.year = filep->date.year;
	
	return date;
}


/**********************************************************
getFileName
-This function return the filename
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a string that contains the filename
***********************************************************/
char *getFileName(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *namep =(char*) malloc(len + 1);
	strcpy(namep, filep->name);
	return namep;
}


/**********************************************************
setFileName
-This function allows user to make change to filename
-Inputs: 
	+ *filep: pointer to the target file
	+ *headFilep: pointer to the head file of the linked list
	   where 'filep' belongs to
-Outputs:
	+ added: return 1 if successfully deleted a file, 0 otherwise
***********************************************************/
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


/**********************************************************
*searchFilename
-This function searches for a file by name
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: name of the file we are looking for
-Outputs:
	+ currentp: return the pointer to the found file, return NULL if no file matched
***********************************************************/
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



/**********************************************************
displayUsers
-This function prints all users in a user linked list 
(could be admin or user linked list)
-Inputs: 
	+ *headUserp: pointer to the head user of the linked list
-Outputs:
	+ none
***********************************************************/
void displayUsers(User_t *headUserp){
	User_t *currentp = headUserp;
	
	if(currentp == NULL)
		printf("THERE IS NO ACCOUNT IN THIS LINKED LIST.\n");
	else{
		while(currentp != NULL){
			printf("%s.\n", currentp->username);
			currentp = currentp->nextp;
		}
	}
}


/**********************************************************
displayFiles
-This function prints all files that a user has
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
-Outputs:
	none
***********************************************************/
void displayFiles(File_t *headFilep){
	File_t *currentp = headFilep;
	
	if(currentp == NULL)
		printf("THIS USER DOES NOT HAVE ANY FILES.\n");
	else{
		/*loop each element in the linked list until currentp is NULL*/
		while(currentp != NULL){
			printf("%-10.10s %-10.10s %02d-%02d-%04d %.3f\n", 
				currentp->name, currentp->type,
				currentp->date.day, currentp->date.month,
				currentp->date.year, currentp->size
			);
			currentp = currentp->nextp;
		}
	}
}


/**********************************************************
checkDuplicateUser
-This function checks if there is any duplicate user
(have the same name) in the provided linkedlist
-Inputs: 
	+ *headUserp: pointer to the head user of the linked list
	+ name[]: the name we use to look for duplicates
-Outputs:
	+ check: 1 if there is a duplicate, 0 otherwise
***********************************************************/
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


/**********************************************************
checkDuplicateFile
-This function checks if there is any duplicate file 
(have the same name) in the provided linkedlist
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: the name we use to look for duplicates
-Outputs:
	+ check: 1 if there is a duplicate, 0 otherwise
***********************************************************/
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


/**********************************************************
deleteFile
-This function deletes a file in a linked list by its name
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: name of the file we want to delete
-Outputs:
	+ added: return 1 if successfully deleted a file, 0 otherwise
***********************************************************/
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


/**********************************************************
addFile
-This function adds a new file to a linked list
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: name of the new file
	+ type[]: type of the new file
	+ date: date of the new file
-Outputs:
	+ added: return 1 if successfully added a new file, 0 otherwise
***********************************************************/
int addFile(File_t* headFilep, char name[], char type[], date_t date){
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
		currentp->nextp->date = date;
		currentp->nextp->nextp = NULL;
		added = 1;
	}
	return added;
}
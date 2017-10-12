#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "file.h"

/*****************************************************************************
Set password function 
Author: Duc Huy Nguyen
The function allows the owner of the accounts or the admin to alter the current
password's of the account to what they desired.
Input: 
pass (new password)
Output:
None
******************************************************************************/
void setPassword(User_t *userp) 
{
	char pass[PASS_SIZE];
	printf("Enter your new password: ");
	scanf("%s", pass);
	strcpy(userp->password, pass); /*set current password to a new one
							(input from user)*/
}
/*****************************************************************************
Set username function 
Author: Duc Huy Nguyen
The function allows the owner of the accounts or the admin to alter the current
username's of the account to what they desired.
Input: 
user (new username)
Output:
success (status)
******************************************************************************/

int setUsername(User_t *userp, User_t *headUserp)
{
	int success = 0;
	char user[USERNAME_SIZE];
	printf("Enter your new username: ");
	scanf("%s", user);
	if(checkDuplicateUser(headUserp, user) == 0){ /*checking for duplicates*/
	
		strcpy(userp->username, user);/*set the current username to a new one
								(input from user)*/
															
		success = 1; /*return 1 indicating that the username change success
						showing that there was no duplicates*/
	}
	else{
		printf("Username already exist.\n"); /* Failure message*/
	}
	
	return success;
}

/*****************************************************************************
Create new user function 
Author: Duc Huy Nguyen
The function allows the admin to create a new users consisting of a username
and a password
Input:
username
password
Output:
None
******************************************************************************/
int createNewUser(User_t *userlistp, int status)
{
	User_t* u = userlistp;
	char password[MAX_PASSWORD_SIZE];
	char username[MAX_USERNAME_SIZE];
	int check;


	printf("Enter desired username:\n");
	scanf("%s", username);

	check = checkDuplicateUser(u, username); /*checking for duplicates name*/

	if(check==1)
	{

		printf("That username is already taken. Please try again.\n");


		/*duplicate username therefore failure*/
		return 0;
	}

	else /*success in creating the username -> start creating new password*/
	{
		printf("Enter desired password:\n");
		scanf("%s", password);



		while(u->nextp != NULL)
		{
			u = u->nextp; 
		}

		
		u->nextp = (User_t*) malloc(sizeof(User_t));

		/*failure when the next user is considered null (no new user)*/
		if (u->nextp == NULL)
		{
			printf("A memory error has occurred, please try again\n");
			return 0;
		}

		u = u->nextp;

		strcpy(u->username, username);
		strcpy(u->password, password);
		u->status = status;
		u->nextp = NULL;

		/*initialise file LL*/
		/*First file in the linked list will not be a placeholder*/
/*		strcpy(fileHead->name,"THIS_IS_A_PLACEHOLDERFILEwejfsd");
		strcpy(fileHead->type, "0");
		u->fileHead ->size=0;
		u->fileHead ->date.day=01;
		u->fileHead ->date.month=01;
		u->fileHead ->date.year=1900;
		u->fileHead ->nextp = NULL;*/

		/*SUCCESS*/
		return 1;
	}

/*int checkDuplicateUser(User_t *headUser, char name[]); / *worked*/
/*ADD DUPLICATE USERNAME CHECKING- duplicate leads to returning a 1. */
}
/*****************************************************************************
Get file name function 
Author: Duc Huy Nguyen
The function allows a user an admin to get a file name from the database
Input: 
None
Output:
None
******************************************************************************/
char *getFileName(File_t *filep){
	int len;
	len  = strlen(filep->name); /*the length of the name*/
	char *namep =(char*) malloc(len + 1); 
	strcpy(namep, filep->name);/*get the name from file and give it to namep*/
	return namep; /*returning the name that got from the file info*/
}

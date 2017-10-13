#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

/**********************************************************
loginAuthentication - Hoang
-This function checks if the user has already registered
-Inputs: 
	+ name[]: the name we use to look for 
	+ pass[]: the password we use to look for
	+ headp: pointer for the head file of the linked list

-Outputs:
	+ return check = 1 if the user is authenticated otherwise return check = 0.
***********************************************************/
int loginAuthentication(char name[], char pass[], User_t* headp)
{
	int check = 0;
	User_t* user = headp;
	while(user!= NULL )
	{
		if((strcmp(user->username, name)==0)&&(strcmp(user->password, pass)==0))
		{
			return check = user->status;
		}
		else
		{
			user = user->nextp;
		}
	}

	return check;
}

/**********************************************************
getUsername - Hoang
-This function return the username of the user
-Inputs: 
	+ userp: pointer to the target username
-Outputs:
	+ usernamep: pointer to a string that contains the username
***********************************************************/
char *getUsername(User_t* userp)
{
	
	int length;
	length = strlen (userp->username);
	char *usernamep = (char*) malloc(length+1);
	strcpy(usernamep, userp->username);
	return usernamep;
	
}

/**********************************************************
getUsername - Hoang
-This function return the password of the user
-Inputs: 
	+ userp: pointer to the target password
-Outputs:
	+ passwordp: pointer to a string that contains the password
***********************************************************/
void *getPassword(User_t* userp)
{
	int length;
	length = strlen (userp->password);
	char *passwordp = (char*) malloc(length+1);
	strcpy(passwordp, userp->password);
	return passwordp;
}

/**********************************************************
deleteUser - Hoang
-This function allows to delete the chosen user
-Inputs: 
	+ userheadp: pointer to the head file of the linked list
	+ name[]: the name we use to look for
-Outputs:
	+ return check = 1 if the user is successfully deleted, otherwise return check = 0.
***********************************************************/
int deleteUser(User_t *userheadp, char name[])
{
	User_t *foundp = NULL;
	User_t *currentp = userheadp;

	if(userheadp->nextp == NULL)
	{
		printf("THERE IS NO USER TO DELETE\n"); /*Display the message to show that there is no user to delete*/
	}

	foundp = searchUser(userheadp, name);
	if(foundp == NULL)
	{
		printf("USER DOES NOT EXIST\n"); /*Display the error message that the user does not exist to delete*/
		return 0;
	}
	else
	{
		while( strcmp(currentp->nextp->username, foundp->username))
		{
				currentp = currentp->nextp;
		}
	}
	
	currentp->nextp = foundp->nextp;
	return 1;
}

/**********************************************************
searchUser - Hoang
-This function searches for a user in the database that
has the same name.
-Inputs: 
	+ *userheadp: pointer to the head user of the linked list
	+ name[]: the name of the user you want to look for
	
-Outputs:
	+ return a pointer to the match user; return NULL 
	if cannot find the user or there is no user in the database
***********************************************************/
User_t *searchUser(User_t* userheadp, char name[])
{
	User_t *currentp = userheadp;
	
	if(userheadp->nextp == NULL)
	{
		printf("THERE IS NO USER\n"); /*Display the message that there is no user*/
		return NULL;
	}
	
	while( currentp != NULL )
	{
		if( (strcmp(currentp->username, name)==0))
		{
			return currentp;
		}
		else
		{
			currentp = currentp->nextp;
		}
	}
	
	return NULL;
}

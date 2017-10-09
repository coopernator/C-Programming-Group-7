#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

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

char *getUsername(User_t* userp)
{
	
	int length;
	length = strlen (userp->username);
	char *usernamep = (char*) malloc(length+1);
	strcpy(usernamep, userp->username);
	return usernamep;
	
}

void *getPassword(User_t* userp)
{
	int length;
	length = strlen (userp->password);
	char *passwordp = (char*) malloc(length+1);
	strcpy(passwordp, userp->password);
	return passwordp;
}

int deleteUser(User_t *userheadp, char name[])
{
	User_t *foundp = NULL;
	User_t *currentp = userheadp;

	if(userheadp->nextp == NULL)
	{
		printf("THERE IS NO USER TO DELETE\n");
	}

	foundp = searchUser(userheadp, name);
	if(foundp == NULL)
	{
		printf("FILE DOES NOT EXIST\n");
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

User_t *searchUser(User_t* userheadp, char name[])
{
	User_t *currentp = userheadp;
	
	if(userheadp->nextp == NULL)
	{
		printf("THERE IS NO FILE\n");
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
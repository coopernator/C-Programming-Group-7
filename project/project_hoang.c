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

void *getPassword(user_t* userp)
{
	int length;
	length = strlen (userp->password);
	char *passwordp = (char*) malloc(length+1);
	strcpy(passwordp, userp->password);
	return passwordp;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "file.h"

void setPassword(User_t *userp)
{
	char pass[PASS_SIZE];
	printf("Enter your new password: ");
	scanf("%s", pass);
	strcpy(userp->password, pass);
}


void setUsername(User_t *userp)
{
	char user[USERNAME_SIZE];
	printf("Enter your new username: ");
	scanf("%s", user);
	strcpy(userp->username, user);
}

int createNewUser(User_t *userlistp, int status)
{
	User_t* u = userlistp;
	char password[MAX_PASSWORD_SIZE];
	char username[MAX_USERNAME_SIZE];
	int check;


	printf("Enter desired username:\n");
	scanf("%s", username);

	check = checkDuplicateUser(u, username);

	if(check==1)
	{

		printf("That username is already taken. Please try again.\n");


		/*duplicate username therefore failure*/
		return 0;
	}

	else
	{
		printf("Enter desired password:\n");
		scanf("%s", password);



		while(u->nextp != NULL)
		{
			u = u->nextp;
		}


		u->nextp = (User_t*) malloc(sizeof(User_t));

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

char *getFileName(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *namep =(char*) malloc(len + 1);
	strcpy(namep, filep->name);
	return namep;
}
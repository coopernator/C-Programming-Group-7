#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define USERNAME_SIZE 10
#define PASS_SIZE 10
#define NAME_SIZE 10
#define size 10

struct date
{
	int day;
	int month;
	int year;
};
typedef struct date date_t;


struct File
{
	char name[size];
	char type[size];
	double size[size];
	date_t date;
	struct File_t* nextp;
};
typedef struct File File_t;

struct User
{	
	char username[USERNAME_SIZE];
	char password[PASS_SIZE];
	char status;
	struct User_t *nextp;
};
typedef struct User User_t;


/*
	Author: Duc Huy
	this function allows the user to set a password
	Inputs: user pointer, password pointer
	Outputs: none
*/
void setPassword(User_t *userp);

void setPassword(User_t *userp)
{
	char pass[PASS_SIZE];
	printf("Enter the username you want to change");
	scanf("%s", pass);
	userp->password = pass;
}

/*
	Author: Duc Huy
	this function allows the user to set a username
	Inputs: user pointer, username pointer
	Outputs: none
*/
void setUsername(User_t *userp);

void setUsername(User_t *userp)
{
	char user[USERNAME_SIZE];
	printf("Enter the username you want to change");
	scanf("%s", user);
	userp->username = user;
}


/*
	Author: Duc Huy
	this function creates a new user
	Inputs: username and password pointers
	Outputs: 1 if successful, 0 if unsuccessful
*/
User_t createNewUser(User_t *userlistp);

User_t createNewUser(User_t *userlistp)
{
	User_t* u = userlistp;
	while(u->nextp != NULL)
	{
		u = u->nextp;
	}
	u->nextp = (User_t*) malloc(sizeof(User_t));
	
	printf("Enter desired username:\n");
	scanf("%s", u->username);
	printf("Enter desired password:\n");
	scanf("%s",  u->password);
	
}



/*****************************************************************************
file information retrieval
*****************************************************************************/

/*
	Author: Duc Huy
	get selected file name
	Inputs: file struct
	Outputs: character pointer
*/
char* getFileName(File_t file);

int main(void)
{
	
}

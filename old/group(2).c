#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define MAX_USER_SIZE 50

struct user
{
	char username[SIZE];
	char password[SIZE];
	struct user* nextp;
};
typedef struct user user_t;

void printMenu(void);
void help();
int showLoginMenu(void);


int main(void)
{
	showLoginMenu();
	user_t userlist[MAX_USER_SIZE];
}

int showLoginMenu(void)
{
	int choice;
	do
	{
		printMenu();
		scanf("%d", &choice);
		

		switch(choice)
		{
			case 1: 
												
					break;

			case 2:
									
					break;

			case 3:
								
					break;

			case 4:
					
					break; 

			case 5:
					
					break;

			case 6: 
					break;

			default:
					help();
					break;
		}
	}while (choice != 6);
	

	return 0;
}


void printMenu(void)
{
	printf("\n"
	"1. a\n"
	"2. b\n"
	"3. c\n"
	"4. d\n"
	"5. e\n"
	"6. exit the program\n"
	"Enter your choice>");
}


void help()
{
	printf("Invalid choice.\n"); 
}

int loginAuthentication(char name[], char pass[], user_t* headp)
{
	int check = 0;
	user_t* user = headp;
	while(user != NULL )
	{
		if(strcmp(user->username, name) == 0 && strcmp(user->password, pass) == 0)
		{
			return check = 1;
		}
		else
		{
			user = user->nextp;
		}
	}

	return check;

}

char getUsername(user_t* userp)
{
	 
}

void getPassword(user_t* userp)
{
	
}
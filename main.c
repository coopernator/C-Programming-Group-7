
/*Currently 'log off' is effectively quitting the program
Shouldn't be too hard to set it up so that log off prompts the user 
to log in again (or exit)

Need a way to return currentUser. Modify createNewUser, and modify login 
authentication functions


Function to check if their is an existing user

current user


WORKING
	main fram working
	change username + password
	Add a file to the list


NOT WORKING
Hoang		login authentication needs working 
Hai			print file and user list			
James		check if the file is in the directory 	(if you can't open not in directory)
James		modify print menu
Huy			save the username and passsword to database
Huy			read username and password to database
Huy			save file list to database
Huy			read file list from database
Jonatan		Get make file and headers working
Jonatan		Encryption 	



MAYBE
	Add name to USER (+username)





get file name and file type


*/
#define DEBUG


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_FILENAME_SIZE 21
#define MAX_FILETYPE_SIZE 11
#define MAX_USERNAME_SIZE 21
#define MAX_PASSWORD_SIZE 16
#define MAX_STATUS_SIZE 6


#define USERNAME_SIZE 10
#define PASS_SIZE 10
#define NAME_SIZE 10
#define SIZE 10







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
	struct User* nextp;
	/**/
};
typedef struct User User_t;








date_t getDate(File_t *filep);
char *getFileType(File_t *filep);
int setFileName(File_t *filep);
int deleteFile(File_t *filep);
int deleteDirectory(char *namep);
File_t *searchName(File_t* head, char name[]);
int addFile(File_t* head, char name[], char type[], date_t date);


void printMenu(void);
void help();
int showLoginMenu(void);
int loginAuthentication(char name[], char pass[], User_t* headp);


void showMenu(int userType);



void setPassword(User_t *userp);
void setUsername(User_t *userp);
User_t* createNewUser(User_t *userlistp);















int main()
{
	int status;
	int choice=0;
	int check /*= checkUser()*/ = 0;
	User_t* userLL;
	User_t* currentUser;
	File_t* fileLL;
	userLL = (User_t*) malloc(sizeof(User_t));
	/*Add faulty memory test*/


	/*Initialise - load files and username from database*/

	fileLL = (File_t*) malloc(sizeof(User_t));









	if(check==0)
	{

		char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

		printf("enter username\n");
		scanf("%s", name);
		printf("enter password\n");
		scanf("%s", password);


		strcpy(userLL	-> username, name);
		strcpy(userLL -> password, password);

		/*currentUser -> status = 1;	
		currentUser -> nextp =NULL;
*/
		check =1;
	}

	if(check==1)
	{
		/*Default status is incorrect user/password*/
		status=0;

		while(status==0)
		{

			int i=showLoginMenu();
					printf("Debug3\n");
	
			char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

			printf("enter username and password(+scanfcrap");

			/*Need a way to return the username as well*/
			status = loginAuthentication(name, password, userLL);

			if(status==0)
			{
				printf("Incorrect username or password, please try again\n");
			}
		}


		/*Admin User*/
		if(status==1)
		{

			while(choice!=5)
			{
				/*Depends on implementation of showMenu*/
				showMenu(1);
				scanf("%d",&choice);
				/*choice = showMenu(1);*/
				
				/*Modify account*/
				if(choice==1)
				{


					setPassword(userLL);
					setUsername(userLL);
					printf("%s,%s", userLL->username, userLL->password);

/*					showAccountMenu();
*/
					/*if()
					{
						fun1(/* user_t* user *)
					}
					if else()
					{
						fun2(/* user_t* user *)
					}*/
				}
				/*Modify user account*/
				else if(choice==2)
				{

				}
				/*encrypt/decrypt admin files*/
				else if(choice==3)
				{

					printf("Debugf1\n");

					char name[MAX_FILENAME_SIZE], type[MAX_FILETYPE_SIZE];
					date_t date2;
					strcpy(name, "nametest");
					strcpy(type, "typetest");
					date2.day =01;
					date2.month=1;
					date2.year = 1900;
										printf("Debugf2\n");



					addFile(fileLL, name, type, date2);
					printf("Debugf3\n");
					printf("%s\n", getFileType(fileLL));
					setPassword(userLL);
					setUsername(userLL);




				}
				/*encrypt/decrypt user files*/
				else if(choice==4)
				{

				}
				/*Logout*/
				else if(choice==5)
				{
					return 0;
				}
				else
				{
					printf("error");
					return 1;
				}
			}
		}

		/*normal user*/
		else if(status==2)
		{
			int choice;

			/*Depends on implementation of showMenu*/
			showMenu(2);
			scanf("%d",&choice);
			/*choice = showMenu(2);*/

			/*Modify account*/
			if(choice==1)
			{

			}			
			/*encrypt/decrypt  files*/
			else if(choice==2)
			{
				
			}
			/*Logout*/
			else if(choice==3)
			{
				return 0;
			}
			else
			{
				printf("error");
				return 1;
			}
		}

		/*public user*/
		else if(status==3)
		{
			int choice;

			/*Depends on implementation of showMenu*/
			showMenu(3);
			scanf("%d", &choice);
			/*choice = showMenu(3);*/
		
			/*compress files*/
			if(choice==1)
			{

			}
			/*Logout*/
			else if(choice==2)
			{
				return 0;
			}
			else
			{
				printf("error");
				return 1;
			}
		}

		else if(status==4)
		{
			return 0;
		}

		else
		{
			printf("error");
			return 1;
		}
	}

	else
	{
		printf("error");
		return 1;
	}


	return 0;



	/*IF user mode*/



	/*IF user mode*/
	/*
	Determine whether its Admin, User, or Public

	Admin:
		printf("Enter password");
			Options:
			enter username
				change password
				add user
				add admin
				delete own admin account
				encrypt and compress all
				decrypt and decrompress all
				encrypt and compress chosen files
				encrypt and compress all
				decrypt and decrompress all
				Modify other users account
					select user: (putblic, user..c. .)
					


		
	User:
		enter user name, then enter password
			change password
			delete account
			




	Public:
		print,		only compression is availlable
		

	



	*/
}



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

int loginAuthentication(char name[], char pass[], User_t* headp)
{
	int check = 0;
	User_t* user = headp;
	while(user != NULL )
	{
		if(strcmp(user->username, name) && strcmp(user->password, pass))
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





void showMenu(int userType){
	
	char* options = "Logged in as Administrator";
	
/*	printf("\e[1;1H\e[2J");
*/
	if(userType == 1)
	{
	/*administrator*/
		printf("%s \n\n", options);
	printf("1. Modify Details\t\t2. Modify User Details\t\t3. Encrypt/Decrypt "
		"\n4. Encrypt/Decrypt Users\t5. Exit\n");

	printf("\n");
		
	}
	else if (userType == 2)
	{
	/*standard user*/
		options = "Logged in as standard user";
		printf("%s \n\n", options);
	printf("1. Modify Details\t\t\t2. Encrypt/Decrypt"
		" 3. Compresses/Decompress\n\t3. Exit\n");

	printf("\n");
		
	}
	else if(userType == 3)
	{
		/*guest*/
		options = "Logged in as guest";
		printf("%s \n\n", options);
	printf("1. Compress/Decompress 5. Exit\n");

	printf("\n");
		
	}
}












void setPassword(User_t *userp)
{
	char pass[PASS_SIZE];
	printf("Enter the password you want to change");
	scanf("%s", pass);
	strcpy(userp->password, pass);
}


void setUsername(User_t *userp)
{
	char user[USERNAME_SIZE];
	printf("Enter the username you want to change");
	scanf("%s", user);
	strcpy(userp->username, user);
}



User_t* createNewUser(User_t *userlistp)
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

	return u;
}


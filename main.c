
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
Hoang		modify change username/password setters to work with any user
Hai			print file and user list			
James		check if the file is in the directory 	(if you can't open not in directory)
James		modify print menu
Huy			save the username and passsword to database
Huy			read username and password to database
Huy			save file list to database
Huy			read file list from database
Jonatan		Get make file and headers working
Jonatan		Encryption 	

TO DO FOR NEXT TIME



MAYBE
	Add name to USER (+username)


FUTURE
	make password invisible??
	require enter password to change user details
	Password/username setters only work to change the first node, no matter what 
		user tries to use them.
	get current user out of the login authentication function.






NOTES
	Authenticate, allows any combo in the first time, after logging out doesn't 
		allwo any combo in (not even correct one)
	May need to change parameters of the File/make file function
	Can probably functionalise some of the options that are shared between admin
		and user




*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define _DEBUG



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


/*void printMenu(void);*/
/*void help();*/
/*int showLoginMenu(void);*/
int loginAuthentication(char name[], char pass[], User_t* headp);


void showMenu(int userType);



void setPassword(User_t *userp);
void setUsername(User_t *userp);
User_t* createNewUser(User_t *userlistp, int status);















int main()
{	
	int status;		
	int choice;
	int subChoice;
	int check;

	User_t* userHead;
	User_t* currentUser;
	File_t* fileHead;


	userHead = (User_t*) malloc(sizeof(User_t));
	if (userHead == NULL)
	{
		printf("fatal error");
		return 1;
	}

	currentUser = (User_t*) malloc(sizeof(User_t));	/*USE THIS AS THE INDEX???*/
	if (currentUser == NULL)
	{
		printf("fatal error");
		return 1;
	}

	fileHead = (File_t*) malloc(sizeof(User_t));
	if (fileHead == NULL)
	{
		printf("fatal error");
		return 1;
	}




	/*Initialise - load files and username from database



	*/


	/*see if there are any users in program*/
	check /*= checkUser()*/ = 0;

	/*If no users in database*/
	if(check==0)
	{
		/*temp username and password*/
		char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

		/*Clear page*/
		printf("\e[1;1H\e[2J");

		printf("This is your first time setting up. Please enter details withou"
			"t spaces:\n");
		printf("Enter username:\n");
		scanf("%s", name);
		printf("Enter password:\n");
		scanf("%s", password);
		printf("\n");

		strcpy(userHead -> username, name);
		strcpy(userHead -> password, password);
		userHead -> status = 1;
		userHead -> nextp = NULL;


		#ifdef DEBUG
			printf("DebugMain0\n");
			printf("Details of first user:\n");
			printf("name: %s, password %s, status %d", 
				userHead -> username, userHead -> password, userHead -> status);
			printf("DebugMainEnd\n");

		#endif

		/*As there is a user, proceeds with program */
		check = 1;
	}


	/*Users in database*/
	if(check==1)
	{
		/*Loop forever (until exit condition is triggered)*/
		while(check==1)
		{
			/*Default conditions*/
			status=0;
			choice=0;
			subChoice=0;


			/*Clear page*/
			printf("\e[1;1H\e[2J");


/*NEED TO GET the CURRENT USER OUT OF LOGIN SOMEHOW*/
			/*Code for login or exitting the program*/
			while(status==0)
			{
				/*Temporary storage of name and password*/
				char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];
	
				printf("LOGIN\n"
				"Please enter your Username and password. If you don't have \n"
				"an account, please ask an Admin to create one for you.\n"
				"To exit the program, please type in EXIT (capitals).\n"
				"To access the public directory, please type in PUBLIC "
				"(in capitals).\n\n");

				printf("Enter username:\n");
				scanf("%s", name);

				/*Exit case*/
				if (! strcmp(name, "EXIT"))
				{
	
					/*Clear screen*/
					printf("\e[1;1H\e[2J");

					return 0;
				}

				/*Public user case*/
				else if (! strcmp(name, "PUBLIC"))
				{
					status = 3;
				}

				/*Normal login*/
				else
				{
					printf("Enter password:\n");
					scanf("%s", password);

					/*status should be 0, 1, or 2*/
					status = loginAuthentication(name, password, userHead);

					#ifdef DEBUG
						printf("DebugMain\n");
						printf("status(normal login) = %d\n", status);

					#endif

				}


				if(status==0)
				{
					printf("\nIncorrect username or password, please try again"
						"\n\n\n");
				}
		
			}


			/*Admin User*/
			if(status==1)
			{

				/*Stay in admin account until logoff (choice==5)*/
				while(choice!=5)
				{

					showMenu(status);
					scanf("%d",&choice);
					
					/*Modify account*/
					if(choice==1)
					{
						printf("Would you like to change your username or"
						" password?\n"
						"WIP1 Change username\n"
						"WIP2 Change password\n"
						"3 Neither\n"
						"IMPLEMENTATION is WIP\n"
							);
						scanf("%d", &subChoice);

						if(subChoice==1)
						{
							setUsername(userHead);
							printf("your new username is ...\n");
						}
						else if(subChoice==2)
						{
							setPassword(userHead);
							printf("your new password is ...\n");


						}

						else if(subChoice==3)
						{

						}

						else
						{
							printf("Please enter a valid choice\n");

						}
					}


					/*Modify user account*/
					else if(choice==2)
					{
						printf("What would you like to do (enter a number)?\n"
							"WIP1 View existing users\n"
							"WIP2 Create new user\n"
							"WIP3 Create new admin user\n"
							"WIP4 Delete user"
							"WIP5 Change user details\n"
							"6 Do nothing\n"
							"NOTE: IMPLEMENTATION IS WIP\n"
							);
						scanf("%d", &subChoice);

						if(subChoice==1)
						{

						}

						/*create new user*/
						else if(subChoice==2)
						{
							createNewUser(userHead, 2);
							printf("UNTESTD!!!!");
						}

						/*create new admin*/
						else if(subChoice==3)
						{
							createNewUser(userHead, 1);
							printf("UNTESTD!!!!");


						}

						else if(subChoice==4)
						{

						}

						else if(subChoice==5)
						{

						}

						else if(subChoice==6)
						{

						}


						else
						{
							printf("Please enter a valid choice\n");

						}

						/*if(subChoice==???),
						View existing users
						Make new user
						Modify users etc...


						

						 */


					}

					/*very WIP*/
					/*encrypt/decrypt admin files*/
					else if(choice==3)
					{

						printf("What would you like to do (enter a number)?"
							"WIP1 ..."
							"WIP2 ..."
							"WIP3 ..."
							);
						scanf("%d", &subChoice);


						#ifdef DEBUG
							printf("DebugMain\n");
						#endif

						/*Temp variables. Date is WIP*/
						char name[MAX_FILENAME_SIZE], type[MAX_FILETYPE_SIZE];
						date_t date2;

						strcpy(name, "nametest");
						strcpy(type, "typetest");
						date2.day =01;
						date2.month=1;
						date2.year = 1900;

						#ifdef DEBUG
							printf("DebugMain\n");
						#endif


						addFile(fileHead, name, type, date2);

						#ifdef DEBUG
							printf("DebugMain\n");
						#endif					
						printf("%s\n", getFileType(fileHead));
					
					}

					/*encrypt/decrypt user files*/
					else if(choice==4)
					{
						printf("What would you like to do? (enter a number)"
							"WIP1 ..."
							"WIP2 ..."
							"WIP3 ..."
							);
						scanf("%d", &subChoice);
						
					}

					/*Logout*/
					else if(choice==5)
					{
						;
					}
					else
					{
						printf("Please enter a valid choice\n");
					}
				}
			}



			/*normal user*/
			else if(status==2)
			{
				while(choice!=3)
				{
					showMenu(status);
					scanf("%d",&choice);

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
						;
					}
					else
					{
						printf("Please enter a valid choice\n");
					}
				}					

			}

			/*public user*/
			else if(status==3)
			{
				while(choice!=2)
				{
					showMenu(status);
					scanf("%d", &choice);
				
					/*compress files*/
					if(choice==1)
					{
	
					}
					/*Logout*/
					else if(choice==2)
					{
						;
					}
					else
					{
						printf("Please enter a valid choice\n");
					}
				}
			}

			else
			{
				printf("error");
				return 1;
			}
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
	
	/*there is no other file has the same name, need a function to check for duplicate*/
	if(1==1){
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
		while((strcmp(currentp->name, name)!= 0 ) && (currentp->nextp != NULL)){
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











/*int showLoginMenu(void)
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
}*/


/*void printMenu(void)
{
	printf("\n"
	"1. a\n"
	"2. b\n"
	"3. c\n"
	"4. d\n"
	"5. e\n"
	"6. exit the program\n"
	"Enter your choice>");
}*/


void help()
{
	printf("Invalid choice.\n"); 
}

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





void showMenu(int userType){
	
	char* options = "Logged in as Administrator";
	
	printf("\e[1;1H\e[2J");

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
	printf("1. Modify Details\t\t2. Encrypt/Decrypt\t\t3. Exit\n");

	printf("\n");
		
	}
	else if(userType == 3)
	{
		/*guest*/
		options = "Logged in as guest";
		printf("%s \n\n", options);
	printf("1. Compress/Decompress\t\t2. Exit\n");

	printf("\n");
		
	}
}












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



User_t* createNewUser(User_t *userlistp, int status)
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
	u->status = status;

	return u;
}


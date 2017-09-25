
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
Hai 	Delete user
james 	change uesr details



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



add current user


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
	File_t *fileHead;
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





/*void printMenu(void);*/
/*void help();*/
/*int showLoginMenu(void);*/
int loginAuthentication(char name[], char pass[], User_t* headp);


void showMenu(int userType);



void setPassword(User_t *userp);
void setUsername(User_t *userp);
User_t* createNewUser(User_t *userlistp, int status);


int checkUser(User_t* userHeadp);


char *getUsername(User_t* userp);










int main()
{	
	int status;		
	int choice;
	int subChoice;
	int check;

	User_t* userHead;
	User_t* currentUser;
/*	File_t* fileHead;
*/



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



	userHead ->fileHead = (File_t*) malloc(sizeof(User_t));
	if (userHead ->fileHead == NULL)
	{
		printf("fatal error");
		return 1;
	}




	/*Initialise - load files and username from database
	*/





	userHead ->fileHead->name[0] = '\0';
	userHead ->fileHead->type[0] = '\0';
	userHead ->fileHead->size = 0;
/*	fileHead->date = date;
*/	userHead ->fileHead->nextp = NULL;





	/*Used to ensure checkUser works properly. May be unenccessary depending
	how database file read function works*/
	userHead -> status = 0;

	/*see if there are any users in program*/
	check = checkUser(userHead);

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

		/*confirm user is now created */
		check = checkUser(userHead);
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
						"1 Change username (works but unelegant)\n"
						"2 Change password (works but unelegatn)\n"
						"3 Return to menu\n"
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
						while(subChoice!=6)
						{	
							printf("\n\nWhat would you like to do (enter a number)?\n"
								"WIP1 View existing users\n"
								"2 Create new user(works but unelegant)\n"
								"3 Create new admin user(works but unelegant)\n"
								"WIP4 Delete user\n"
								"WIP5 Change user details\n"
								"6 Return to menu\n"
								"NOTE: IMPLEMENTATION IS WIP\n"
								);
							scanf("%d", &subChoice);

							if(subChoice==1)
							{

								printf("\n\nUsers are:\n");
								displayUsers(userHead);
							}

							/*create new user*/
							else if(subChoice==2)
							{
								createNewUser(userHead, 2);
	/*							printf("UNTESTD!!!!");
	*/						}

							/*create new admin*/
							else if(subChoice==3)
							{
								createNewUser(userHead, 1);
	/*							printf("UNTESTD!!!!");
	*/

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
					}

					/*very WIP*/
					/*encrypt/decrypt admin files*/
					else if(choice==3)
					{

						printf("What would you like to do (enter a number)?\n"
							"1 Add file\n"
							"2 Delete file\n"
							"WIP3 Encrypt file\n"
							"WIP4 Decrypt file\n"
							"WIP5 Compress file\n"
							"WIP6 Decompress file\n"
							"7 show all files\n"
							"WIP8 SORT AND SEARCH IF TIME\n"
							"9 Return to menu\n"
							);
						scanf("%d", &subChoice);

						/*Dummy  variable for date*/
						if(subChoice==1)
						{

						char name[MAX_FILENAME_SIZE], type[MAX_FILETYPE_SIZE];
						date_t date2;

						printf("what is the file name");
						scanf("%s", name);
						printf("what is the file type");
						scanf("%s", type);

						
						date2.day =01;
						date2.month=1;
						date2.year = 1900;

						 

						addFile(userHead->fileHead, name, type, date2);
						printf("ADDED FILE:\n");
						printf("N: %s, T: %s", userHead->fileHead->name, 
							userHead->fileHead->type);
					
						}

						else if(subChoice==2)
						{
							char name[MAX_FILENAME_SIZE];
							printf("what is the name of the file you want to delete?\n");
							scanf("%s", name);

							deleteFile(userHead->fileHead, name);
						}


						else if(subChoice==7)
						{
							displayFiles(userHead->fileHead);
						}


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
			printf("%s\n", currentp->username);
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
	u = u->nextp;
	printf("Enter desired username:\n");
	scanf("%s", u->username);
	printf("Enter desired password:\n");
	scanf("%s",  u->password);
	u->status = status;

	return u;
}




int checkUser(User_t* userHeadp)
{
	if(userHeadp -> status == 0)
	{
		return 0;
	}
	else if( (userHeadp -> status == 1) ||(userHeadp -> status ==2))
	{
		return 1;
	}
	else
	{
		return 2;
	}


}



char *getFileType(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *typep =(char*) malloc(len + 1);
	strcpy(typep, filep->name);
	return typep;
}



char *getUsername(User_t* userp)
{
	
	int length;
	length = strlen (userp->username);
	char *usernamep = (char*) malloc(length+1);
	strcpy(usernamep, userp->username);
	return usernamep;
	
	 
}
<<<<<<< HEAD:other/main.c
/*Currently 'log off' is effectively quitting the program
Shouldn't be too hard to set it up so that log off prompts the user 
to log in again (or exit)

Need a way to return currentUser. Modify createNewUser, and modify login 
authentication functions


Function to check if their is an existing user

current user


WORKING
	main frame working
	change username + password
	Add a file to the list
=======

/*


WORKING
	Can login
	add new users
	modify your own data
	User info is preserved 


NOT WORKING/BUGS/TO DO
	FILES!!
		Can add files to the original user, can't add files to other users at all
		duplicates only detected if own ll
		CREATE NEW USER AND ADDING FILES

			I think we should change it so files is a LL, with a property of 'user'
	encryption
	compression
	delete your own account
	change another users detail (eg admin changes a users detail)
		require enter password again (see implementation for change own details)
		use a tempuser?? in place of currentuser? (should be doable)
	Delete another users account
	sort and search
	header files
	database to store file information so it is preserved across logins
	check if file is in the directory before allowing you to add it to the program
	view user function 
		Just need to display the status. 
		Also, should it display the passwords of other admin???

>>>>>>> 437f5635abbc98064695c46cc13d7b8185010806:main.c

	

JOBS for people to do
Hai			print file list			
James		check if the file is in the directory 	(if you can't open not in directory)
Huy			save file list to database
Huy			read file list from database
Jonatan		Get make file and headers working
Jonatan		Encryption 	
Hai 		Delete user
james 		change uesr details
				still worth doing??



NOTES
	May need to change parameters of the File/make file function and User
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



#define USERNAME_SIZE 10
#define PASS_SIZE 10
#define NAME_SIZE 10
#define SIZE 10


#define DB_FILE_NAME "DO_NOT_DELETE" 





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
int createNewUser(User_t *userlistp, int status);


<<<<<<< HEAD:other/main.c
int main()
=======
int checkUser(User_t* userHeadp);


char *getUsername(User_t* userp);


User_t* getCurrentUser(char* name, User_t* userHeadp);

void clear(void);

int saveUserDatabase(User_t* userp);

int readUserDatabase(User_t* userp);



/*******************************************************************************
Main function
*******************************************************************************/

int main(void)
>>>>>>> 437f5635abbc98064695c46cc13d7b8185010806:main.c
{	
	int status;		
	int choice;
	int subChoice;
	int check;

	User_t* userHeadp;
	User_t* currentUserp;



	userHeadp = (User_t*) malloc(sizeof(User_t));
	if (userHeadp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	currentUserp = (User_t*) malloc(sizeof(User_t));	/*USE THIS AS THE INDEX???*/
	if (currentUserp == NULL)
	{
		printf("fatal error");
		return 1;
	}




	/*Initialise - load files and username from database
	*/




	/*Used to ensure checkUser works properly. May be unenccessary depending
	how database file read function works*/
	userHeadp -> status = 0;


	readUserDatabase(userHeadp);

	/*see if there are any users in program*/
	check = checkUser(userHeadp);

	/*If no users in database*/
	if(check==0)
	{
		/*temp username and password*/
		char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

		/*Clear page*/
		clear();

		/*Get user name and password*/
		printf("This is your first time setting up. Please enter details withou"
			"t spaces:\n");
		printf("Enter username:\n");
		scanf("%s", name);
		printf("Enter password:\n");
		scanf("%s", password);
		printf("\n");

		/*Save username, password as the user LL head*/
		strcpy(userHeadp -> username, name);
		strcpy(userHeadp -> password, password);
		userHeadp -> status = 1;

		/*First file in the linked list will not be deleted*/
		strcpy(userHeadp->fileHead ->name,"THIS_IS_A_PLACEHOLDERFILEwejfsd");
		strcpy(userHeadp->fileHead ->type, "0");
		userHeadp->fileHead ->size=0;
		userHeadp->fileHead ->date.day=01;
		userHeadp->fileHead ->date.month=01;
		userHeadp->fileHead ->date.year=1900;
		userHeadp->fileHead ->nextp = NULL;



		userHeadp -> nextp = NULL;


		/*confirm user is now created */
		check = checkUser(userHeadp);
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


			/*Clear page*/
			clear();

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
					clear();
					
					saveUserDatabase(userHeadp);

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
					status = loginAuthentication(name, password, userHeadp);
					currentUserp = getCurrentUser(name, userHeadp);

				}


				if(status==0)
				{
					printf("\nIncorrect username or password, please try again"
						"\n\n");
				}
		
			}

			/*clear screen*/
			clear();


			/*Admin User*/
			if(status==1)
			{

				

				/*Stay in admin account until logoff (choice==5)*/
				while(choice!=5)
				{
					subChoice=0;

					showMenu(status);
					scanf("%d",&choice);
					clear();

					

					/*Modify own account*/
					if(choice==1)
					{


						/*functionalise below once makefile is working*/

						while(subChoice!=4)
						{
							/*get users choice*/
							printf(
							"Please choose an option:\n"
							"1 Change username\n"
							"2 Change password\n"
							"WIP3 Delete  account\n"
							"4 Return to menu\n"
							"IMPLEMENTATION is WIP\n"
								);
							scanf("%d", &subChoice);
							clear();

							/*Change username*/
							if(subChoice==1)
							{
								int success;
								char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];


								/*Confirm user identity*/
								printf("Please reenter your username:\n");
								scanf("%s", name);
								printf("Please reenter your password:\n");
								scanf("%s", password);

								success = loginAuthentication(name, password, currentUserp);
			
								/*Alow user to change password if login correcty*/
								if(success==(1||2))
								{
								setUsername(currentUserp);
								printf("your new username is: %s\n",currentUserp->username);
								}

								else
								{
									printf("Incorrect username or password\n");
								}

							}

							/*Change password*/
							else if(subChoice==2)
							{
								int success;
								char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];


								printf("Please reenter your username:\n");
								scanf("%s", name);
								printf("Please reenter your password:\n");
								scanf("%s", password);


								success = loginAuthentication(name, password, currentUserp);
	
								if(success==(1||2))
								{
								setPassword(currentUserp);
								printf("your new password is: %s\n",currentUserp->password);
								}

								else
								{
									printf("Incorrect username or password\n");
								}

							}


							/*DELETE account WIP*/
							else if(subChoice==3)
							{

							}

							if(subChoice==1||subChoice==2||subChoice==3)	
							{	
								printf("\n\n");
							}

							/*Return to menu*/
							else if(subChoice==4)
							{
								clear();
							}

							else
							{
								clear();
								printf("Please enter a valid choice\n");
							}


						}
					}


					/*Modify Other user's account*/
					else if(choice==2)
					{
						while(subChoice!=6)
						{	

							/*WIP - create new user - returns int based on whether there was another user or not
									print list 		- Need to include status 
							*/
							printf("What would you like to do (enter a number)?\n"
								"1 View existing users\n"
								"2 Create new user \n"
								"3 Create new admin user\n"
								"WIP4 Delete user\n"
								"WIP5 Change user details\n"
								"6 Return to menu\n"
								"NOTE: IMPLEMENTATION IS WIP\n"
								);
							scanf("%d", &subChoice);
							clear();

							/*Display existing users */
							if(subChoice==1)
							{

								printf("Current users are:\n");
								displayUsers(userHeadp);
							}

							/*create new user*/
							else if(subChoice==2)
							{
								int success = createNewUser(userHeadp, 2);
								if (success==1)
								{
									printf("You have successfully created a new user.\n");
								}
			
							
							}

							/*create new admin*/
							else if(subChoice==3)
							{
								int success = createNewUser(userHeadp, 1);
								if (success==1)
								{
									printf("You have successfully created a new Admin.\n");
								}
								
							}

							/*Delete a user very WIP*/
							else if(subChoice==4)
							{

							}

							/*Modify another users details VERY Very WIP WIP*/
							else if(subChoice==5)
							{

							}

							if(subChoice==1||subChoice==2||subChoice==3||subChoice==4||subChoice==5)	
							{	
								printf("\n\n");
							}

							/*Return to menu*/
							else if(subChoice==6)
							{
								clear();
							}


							else
							{
								clear();
								printf("Please enter a valid choice\n");

							}



							

							
						}
					}

					/*very WIP*/
					else if(choice==3)
					{
						while(subChoice!=9)
						{
							printf(
								"What would you like to do (enter a number)?\n"
								"1 View all files\n"
								"2 Add file\n"
								"3 Delete file\n"
								"WIP4 Encrypt file\n"
								"WIP5 Decrypt file\n"
								"WIP6 Compress file\n"
								"WIP7 Decompress file\n"
								"WIP8 SORT AND SEARCH IF TIME\n"
								"9 Return to menu\n"
								);
							scanf("%d", &subChoice);
							clear();

							/*Dummy  variable for date WIPWIPWIP*/


							/*Display files*/
							if(subChoice==1)
							{
								displayFiles(currentUserp->fileHead);
							}

							else if(subChoice==2)
							{

								char name[MAX_FILENAME_SIZE], type[MAX_FILETYPE_SIZE];
								date_t date2;
								int success;

								printf("what is the file name\n");
								scanf("%s", name);
								printf("what is the file type\n");
								scanf("%s", type);

								
								date2.day =01;
								date2.month=1;
								date2.year = 1900;

								 

								success = addFile(currentUserp->fileHead, name, type, date2);

								if(success==1)
								{
									printf("Successfully added file\n");
								}
								else
								{
									printf("Failed to add File. File may already be added,"
										" or file may be owned by another user\n");
								}

							}

							else if(subChoice==3)
							{
								char name[MAX_FILENAME_SIZE];
								printf("what is the name of the file you want to delete?\n");
								scanf("%s", name);

								int success = deleteFile(currentUserp->fileHead, name);

								if (success==0)
								{
									printf("You have successfully deleted your file.\n");
								}
								else
								{
									printf("File Deletion failed. Ensure you entered the correct name.\n");
								}
							}

/*							else if()
*/


							if(subChoice==1||subChoice==2||subChoice==3||subChoice==4
								||subChoice==5||subChoice==6||subChoice==7||subChoice==8)	
							{
								printf("\n\n");
							}

							/*Exit the loop*/
							else if(subChoice==9)
							{
								clear();
							}

							else
							{
								clear();
								printf("Please enter a valid choice\n");

							}


							




						}
					}

					/* VERY VERY VERY WIP encrypt/decrypt user files*/
					else if(choice==4)
					{
						printf("What would you like to do? (enter a number)"
							"WIP1 ..."
							"WIP2 ..."
							"WIP3 ..."
							);
						scanf("%d", &subChoice);
						clear();

						/*
						while()
						{
							....





							if(subChoice==1||subChoice==2||subChoice==3||subChoice==4
								||subChoice==5|| ......)	
							{
								printf("\n\n");
							}

							/ *Exit the loop* /
							else if(subChoice==9)
							{
								clear();
							}

							else
							{
								clear();
								printf("Please enter a valid choice\n");

							}




						}
						*/

							
							


						
					}

					/*Logout*/
					else if(choice==5)
					{
						;
					}
					else
					{
						clear();
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
						clear();
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
						clear();
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

<<<<<<< HEAD:other/main.c
/*
	hai
*/

=======
/**********************************************************
getDate
-This function return the date of the file
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a date_t that contains the file date
***********************************************************/
>>>>>>> 437f5635abbc98064695c46cc13d7b8185010806:main.c
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
	/*First file is a placeholder*/
	File_t *currentp = headFilep->nextp;
	
	if(currentp == NULL)
		printf("THIS USER DOES NOT HAVE ANY FILES.\n");
	else{

			printf("%-10.10s %-10.10s %-12s %s\n", 
				"Name", "Type",
				"Date", "Size"
			);
		/*loop each element in the linked list until currentp is NULL*/
		while(currentp != NULL){
			printf("%-10.10s %-10.10s %02d-%02d-%04d   %.3f\n", 
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



/*
	hoang
*/


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



/*
	jonatan
*/

void showMenu(int userType){
	
	char* options = "Logged in as Administrator";
	
/*	printf("\e[1;1H\e[2J");
*/
	if(userType == 1)
	{
	/*administrator*/
		printf("%s \n\n", options);
	printf("1. Modify Details\t\t2. Modify User Details\t\t3. Encrypt/Decrypt "
		"\n4. Encrypt/Decrypt Users\t5. Logout\n");

	printf("\n");
		
	}
	else if (userType == 2)
	{
	/*standard user*/
		options = "Logged in as standard user";
		printf("%s \n\n", options);
	printf("1. Modify Details\t\t2. Encrypt/Decrypt\t\t3. Logout\n");

	printf("\n");
		
	}
	else if(userType == 3)
	{
		/*guest*/
		options = "Logged in as guest";
		printf("%s \n\n", options);
	printf("1. Compress/Decompress\t\t2. Logout\n");

	printf("\n");
		
	}
}







/*
	Huy
*/




void setPassword(User_t *userp)
{
	char pass[PASS_SIZE];
	printf("Enter your new password: ");
	scanf("%s", pass);
	strcpy(userp->password, pass);
}

/*
	Huy
*/
void setUsername(User_t *userp)
{
	char user[USERNAME_SIZE];
	printf("Enter your new username: ");
	scanf("%s", user);
	strcpy(userp->username, user);
}


<<<<<<< HEAD:other/main.c
/*
	Huy
*/
User_t* createNewUser(User_t *userlistp, int status)
=======

int createNewUser(User_t *userlistp, int status)
>>>>>>> 437f5635abbc98064695c46cc13d7b8185010806:main.c
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
/*		strcpy(u->fileHead->name,"THIS_IS_A_PLACEHOLDERFILEwejfsd");
		strcpy(u->fileHead->type, "0");
		u->fileHead ->size=0;
		u->fileHead ->date.day=01;
		u->fileHead ->date.month=01;
		u->fileHead ->date.year=1900;
		u->fileHead ->nextp = NULL;
*/
		/*SUCCESS*/
		return 1;

	}

	

/*int checkDuplicateUser(User_t *headUser, char name[]); / *worked*/






	/*ADD DUPLICATE USERNAME CHECKING- duplicate leads to returning a 1. */
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



User_t* getCurrentUser(char* name, User_t* userHeadp)
{
	User_t* currentp = userHeadp;
	while(currentp != NULL)
	{
		if(strcmp(currentp->username, name)==0)
		{
			return currentp;
		}
		else
		{
			currentp = currentp->nextp;
		}
	}

	return currentp;
}

void clear()
{
	/*Clears the page*/
	printf("\e[1;1H\e[2J");

}








/*
 
*/
int saveUserDatabase(User_t* userp)
{
	User_t *currentp = userp;
	FILE* fp;

	fp = fopen(DB_FILE_NAME, "w");

	/*Error checking code, to determine if file opened succesfully*/
	if (fp == NULL)
	{
		printf("Did not save database correctly\n");
		return 0;
	}
	
	while(currentp != NULL)
	{
		fprintf(fp, "%d %s %s\n", 
			currentp->status,currentp->password, currentp->username);
		currentp = currentp->nextp;
	}

	fprintf(fp, "0");

	fclose(fp);

	return 1;
	
}






int readUserDatabase(User_t* userp)
{

	User_t *currentp = userp;

	/*temp storage of status, test if file is empty*/
	int check;


	FILE* fp;
	fp = fopen(DB_FILE_NAME, "r");

	if (fp ==NULL)
	{
		return 0;
	}

	fscanf(fp, "%d %s %s\n", 
				&currentp->status, currentp->password, currentp->username);


	fscanf(fp, "%d", &check);

	/*If there are more usernames*/
	while(check!=0)
	{

		currentp->nextp = (User_t*) malloc(sizeof(User_t));

		if (currentp->nextp == NULL)
		{
			printf("A memory error has occurred\n");
			return 0;
		}

		/*increment LL*/
		currentp=currentp->nextp;


		currentp->status = check;

		fscanf(fp, " %s %s\n", 
				currentp->password, currentp->username);

		fscanf(fp, "%d", &check);

	}



	currentp->nextp=NULL;
	

	

	fclose(fp);

	return 1;

}


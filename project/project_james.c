/*
WORKING
	Can login
	add new users
	modify your own data
	User info is preserved 

NOT WORKING/BUGS/TO DO
FILES!!
	Can add files to the original user, can't add files to other users at 
	all	duplicates only detected if own LL
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

JOBS for people to do
Hai			print file list			
James		check if the file is in the directory(if you can't 
			open not in directory)
Huy			save file list to database
Huy			read file list from database
Jonatan		Get make file and headers working
Jonatan		Encryption 	
Hai 		Delete user
james 		change uesr details
				still worth doing??

NOTES
	May need to change parameters of the File/make file function and User
	Can probably functionalise some of the options that are shared 
	between admin and user
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "user.h"
#include "helper.h"
#include "file.h"

#define DB_FILE_NAME "DO_NOT_DELETE"

/*****************************************************************************
Main function
*****************************************************************************/
int main()
{	
	int status;
	int choice;
	int subChoice;
	int check;

	User_t* userHeadp;
	User_t* currentUserp;
	File_t* fileHead;

	userHeadp = (User_t*) malloc(sizeof(User_t));
	if (userHeadp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	currentUserp = (User_t*) malloc(sizeof(User_t));/*USE THIS AS THE INDEX?*/
	if (currentUserp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	fileHead = (File_t*) malloc(sizeof(User_t));
	if (userHeadp == NULL)
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
		printf("This is your first time setting up. Please enter details"
			" without spaces:\n");
		printf("Enter username:\n");
		scanf("%s", name);
		printf("Enter password:\n");
		scanf("%s", password);
		printf("\n");

		/*Save username, password as the user LL head*/
		strcpy(userHeadp -> username, name);
		strcpy(userHeadp -> password, password);
		userHeadp -> status = 1;
		userHeadp -> nextp = NULL;

		/*First file in the linked list will not be deleted*/
		strcpy(fileHead ->name,"THIS_IS_A_PLACEHOLDERFILEwejfsd");
		strcpy(fileHead ->type, "0");
		fileHead ->size=0;
		strcpy(fileHead ->owner,"ADMINDEFAULTOWNER");

		fileHead ->nextp = NULL;

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
				"Please enter your Username and password. If you don't have\n"
				" an account, please ask an Admin to create one for you.\n"
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
					printf("\nIncorrect username or password, please try " 
						"again\n\n");
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
							"IMPLEMENTATION is WIP\n");
							scanf("%d", &subChoice);
							clear();

							/*Change username*/
							if(subChoice==1)
							{
								int success;
								char name[MAX_USERNAME_SIZE], 
								password[MAX_PASSWORD_SIZE];

								/*Confirm user identity*/
								printf("Please reenter your username:\n");
								scanf("%s", name);
								printf("Please reenter your password:\n");
								scanf("%s", password);

								success = loginAuthentication(name, password, 
									currentUserp);
			
								/*Alow user to change password if login 
									correcty*/
								if(success==(1||2))
								{
									setUsername(currentUserp);
									printf("your new username is: %s\n",
										currentUserp->username);
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
								char name[MAX_USERNAME_SIZE], 
									password[MAX_PASSWORD_SIZE];

								printf("Please reenter your username:\n");
								scanf("%s", name);
								printf("Please reenter your password:\n");
								scanf("%s", password);


								success = loginAuthentication(name, password, 
									currentUserp);
	
								if(success==(1||2))
								{
								setPassword(currentUserp);
								printf("your new password is: %s\n",
									currentUserp->password);
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
							/*WIP - create new user - returns int based on 
							whether there was another user or not
							print list 		- Need to include status 
							*/
							printf("What would you like to do "
								"(enter a number)?\n"
								"1 View existing users\n"
								"2 Create new user \n"
								"3 Create new admin user\n"
								"WIP4 Delete user\n"
								"WIP5 Change user details\n"
								"6 Return to menu\n"
								"NOTE: IMPLEMENTATION IS WIP\n");
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
									printf("You have successfully created"
										" a new user.\n");
								}
							}

							/*create new admin*/
							else if(subChoice==3)
							{
								int success = createNewUser(userHeadp, 1);
								if (success==1)
								{
									printf("You have successfully created a "
										"new Admin.\n");
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
							if(subChoice==1||subChoice==2||subChoice==3||
								subChoice==4||subChoice==5)	
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
								"What would you like to do "
								"(enter a number)?\n"
								"1 View all files\n"
								"2 Add file\n"
								"3 Delete file\n"
								"WIP4 Encrypt file\n"
								"WIP5 Decrypt file\n"
								"WIP6 Compress file\n"
								"WIP7 Decompress file\n"
								"WIP8 SORT AND SEARCH IF TIME\n"
								"9 Return to menu\n");
							scanf("%d", &subChoice);
							clear();

							/*Dummy  variable for date WIPWIPWIP*/

							/*Display files*/
							if(subChoice==1)
							{
								displayFiles(fileHead);
							}

							else if(subChoice==2)
							{
								char name[MAX_FILENAME_SIZE], 
									type[MAX_FILETYPE_SIZE];
								int success;

								printf("what is the file name\n");
								scanf("%s", name);
								printf("what is the file type\n");
								scanf("%s", type);

								success = addFile(fileHead, name, type);

								if(success==1)
								{
									printf("Successfully added file\n");
								}
								else
								{
									printf("Failed to add File. File may "
										"already be added, or file may be "
										"owned by another user\n");
								}
							}
							else if(subChoice==3)
							{
								char name[MAX_FILENAME_SIZE];
								printf("what is the name of the file you "
									"want to delete?\n");
								scanf("%s", name);

								int success = deleteFile(fileHead, name);

								if (success==1)
								{
									printf("You have successfully deleted "
										"your file.\n");
								}
								else
								{
									printf("File Deletion failed. Ensure you"
										" entered the correct name.\n");
								}
							}
							/*else if()*/
							if(subChoice==1||subChoice==2||subChoice==3||
								subChoice==4||subChoice==5||subChoice==6||
								subChoice==7||subChoice==8)	
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

							if(subChoice==1||subChoice==2||subChoice==3||
								subChoice==4||subChoice==5|| ......)	
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
} /*main*/

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

/*appears to produce error i.e. fp not defined even though it is */
int saveUserDatabase(User_t* userp)
{
	User_t* currentp = userp;
	FILE *fp;

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


	FILE *fp;
	fp = fopen(DB_FILE_NAME, "r");

	if (fp ==NULL)
	{
		printf("read error\n");
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
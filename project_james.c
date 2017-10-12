/*****************************************************************************

*****************************************************************************/

#include <stdio.h>	/*printf, scanf, fopen, fclose, fprintf, fscanf*/
#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*strcpy, strcmp*/
#include <math.h>

#include "user.h"	/*User_t, modifyAccount, loginAuthentication, 
getCurrentUser, displayUsers, createNewUser, readUserDatabase, confirmLogin,
saveUserDatabase, checkUser, copyUser, setUsername, setPassword */

#include "file.h"	/*readFileDatabase, saveFileDatabase, modifyFileDetails,
displayFiles, addFile, deleteFile, encryptDecrypt, createHuffman*/

#include "helper.h"	/*showmenu, clear*/


#define DB_FILE_NAME_USER "DB_user"
#define DB_FILE_NAME_FILE "DB_file"



/*****************************************************************************
Main function
*****************************************************************************/
int main(int argc, char* argv[])
{	
	User_t* userHeadp;
	User_t* currentUserp;
	User_t* tempUserp;
	File_t* fileHeadp;

	/*Create all the Linked Lists*/
	userHeadp = (User_t*) malloc(sizeof(User_t));
	if (userHeadp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	fileHeadp = (File_t*) malloc(sizeof(User_t));
	if (userHeadp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	/*Create a seperate User_t pointer to store current user*/
	currentUserp = (User_t*) malloc(sizeof(User_t));
	if (currentUserp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	/*Create a seperate user_t pointer for admin to change user details*/
	tempUserp = (User_t*) malloc(sizeof(User_t));
	if (tempUserp == NULL)
	{
		printf("fatal error");
		return 1;
	}

	/*Initialise - load files and username from database*/

	/*Used for checkUser function*/
	userHeadp -> status = 0;

	/*Copy userdatabase (if it exists) into the userHeadp LL*/
	readUserDatabase(userHeadp);

	/*Copy filedatabase into fileHeadp LL*/
	readFileDatabase(fileHeadp);


	/*see if there are users in program(check results of readUserDatabase*/
	int check = checkUser(userHeadp);


	/*Command line parsing*/

	if(argc > 1)
	{
		if(handleParsing(argc, argv, userHeadp) == 0)
		{
			free(userHeadp);
			free(fileHeadp);
			free(currentUserp);
			free(tempUserp);
			return 0;
		}
		else 
		{
			free(userHeadp);
			free(fileHeadp);
			free(currentUserp);
			free(tempUserp);				
			return 1;
		}		
	}

	/*If no users in database*/
	if(check==0)
	{

		/*Clear page*/
		clear();

		/*First User in the linked list is a placeholder*/
		strcpy(userHeadp -> username, "PLACEHOLDERRRRRRR");
		strcpy(userHeadp -> password, "aijfesdjflkaerjfpdiokld");
		userHeadp -> status = 2;
		userHeadp -> nextp = NULL;


		/*First file in the linked list is a placeholder*/
		strcpy(fileHeadp ->name,"PLACEHOLDERRRR");
		strcpy(fileHeadp ->type, "PLACEHOLDERRRR");
		strcpy(fileHeadp ->owner,"PLACEHOLDERRRR");
		fileHeadp ->size=0;
		fileHeadp ->nextp = NULL;

		/*Set up first Admin user*/
		printf("This is your first time setting up. Please enter your details"
			" below:\n");
		createNewUser(userHeadp, 1);


		saveUserDatabase(userHeadp);
		saveFileDatabase(fileHeadp);

		/*confirm user is now created */
		check = checkUser(userHeadp);
	}

	/*Loop the main program until exit condition is triggered*/
	while(check==1)
	{
		/*Default conditions*/
		int status=0;
		char choice='0';
		char subchoice='0';	

		/*Clear page*/
		clear();

		/*Code for login or exitting the program*/
		while(status==0)
		{

			/*If no admin user in the LL*/
			if(checkUser(userHeadp)==0)
			{
				printf("There is currently no admin user. Please create an "
					"admin\n");
				createNewUser(userHeadp, 1);
				saveUserDatabase(userHeadp);
				clear();
			}

			/*Temporary storage of name and password*/
			char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

			printf("LOGIN\n"
			"Please enter your Username and password. If you don't have\n"
			"an account, please ask an Admin to create one for you.\n"
			"To exit the program, please type in EXIT (capitals).\n\n");

			printf("Enter username:\n");
			scanf("%s", name);

			/*Exit case*/
			if (! strcmp(name, "EXIT"))
			{
				clear();
		
				saveUserDatabase(userHeadp);
				saveFileDatabase(fileHeadp);

				free(userHeadp);
				free(fileHeadp);
				free(currentUserp);
				free(tempUserp);

				return 0;
			}

			/*Normal login*/
			else
			{
				printf("Enter password:\n");
				scanf(" %s", password);

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

		clear();

		/*Admin User*/
		if(status==1)
		{
			/*Stay in admin account until logoff (choice==5)*/
			while(choice!='5')
			{
				subchoice='0';

				/*Shows menu for admin*/
				showMenu(status);
				scanf(" %c",&choice);
				clear();

				/*Modify own account*/
				if(choice=='1')
				{

					/*Modify user, if account is deleted, logout*/
					if(modifyAccount(userHeadp, currentUserp, 0)==1)
					{
						choice='5';
					}
					
				}

				/*Modify Other user's account*/
				else if(choice=='2')
				{
					while(subchoice!='5')
					{	
						printf("What would you like to do "
							"(enter a number)?\n"
							"1 View existing users\n"
							"2 Create new user \n"
							"3 Create new admin user\n"
							"4 Change user details\n"
							"5 Return to menu\n"
							);
						scanf(" %c", &subchoice);
						clear();

						/*Display existing users */
						if(subchoice=='1')
						{
							printf("Current users are:\n");
							displayUsers(userHeadp);
						}

						/*create new user*/
						else if(subchoice=='2')
						{
							int success = createNewUser(userHeadp, 2);
							if (success==1)
							{
								printf("You have successfully created"
									" a new user.\n");

								saveUserDatabase(userHeadp);
							}
							
						}

						/*create new admin user*/
						else if(subchoice=='3')
						{
							int success = createNewUser(userHeadp, 1);
							if (success==1)
							{
								printf("You have successfully created a "
									"new Admin.\n");
								saveUserDatabase(userHeadp);
							}
							
						}

						/*Modify another users details*/
						else if(subchoice=='4')
						{

							int success = confirmLogin(currentUserp);

							/*Allow admin to edit if correct details*/
							if (success==1)
							{
								clear();

								char name[MAX_USERNAME_SIZE];

								/*Admin selects user to edit*/
								printf("Current users are:\n");
								displayUsers(userHeadp);

								printf("\n\n");
								printf("Users in the database are listed" 
									"above.\nPlease enter the username of the" 
									"user you wish to modify. If you wish to" 
									"cancel, type 'CANCEL' (in capitals)\n");
								scanf("%s", name);

								/*Storage of user admin will edit*/
								tempUserp = getCurrentUser(name, userHeadp);

								/*Ensure that they are editting a valid user*/
								while((tempUserp==NULL||tempUserp->status==1)
									&& (strcmp(name, "CANCEL")!=0))
								{
									clear();
									
									printf("Current users are:\n");
									displayUsers(userHeadp);

									/*Error message for no user selected*/
									if(tempUserp==NULL)
									{
										printf("That username does not exist."
											"\n\nPlease enter a (non-admin) "
											"username from the options shown " 
											"above, or type 'CANCEL'\n");									
									}

									/*Error mesage for editting an admin*/
									else if(tempUserp->status==1)
									{
										printf("That is an admin.\n\n"
										"Please enter a (non-admin) username "
										"from the options shown above, "
										"or type 'CANCEL'\n");
									}
									scanf("%s", name);
									tempUserp = getCurrentUser(name, 
										userHeadp);
									printf("\n");
								}

								/*Allow editting (if cancel is not input)*/
								if((strcmp(name, "CANCEL")!=0))
								{
									/*Actually modify account. 
									Logout if account is deleted*/
									if(modifyAccount(userHeadp, tempUserp, 1)
										==1)
									{
										subchoice='5';
										strcpy(name, "CANCEL");
									}
								}
							}
							else
							{
								printf("Incorrect username or password\n");
								
								/*Prevent clear page*/
								subchoice='1';
							}
						}


						/*Return to menu*/


						/*allow previous output to be seen*/
						if(subchoice=='1'||subchoice=='2'||
							subchoice=='3')	
						{	
							printf("\n\n");
						}

						/*clear page*/
						else if(subchoice=='5'||subchoice=='4')
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

				/*modify/encrypt own files*/
				else if(choice=='3')
				{
					modifyFileDetails(currentUserp, fileHeadp);
				}

				/* modify/encrypt user files*/
				else if(choice=='4')
				{
					int success = confirmLogin(currentUserp);


					/*Allow admin to edit*/
					if (success==1)
					{
						clear();

						char name[MAX_USERNAME_SIZE];

						/*Admin seects user to edit*/
						printf("Current users are:\n");
						displayUsers(userHeadp);

						printf("\n\n");
						printf("Users in the database are listed above."
								"\nPlease enter the username of the user "
								"whose files you wish to edit."
								" If you wish to cancel"
								", type 'CANCEL' (in capitals)\n");
						scanf("%s", name);

						tempUserp = getCurrentUser(name, userHeadp);

						/*Ensure that they are editting a valid user*/
						while((tempUserp==NULL||tempUserp->status==1)
							&& (strcmp(name, "CANCEL")!=0))
						{
							clear();
							printf("Current users are:\n");
							displayUsers(userHeadp);

							/*Error message for no user selected*/
							if(tempUserp==NULL)
							{
								printf("That username does not exist.\n"
								"\nPlease enter a (non-admin) username "
								"from the options shown above, or type"
								" 'CANCEL'\n");									
							}
							/*Error mesage for editting an admin*/
							else if(tempUserp->status==1)
							{
								printf("That is an admin.\n\n"
								"Please enter a (non-admin) username "
								"from the options shown above, or type"
								" 'CANCEL'\n");
							}
							scanf("%s", name);
							tempUserp = getCurrentUser(name, userHeadp);
							printf("\n");
						}

						if((strcmp(name, "CANCEL")!=0))
						{
							clear();
							/*Actually modify files*/
							modifyFileDetails(tempUserp, fileHeadp);
						}
					}
					else
					{
						printf("Incorrect username or password\n");
						/*Prevent clear page, so above msg shown*/
						subchoice='1';
					}
					
					if(subchoice=='1'||subchoice=='2'||
						subchoice=='3')	
					{	
						printf("\n\n");
					}
					/*Return to menu*/
					else if(subchoice=='5'||subchoice=='4')
					{
						clear();
					}
					else
					{
						clear();
						printf("Please enter a valid choice\n");
					}
				}
				/*Logout*/
				else if(choice=='5')
				{
					; /*break the look*/
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
			while(choice!='3')
			{
				showMenu(status);
				scanf(" %c",&choice);

				/*Modify account*/
				if(choice=='1')
				{
					/*modify account, logout if account deleted*/
					if(modifyAccount(userHeadp, currentUserp, 0)==1)
					{
						choice='3';
					}
				}			
				/*encrypt/decrypt  files*/
				else if(choice=='2')
				{
					modifyFileDetails(currentUserp, fileHeadp);
				}

				/*Logout*/
				else if(choice=='3')
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
	}

	printf("error");
	return 1;	
} /*end main*/


/*****************************************************************************
User defined functions!!
*****************************************************************************/


/*****************************************************************************
Author: James
Name:getCurrentUser
Explanation: Returns the User_t which has a given name
input:
 - char* name - The name that we want to match for
 - User_t* userHeadp - The head of the user Linked List
output:
 - User_t* - the node of the linked list that has inputted name
*****************************************************************************/
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

/*****************************************************************************
Author: James
Name:copyUser
Explanation: Creates a new User_t node that contains the same data as an input
			node, however is not linked to any of the other nodes in the LL
input:
 - User_t* currentp - The node of the linked list that is being copied
output:
 - User_t* - a newcopy of the input node (without the data links)
*****************************************************************************/

User_t* copyUser(User_t* currentp)
{
	User_t* copyp = (User_t*) malloc(sizeof(User_t*));
	if(copyp==NULL)
	{
		printf("FATAL ERROR");
		return currentp;
	}

	strcpy(copyp->username, currentp->username);
	strcpy(copyp->password, currentp->password);
	copyp->status=currentp->status;
	copyp->nextp=NULL;

	return copyp;
}

/*****************************************************************************
Author: James
Name:checkUser
Explanation: Checks if there are users in the linked list
input:
 - User_t* userHeadp - The head of the user Linked List 
output:
 - User_t* - 0 if there are no users in the LL, or if status = 0 
 			(value set for identifying if empty.). 
 		   - 1 if there are valid users in the LL(valid users have status 1/2)
 		   - 2 if neither conditions are wrong (i.e. theres a bug) 
*****************************************************************************/
int checkUser(User_t* userHeadp)
{
	if((userHeadp -> status == 0)||(userHeadp->nextp==NULL))
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
/*****************************************************************************
Author: Jonatan
Name:clear
Explanation: clears the page on the terminal
input:
 - none
output:
 - none
*****************************************************************************/
void clear()
{
	/*Clears the page*/
	printf("\e[1;1H\e[2J");

}

/*****************************************************************************
Author: James
Name:saveUserDatabase
Explanation: saves the userp LL into the database and then encrypts the db.
input:
 - User_t* userp - the user head that will be saved into the database
output:
 - int - 1 if successful, 0 if unsuccessful
*****************************************************************************/

int saveUserDatabase(User_t* userp)
{
	User_t* currentp = userp;
	FILE *fp;

	fp = fopen(DB_FILE_NAME_USER, "w");

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

	/*Encrypt the database*/
	encryptDecrypt(DB_FILE_NAME_USER, "this_is_the_password");

	return 1;
	
}


/*****************************************************************************
Author: James
Name:readUserDatabase
Explanation: decrypts user db, saves it into LL, rencrypts the user db
input:
 - User_t* userp - the user head that the db will be saved into
output:
 - int - 1 if successful, 0 if unsuccessful
*****************************************************************************/

int readUserDatabase(User_t* userp)
{

	/*Decrypt the database*/
	encryptDecrypt(DB_FILE_NAME_USER, "this_is_the_password");


	User_t *currentp = userp;

	/*temp storage of status, test if file is empty*/
	int check;

	FILE *fp;
	fp = fopen(DB_FILE_NAME_USER, "r");

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

	/*Rencrypt the database*/
	encryptDecrypt(DB_FILE_NAME_USER, "this_is_the_password");


	return 1;
}

/*****************************************************************************
Author: James
Name:saveFileDatabase
Explanation: saves the filep LL into the database and then encrypts the db.
input:
 - File_t* filep - the file head of the LL that will be saved into the db
output:
 - int - 1 if successful, 0 if unsuccessful
*****************************************************************************/


int saveFileDatabase(File_t* filep)
{
	

	File_t* currentp = filep;
	FILE *fp;

	fp = fopen(DB_FILE_NAME_FILE, "w");

	/*Error checking code, to determine if file opened succesfully*/
	if (fp == NULL)
	{
		printf("Did not save database correctly\n");
		return 0;
	}
	
	while(currentp != NULL)
	{
		fprintf(fp, "%lf %s %s %s\n", 
			currentp->size,currentp->name, currentp->owner, currentp->type);
		currentp = currentp->nextp;
	}

	fprintf(fp, "-1");
	fclose(fp);

	/*Encrypt the database*/
	encryptDecrypt(DB_FILE_NAME_FILE, "this_is_the_password");


	return 1;
}


/*****************************************************************************
Author: James
Name:readFileDatabase
Explanation: decrypts the db, saves the db into LL and recrypts the db
input:
 - File_t* filep - the file head of the LL that the db will be saved into
output:
 - int - 1 if successful, 0 if unsuccessful
*****************************************************************************/


int readFileDatabase(File_t* filep)
{
	/*Decrypt the database*/
	encryptDecrypt(DB_FILE_NAME_FILE, "this_is_the_password");


	File_t *currentp = filep;

	/*temp storage of status, test if file is empty*/
	double check;

	FILE *fp;
	fp = fopen(DB_FILE_NAME_FILE, "r");

	if (fp ==NULL)
	{
		printf("read error\n");
		return 0;
	}

	fscanf(fp, "%lf %s %s %s\n", 
			&currentp->size, currentp->name, currentp->owner,currentp->type);


	fscanf(fp, "%lf", &check);

	/*If there are more filenames*/
	while(check!=-1)
	{
		currentp->nextp = (File_t*) malloc(sizeof(File_t));

		if (currentp->nextp == NULL)
		{
			printf("A memory error has occurred\n");
			return 0;
		}

		/*increment LL*/
		currentp=currentp->nextp;
		currentp->size = check;
		fscanf(fp, " %s %s %s\n", 
			currentp->name, currentp->owner, currentp->type);

		fscanf(fp, "%lf", &check);
	}


	currentp->nextp=NULL;
	fclose(fp);

	/*Encrypt the database*/
	encryptDecrypt(DB_FILE_NAME_FILE, "this_is_the_password");

	return 1;
}


/*****************************************************************************
Author: James
Name:confirmLogin
Explanation: prompts current user to reenter their login details
input:
 - User_t* currentUserp - The user that needs to reenter their login details
output:
 - int - returns 0 if unsuccessful, or the users status if successful.
*****************************************************************************/


int confirmLogin(User_t* currentUserp)
{
	char name[MAX_USERNAME_SIZE], 
		password[MAX_PASSWORD_SIZE];

	/*Confirm user identity*/
	printf("Please reenter your username:\n");
	scanf("%s", name);
	printf("Please reenter your password:\n");
	scanf(" %s", password);

	/*Tests if login matches current user*/
	return loginAuthentication(name, password, copyUser(currentUserp));
}









/*****************************************************************************
Author: James
Name:modifyAccount
Explanation: Allows the User_t* currentUserp's account to be modified. 
			Depending on the mode, either the user will modify their own
			account, or an admin will modify the account.
			Allows the username and password to be changed and the account to 
			be deleted
input:
 - User_t* userHeadp - The head of the user LL
 - User_t* currentUserp - The account of the user that is being modified
 - int mode - mode 0 is for modifying your own account
  			- mode 1 is for modifying other users account (for admin use only)
 output:
 - int - returns 1 if the user deletes their account, returns 0 otherwise
*****************************************************************************/


int modifyAccount(User_t* userHeadp, User_t* currentUserp, int mode)
{
	char subchoice='0';
	char letter;

	while(subchoice!='4')
	{
		/*get users choice*/
		printf(
		"Please choose an option:\n"
		"1 Change username\n"
		"2 Change password\n"
		"3 Delete account\n"
		"4 Return to menu\n"
		);
		scanf(" %c", &subchoice);
		clear();

		/*Change username*/
		if(subchoice=='1')
		{
			int success;

			/*Mode 0 is for modifying own acct, else is modify other accts*/

			if(mode==0)
			{
				success = confirmLogin(currentUserp);

			}

			else if(mode==1)
			{
				printf("Current username is: %s\n", currentUserp->username);
				printf("Are you sure you want to change the username?\n");
				printf("(Enter 'y' to confirm)\n");
				scanf(" %c",&letter);

				if(letter=='y')
				{
					success=1;
				}
				else
				{
					success=7;
				}
			}

			/*Alow username to be changed*/
			if((success==1)||(success==2))
			{
				int set;
				set = setUsername(currentUserp, userHeadp);
				
				if(set == 1){
					printf("New username is: %s\n",
						currentUserp->username);
					saveUserDatabase(userHeadp);
				}	
			}
			/*Do nothing for mode 1 if user cancels*/
			else if(success==7)
			{
				;
			}
			/*mode 0 error message*/
			else
			{
				printf("Incorrect username or password\n");
			}
		}
		/*Change password*/
		else if(subchoice=='2')
		{

			int success;
			if(mode==0)
			{
				success = confirmLogin(currentUserp);

			}

			else if(mode==1)
			{
				printf("Current password of user '%s' is: %s\n",
					currentUserp->username, currentUserp->password);
				printf("Are you sure you want to change the password?\n");
				printf("(Enter 'y' to confirm)\n");
				scanf(" %c",&letter);

				if(letter=='y')
				{
					success=1;
				}
				else
				{
					success=7;
				}
			}

			if((success==1)||(success==2))
			{
				setPassword(currentUserp);
				printf("New password is: %s\n",
					currentUserp->password);
				saveUserDatabase(userHeadp);
			}
			else if(success==7)
			{
				;
			}
			else
			{
				printf("Incorrect username or password\n");
			}
		}
		/*DELETE account */
		else if(subchoice=='3')
		{
			int success;
			char name[MAX_USERNAME_SIZE];

			if (mode==0)
			{
				success = confirmLogin(currentUserp);
				if(success==1)
				{
					printf("Are you sure you want to delete your account?\n");
					printf("(Enter 'y' to confirm)\n");
					scanf(" %c",&letter);

					if(letter=='y')
					{
						success=1;
					}
					else
					{
						success=7;
					}
				}

			}
			else if (mode==1)
			{
				printf("Are you sure you want to delete the user '%s'?\n",
					currentUserp->username);
				strcpy(name,currentUserp->username);
				printf("(Enter 'y' to confirm)\n");
				scanf(" %c",&letter);

				if(letter=='y')
				{
					success=1;
				}
				else
				{
					success=7;
				}
			}

			if((success==1)||(success==2))
			{

				deleteUser(userHeadp, name);

				saveUserDatabase(userHeadp);
				return 1;
			}

			else if(success==7)
			{
				subchoice=4;
	
			}

			else
			{
				printf("Incorrect username or password\n");
			}

		}

		if(subchoice=='1'||subchoice=='2')	
		{	
			printf("\n\n");
		}

		/*Return to menu*/
		else if(subchoice=='4')
		{
			clear();
			return 0;
		}

		else
		{
			clear();
			printf("Please enter a valid choice\n");
		}
	}

	return 0;
}

/*****************************************************************************
Author: James
Title: modifyFileDetails
Explanation: Allows the User_t* currentUserp's account to be modified. Allows 
				files to be added, deleted, viewed, encrypted, compressed, 
				decrypted, decompressed. 
input:
 - User_t* currentUserp - The owner of the files being modified
 - File_t* fileHeadp - The head of the file LL
output:
 - none
*****************************************************************************/

void modifyFileDetails(User_t* currentUserp, File_t* fileHeadp)
{
	char subchoice='0';

	while(subchoice!='8')
	{
		printf(
			"What would you like to do "
			"(enter a number)?\n"
			"1 View all files\n"
			"2 Add file\n"
			"3 Delete file\n"
			"4 Encrypt file\n"
			"5 Decrypt file\n"
			"6 Compress file\n"
			"7 Decompress file\n"
			"8 Return to menu\n");
		scanf(" %c", &subchoice);
		clear();


		/*Display files*/
		if(subchoice=='1')
		{


			displayFiles(fileHeadp, currentUserp->username);
		}

		else if(subchoice=='2')
		{
			char name[MAX_FILENAME_SIZE], 
				type[MAX_FILETYPE_SIZE];
			int success;

			printf("What is the file name:\n");
			scanf("%s", name);
			printf("What is the file type\n");
			scanf("%s", type);
			

			success = addFile(fileHeadp, currentUserp->username, name, type);

			if(success==1)
			{
				printf("Successfully added file\n");
				saveFileDatabase(fileHeadp);
			}
			else if (success==0)
			{
				printf("Failed to add File. File may "
					"already be added, or file may be "
					"owned by another user\n");
			}
			else if(success==2)
			{
				printf("Please add file to the directory, and"
					" check name is correct");
			}
		}
		else if(subchoice=='3')
		{
			char name[MAX_FILENAME_SIZE];
			char name1[MAX_FILENAME_SIZE];


			printf("Current files are listed below:\n");
			displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("what is the name of the file you want to delete?\n");
			scanf("%s", name);
			strcpy(name1, name);

			int success = deleteFile(fileHeadp, name1,currentUserp->username); 

			if (success==1)
			{
				printf("You have successfully deleted "
					"your file.\n");
				saveFileDatabase(fileHeadp);
			}
			else
			{
				printf("File Deletion failed. Ensure you"
					" entered the correct name.\n");
			}
		}
		/*Encrypt*/
		else if(subchoice=='4')
		{

			int encrypt_status = 0;
			char name[MAX_FILENAME_SIZE];


			printf("Current files are listed below:\n");
						displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("What file do you want to encrypt?\n");
			scanf("%s", name);



			encrypt_status = encryptDecrypt(name, currentUserp->password);

			clear();

			if(encrypt_status > 0 ){
				printf("successful encryption\n");
			}else{
				printf("unsuccessful encryption\n");
			}

		}

		/*Decrypt*/
		else if(subchoice=='5')
		{
			
			int decrypt_status = 0;
			char name[MAX_FILENAME_SIZE];


	
			printf("Current files are listed below:\n");
			displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("What file do you want to decrypt?\n");
			scanf("%s", name);




			decrypt_status = encryptDecrypt(name, currentUserp->password);

			clear();

			if(decrypt_status > 0 ){
				printf("successful decryption\n");
			}else{
				printf("unsuccessful decryption\n");
			}
		}
		

		else if(subchoice=='6')
		{
			File_t * filep;
			char filename[MAX_FILENAME_SIZE];
			char compressName[MAX_FILENAME_SIZE];
			char type[MAX_FILETYPE_SIZE];
			int check;
			node_t *treep;
			int binaryTable1[27], binaryTable2[27];    
			
			buildTree(&treep);
			fill(binaryTable1, treep, 0);
			invertCode(binaryTable1,binaryTable2);
			
			strcpy(compressName, "compressed.txt");
			strcpy(type, "compressed");			
			printf("Please enter the name of the file you want to compress ");
			scanf("%s", filename);
			
			filep = searchFilename(fileHeadp,filename,currentUserp->username);

			if(filep == NULL){
				printf("Error, File not found!");
			}
			else{
				addFile(fileHeadp, currentUserp -> username, 
					compressName, type);
				check = compressHuffman(filename, binaryTable2);
				
				if(check == 1){
					printf("You have successfully compressed the file.");
				}
				else{
					printf("Error. Failed to compress the file.");
				}
			}
			
		}

		else if(subchoice=='7')
		{
			File_t * filep;
			char filename[MAX_FILENAME_SIZE];
			char decompressName[MAX_FILENAME_SIZE];
			char type[MAX_FILETYPE_SIZE];
			int check;
			node_t *treep; 
			
			buildTree(&treep);
			
			strcpy(decompressName, "decompressed.txt");
			strcpy(type, "decompressed");
			printf("Please enter the name of the file you "
				"want to decompress: ");
			scanf("%s", filename);
			
			filep = searchFilename(fileHeadp, filename, 
						currentUserp->username);

			if(filep == NULL){
				printf("Error, File not found!");
			}
			else{
				addFile(fileHeadp, currentUserp->username, 
					decompressName, type);
				check = decompressHuffman(filename, treep);
				
				if(check == 1){
					printf("You have successfully decompressed the file.");
				}
				else{
					printf("Error. Failed to decompress the file.");
				}
			}
		}
		/*else if()*/
		if(subchoice=='1'||subchoice=='2'||subchoice=='3'||
			subchoice=='4'||subchoice=='5'||subchoice=='6'||
			subchoice=='7')	
		{
			printf("\n\n");
		}
		/*Exit the loop*/
		else if(subchoice=='8')
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




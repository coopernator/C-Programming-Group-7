/*
WORKING
	Can login
	add new users
	modify your own data
	User info is preserved 

NOT WORKING/BUGS/TO DO
 
I think we should change it so files is a LL, with a property of 'user'

encryption
compression
delete your own account
sort and search
database to store file information so it is preserved across logins
check if file is in the directory before allowing you to add it to the program
view user function 
	Just need to display the status. 

JOBS for people to do
Hai			print file list			
James		check if the file is in the directory(if you can't 
			open not in directory)

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
#include "file.h"
#include "helper.h"


#define DB_FILE_NAME_USER "DB_user"
#define DB_FILE_NAME_FILE "DB_file"



/*****************************************************************************
Main function
*****************************************************************************/
int main()
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

	/*Used for checkUser function, as status should never be 0 normally */
	userHeadp -> status = 0;

	/*Copy userdatabase (if it exists) into the userHeadp LL*/
	readUserDatabase(userHeadp);

	/*Copy filedatabase into fileHeadp LL*/
	readFileDatabase(fileHeadp);


	/*see if there are any users in program(check results of readUserDatabase*/
	int check = checkUser(userHeadp);

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
		strcpy(fileHeadp ->name,"PLACEHOLDERRRR");
		strcpy(fileHeadp ->type, "PLACEHOLDERRRR");
		strcpy(fileHeadp ->owner,"PLACEHOLDERRRR");
		fileHeadp ->size=0;
		fileHeadp ->nextp = NULL;


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
			/*Temporary storage of name and password*/
			char name[MAX_USERNAME_SIZE], password[MAX_PASSWORD_SIZE];

			printf("LOGIN\n"
			"Please enter your Username and password. If you don't have\n"
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
				saveFileDatabase(fileHeadp);

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
			while(choice!='5')
			{
				subchoice='0';
				showMenu(status);
				scanf(" %c",&choice);
				clear();

				/*Modify own account*/
				if(choice=='1')
				{

					modifyAccount(userHeadp, currentUserp, 0);
					
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
							else
							{
								printf("ERROR");
							}
						}

						/*create new admin*/
						else if(subchoice=='3')
						{
							int success = createNewUser(userHeadp, 1);
							if (success==1)
							{
								printf("You have successfully created a "
									"new Admin.\n");
								saveUserDatabase(userHeadp);
							}
							else
							{
								printf("ERROR");
							}
						}

						/*Modify another users details*/
						else if(subchoice=='4')
						{

							char name[MAX_USERNAME_SIZE], 
								password[MAX_PASSWORD_SIZE];

							/*Confirm Admin user identity*/
							printf("Please reenter your username:\n");
							scanf("%s", name);
							printf("Please reenter your password:\n");
							scanf("%s", password);

							int success = loginAuthentication(name, password, 
								copyUser(currentUserp));

							/*Allow admin to edit*/
							if (success==1)
							{
								clear();

								/*Admin seects user to edit*/
								printf("Current users are:\n");
								displayUsers(userHeadp);

								printf("\n\n");
								printf("Users in the database are listed above."
									"\nPlease the username of the user you wish"
									" to modify. If you wish to cancel, type"
									" 'CANCEL' (in capitals)\n");
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
									/*Actually modify account*/
									modifyAccount(userHeadp, tempUserp, 1);
								}

							}


							else
							{
								printf("incorrect username or password\n");

								/*Prevent clear page, so above msg shown*/
								subchoice='1';
							}


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
				}

				/*modify/encrypt own files*/
				else if(choice=='3')
				{
					modifyFileDetails(currentUserp, fileHeadp);

				}
				/* VERY VERY VERY WIP encrypt/decrypt user files*/
				else if(choice=='4')
				{
					printf("What would you like to do? (enter a number)"
						"WIP1 ..."
						"WIP2 ..."
						"WIP3 ..."
						);
					scanf(" %c", &subchoice);
					clear();

					/*
					while()
					{
						....

						if(subchoice=='1'||subchoice=='2'||subchoice=='3'||
							subchoice=='4'||subchoice=='5'|| ......)	
						{
							printf("\n\n");
						}
						/ *Exit the loop* /
						else if(subchoice=='9')
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
				else if(choice=='5')
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
			while(choice!='3')
			{
				showMenu(status);
				scanf(" %c",&choice);

				/*Modify account*/
				if(choice=='1')
				{
					modifyAccount(userHeadp, currentUserp,0);


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
		/*public user*/
		else if(status==3)
		{
			while(choice!='2')
			{
				showMenu(status);
				scanf(" %c", &choice);
			
				/*compress files*/
				if(choice=='1')
				{

				}
				/*Logout*/
				else if(choice=='2')
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


	printf("error");
	return 1;


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






/*******************************************************************************
User defined functions!!

*******************************************************************************/



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

void clear()
{
	/*Clears the page*/
	printf("\e[1;1H\e[2J");

}



/*
appears to produce error i.e. fp not defined even though it is */
int saveUserDatabase(User_t* userp)
{
	User_t* currentp = userp;
	FILE *fp;

	fp = fopen(DB_FILE_NAME_USER, "w");

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

	return 1;
}



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

	return 1;
	
}


int readFileDatabase(File_t* filep)
{

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

	return 1;
}




/*******************************************************************************

*******************************************************************************/

void modifyAccount(User_t* userHeadp, User_t* currentUserp, int mode)
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
		"WIP3 Delete account\n"
		"4 Return to menu\n"
		);
		scanf(" %c", &subchoice);
		clear();

		/*Change username*/
		if(subchoice=='1')
		{
			int success;
			char name[MAX_USERNAME_SIZE], 
			password[MAX_PASSWORD_SIZE];

			/*Mode 0 is for modifying own acct, else is modifying other accts*/


			if(mode==0)
			{
				/*Confirm user identity*/
				printf("Please reenter your username:\n");
				scanf("%s", name);
				printf("Please reenter your password:\n");
				scanf("%s", password);

				success = loginAuthentication(name, password, 
					copyUser(currentUserp));
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
				setUsername(currentUserp);
				printf("New username is: %s\n",
					currentUserp->username);
				saveUserDatabase(userHeadp);
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
			char name[MAX_USERNAME_SIZE], 
				password[MAX_PASSWORD_SIZE];

			if(mode==0)
			{
				printf("Please reenter your username:\n");
				scanf("%s", name);
				printf("Please reenter your password:\n");
				scanf("%s", password);

				success = loginAuthentication(name, password, 
				copyUser(currentUserp));

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

		/*DELETE account WIP*/
		else if(subchoice=='3')
		{

			int success;
			char name[MAX_USERNAME_SIZE], 
				password[MAX_PASSWORD_SIZE];			

			if (mode==0)
			{
				printf("Please reenter your username:\n");
				scanf("%s", name);
				printf("Please reenter your password:\n");
				scanf("%s", password);

				success = loginAuthentication(name, password, 
				copyUser(currentUserp));
			}

			else if (mode==0)
			{
				printf("Are you sure you want to delete the user '%s'?\n",
					currentUserp->username);
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



				/*dlete user function goes here*/



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

		if(subchoice=='1'||subchoice=='2'||subchoice=='3')	
		{	
			printf("\n\n");
		}



		/*Return to menu*/
		else if(subchoice=='4')
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

/*******************************************************************************

*******************************************************************************/

void modifyFileDetails(User_t* currentUserp, File_t* fileHeadp)
{
	char subchoice='0';

	while(subchoice!='9')
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
		scanf(" %c", &subchoice);
		clear();


		/*Display files*/
		if(subchoice=='1')
		{

			printf("%-20.20s %-20.20s %-10.10s %.4s\n", 
				"Owner", "Name", "Type", "Size");

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
			else
			{
				printf("Failed to add File. File may "
					"already be added, or file may be "
					"owned by another user\n");
			}
		}
		else if(subchoice=='3')
		{
			char name[MAX_FILENAME_SIZE];
			char name1[MAX_FILENAME_SIZE];


			printf("Current files are listed below:\n");
			printf("%-20.20s %-20.20s %-10.10s %.4s\n", 
				"Owner", "Name", "Type", "Size");
			displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("what is the name of the file you want to delete?\n");
			scanf("%s", name);
			strcpy(name1, name);

			int success = deleteFile(fileHeadp, name1, currentUserp->username); /*temporarily added owner*/

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
			/*char filename[MAX_FILENAME_SIZE];
			strcpy(filename, "a");

			char password[MAX_PASSWORD_SIZE];
			strcpy(password, "test");


			encryptDecrypt(filename, password);*/

			int encrypt_status = 0;
			char name[MAX_FILENAME_SIZE];


			printf("Current files are listed below:\n");
			printf("%-20.20s %-20.20s %-10.10s %.4s\n", 
				"Owner", "Name", "Type", "Size");
			displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("What file do you want to encrypt?\n");
			scanf("%s", name);



			encrypt_status = encryptDecrypt(name, "this_is_the_password");

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
			/*char filename[MAX_FILENAME_SIZE];
			strcpy(filename, "a");

			char password[MAX_PASSWORD_SIZE];
			strcpy(password, "test");*/
			int decrypt_status = 0;
			char name[MAX_FILENAME_SIZE];


	
			printf("Current files are listed below:\n");
			printf("%-20.20s %-20.20s %-10.10s %.4s\n", 
				"Owner", "Name", "Type", "Size");
			displayFiles(fileHeadp, currentUserp->username);
			printf("\n\n");

			printf("What file do you want to decrypt?\n");
			scanf("%s", name);




			decrypt_status = encryptDecrypt(name, "this_is_the_password");

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
			printf("Please enter the name of the file you want to compress: ");
			scanf("%s", filename);
			
			filep = searchFilename(fileHeadp, filename, currentUserp->username);

			if(filep == NULL){
				printf("ERROR, FILE NOT FOUND!!!");
			}
			else{
				addFile(fileHeadp, currentUserp->username, compressName, type);
				check = compressHuffman(filename, binaryTable2);
				
				if(check == 1){
					printf("YOU HAVE SUCCESSFULLY COMPRESSED THE FILE.");
				}
				else{
					printf("ERROR, UNSUCCESSFULLY COMPRESSED FILE.");
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
			printf("Please enter the name of the file you want to decompress: ");
			scanf("%s", filename);
			
			filep = searchFilename(fileHeadp, filename, currentUserp->username);

			if(filep == NULL){
				printf("ERROR, FILE NOT FOUND!!!");
			}
			else{
				addFile(fileHeadp, currentUserp->username, decompressName, type);
				check = decompressHuffman(filename, treep);
				
				if(check == 1){
					printf("YOU HAVE SUCCESSFULLY DECOMPRESSED THE FILE.");
				}
				else{
					printf("ERROR, UNSUCCESSFULLY DECOMPRESSED FILE.");
				}
			}

		}


		/*else if()*/
		if(subchoice=='1'||subchoice=='2'||subchoice=='3'||
			subchoice=='4'||subchoice=='5'||subchoice=='6'||
			subchoice=='7'||subchoice=='8')	
		{
			printf("\n\n");
		}
		/*Exit the loop*/
		else if(subchoice=='9')
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


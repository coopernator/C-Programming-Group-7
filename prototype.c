/*

Jonatan Cooper, Hoang Nguyen, Duc Huy Nguyen, James Singer, Hai Trinh

*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct fileDetail
{
	char* name;
	char* type;		/*encryption status*/
	double size;
	fileDetail_t* nextp;
};
typedef struct fileDetail fileDetail_t;


struct user
{	
	char* username;
	char* password;
	char* status;
	user_t* nextp;

};
typedef struct user user_t;

/*add different levels of users i.e. admin, user guest
  admin has access to everything, 
  user only access to their files, guest can use it as a regular file manager*/

/*****************************************************************************
general
*****************************************************************************/

/*
	Author: Jonatan
	this function displays the main menu that would be used to minipulate the 
	files
	Inputs: none
	Outputs:none
*/
void showMenu();

/*
	Author: Jonatan
	this function adds a file to a stack/queue/list (undecided) for 
	either encryption, decryption, compression or decompression
	Inputs: a file pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
//int addtoStack(File_t* filep);

/*
	Author: Jonatan
	this function removes a file from the stack/queue/list (undecided)
	that would be used encrypt, decrypt, compress or decompression
	Inputs: a file pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
//int removeFromStack(File_t* filep);

/*****************************************************************************
user login
*****************************************************************************/

/*
	Author: Hoang
	this function displays the login menu for a user
	Inputs: none
	Outputs: none
*/
void showLoginMenu();

/*
	Author: Hoang
	this function returns a 0 if login is incorrect,
	a 1 if the user is an admin, and 2 if the user is a normal user,
	inputs: login, password
	outputs: integer to determine status.
*/
int loginAuthentication(char* username, char* password);



/*
	author Duc Hoy
	change your own username and or password
*/
void modifyUser(user_t* user);

/*
	show all (nonadmin) users and their passwords
*/
void showAllUsers(user_t* user);

/*


*/
void showAllFiles(fileDetail_t* fileDetail);

/*
	Author: Hoang
	this function retrieves a username from the user
	Inputs: User pointer
	Outputs:none
*/
// void getUsername(User_t* userp);

/*
	Author Hoang
	this function retrieves a password from the user
	Inputs: User pointer
	Outputs: none
*/
// void getPassword(User_t* userp);

/*
	Author: Duc Huy
	this function allows the user to set a password
	Inputs: user pointer, password pointer
	Outputs: none
*/
// void setPassword(User_t* userp, char* passwordp);

/*
	Author: Duc Huy
	this function allows the user to set a username
	Inputs: user pointer, username pointer
	Outputs: none
*/
// void setUsername(User_t* userp, char* usernamep);

/*
	Author: Duc Huy
	this function creates a new user, admin can only create a new user
	Inputs: username and password pointers
	Outputs: 1 if successful, 0 if unsuccessful
*/
void createNewUser(char* usernamep, char* passwordp);

/*****************************************************************************
file information retrieval
*****************************************************************************/

/*	
	author: Hai
	Add file to a linked list
	int to determine whether it is successful or not
*/
int addFile(char* fileName);


// /*
// 	Author: Duc Huy
// 	get selected file name
// 	Inputs: file struct
// 	Outputs: character pointer
// */
// char* getFileName(File_t file);

// /*
// 	Author: James
// 	get the location of a file
// 	Inputs: file struct
// 	Outputs:character pointer
// */
// char* getFileLocation(File_t file);

// /*
// 	Author: James
// 	this function retrieves a user name from the user
// 	Inputs: file struct
// 	Outputs:character pointer
// */
// int makeDirectory();

// /*
// 	Author: James 
// 	this function returns the size of a file
// 	Inputs: file struct
// 	Outputs: the size of the file
// */
// double getFileSize(File_t file);


// 	Author: James
// 	returns date properties of a file
// 	Inputs: file struct
// 	Outputs: date struct

// date_t getDate(File_t file);


// 	Author: Hai
// 	returns the file type of a specific file
// 	Inputs: file pointer
// 	Outputs: character pointer

// char* getFileType(File_t file);

/*
	Author: Hai
	allows for a file to be renamed
	Inputs: file structure
	Outputs: 1 if successful, 0 if unsuccessful
*/
int setFileName(File_t file);

/*
	Author: Hai
	allows for a file to be deleted
	Inputs: file structure
	Outputs: 1 if successful, 0 if unsuccessful
*/
int deleteFile(File_t file);

// /*
// 	Author: Hai
// 	allows for a folder to be deleted
// 	Inputs: char pointer
// 	Outputs: 1 if successful, 0 if unsuccessful
// */
// int deleteDirectory(char* namep);

// /*****************************************************************************
// sorting
// *****************************************************************************/

// /*
// 	Author: TBD
// 	allows the current view to be sorted by a specific metric
// 	Inputs: the file directory, the metric to sort by (size, file type)
// 	Outputs: 1 if successful, 0 if unsuccessful
// */
// void sort(char* directory, int sort_type);

// //searching

// /*
// 	Author: TBD
// 	this function allows the user to search a directory for a certain 
// 	file based on the name entered
// 	Inputs: the file directory, the name of the file
// 	Outputs: none
// */
// void searchName(char* name, char* directory);

// /*
// 	Author: TBD
// 	this function allows the user to search a directory for a certain 
// 	file based on the date entered
// 	Inputs: the file directory, the date of the file
// 	Outputs: none
// */
// void searchDate(Date date, int directory);


// 	Author: TBD
// 	this function allows the user to search a directory for a certain 
// 	file based on the date entered
// 	Inputs: the file directory, the date of the file
// 	Outputs: none

// void searchType(char* type, int directory);

// /*****************************************************************************
// Encryption & decryption
// *****************************************************************************/

// /*
// 	Author: TBD
// 	this function encrypts a file
// 	Inputs: File_t pointer
// 	Outputs: 1 if successful, 0 if unsuccessful
// */
// int encrypt(File_t* file);

// /*
// 	Author: TBD
// 	this function decrypts a file
// 	Inputs: File_t pointer
// 	Outputs:1 if successful, 0 if unsuccessful
// */
// int decrypt(File_t* file);

// /*****************************************************************************
// Compression and decompression
// *****************************************************************************/

// /*
// 	Author: TBD
// 	this function compresses a file
// 	Inputs: File_t pointer
// 	Outputs: 1 if successful, 0 if unsuccessful
// */
// int compress(File_t* file);

// /*
// 	Author: TBD
// 	this function decompresses a file
// 	Inputs: File_t pointer
// 	Outputs: 1 if successful, 0 if unsuccessful
// */
// int decompress(File_t* file);

/*****************************************************************************
Main Function
*****************************************************************************
/int main(void){
	
	return 0;
}

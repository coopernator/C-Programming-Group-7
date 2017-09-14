#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct File
{
	char* name;
	char* type;
	double size;
	date_t date;
	File_t* nextp;
};
typedef struct File File_t;

struct date
{
	int day;
	int month;
	int year;
};
typedef struct date date_t;

struct User
{	
	char* username;
	char* password;
	char* status;
};
typedef struct User User_t;

//add different levels of users i.e. admin, user guest
//admin has access to everything, 
//user only access to their files, guest can use it as a regular file manager

/*****************************************************************************
general
*****************************************************************************/

/*
	this function displays the main menu that would be used to minipulate the 
	files
	Inputs: none
	Outputs:none
*/
void showMenu();

/*
	this function adds a file to a stack/queue/list (undecided) for 
	either encryption, decryption, compression or decompression
	Inputs: a file pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int addtoStack(File_t* filep);

/*
	this function removes a file from the stack/queue/list (undecided)
	that would be used encrypt, decrypt, compress or decompression
	Inputs: a file pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int removeFromStack(File_t* filep);

/*****************************************************************************
user login
*****************************************************************************/

/*
	this function displays the login menu for a user
	Inputs: none
	Outputs: none
*/
void showLoginMenu();

/*
	this function verifies the credentials of a user
	Inputs: the username and the password
	Outputs: 1 if successful, 0 if unsuccessful
*/
int login(char* username, char* password);

/*
	this function retrieves a username from the user
	Inputs: User pointer
	Outputs:none
*/
void getUsername(User_t* userp);

/*
	this function retrieves a password from the user
	Inputs: User pointer
	Outputs: none
*/
void getPassword(User_t* userp);

/*
	this function allows the user to set a password
	Inputs: user pointer, password pointer
	Outputs: none
*/
void setPassword(User_t* userp, char* passwordp);

/*
	this function allows the user to set a username
	Inputs: user pointer, username pointer
	Outputs: none
*/
void setUsername(User_t* userp, char* usernamep);

/*
	this function creates a new user
	Inputs: username and password pointers
	Outputs: 1 if successful, 0 if unsuccessful
*/
void createNewUser(char* usernamep, char* passwordp);

/*****************************************************************************
file information retrieval
*****************************************************************************/

/*
	get selected file name
	Inputs: file struct
	Outputs: character pointer
*/
char* getFileName(File_t file);

/*
	get the location of a file
	Inputs: file struct
	Outputs:character pointer
*/
char* getFileLocation(File_t file);

/*
	this function retrieves a user name from the user
	Inputs: file struct
	Outputs:character pointer
*/
int makeDirectory();

/*
	this function returns the size of a file
	Inputs: file struct
	Outputs: the size of the file
*/
double getFileSize(File_t file);

/*
	returns date properties of a file
	Inputs: file struct
	Outputs: date struct
*/
date_t getDate(File_t file);

/*
	returns the file type of a specific file
	Inputs: file pointer
	Outputs: character pointer
*/
char* getFileType(File_t file);

/*
	allows for a file to be renamed
	Inputs: file structure
	Outputs: 1 if successful, 0 if unsuccessful
*/
int setFileName(File_t file);

/*
	allows for a file to be deleted
	Inputs: file structure
	Outputs: 1 if successful, 0 if unsuccessful
*/
int deleteFile(File_t file);

/*
	allows for a folder to be deleted
	Inputs: char pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int deleteDirectory(char* namep);

/*****************************************************************************
sorting
*****************************************************************************/

/*
	allows the current view to be sorted by a specific metric
	Inputs: the file directory, the metric to sort by (size, file type)
	Outputs: 1 if successful, 0 if unsuccessful
*/
void sort(char* directory, int sort_type);

//searching

/*
	this function allows the user to search a directory for a certain 
	file based on the name entered
	Inputs: the file directory, the name of the file
	Outputs: none
*/
void searchName(char* name, char* directory);

/*
	this function allows the user to search a directory for a certain 
	file based on the date entered
	Inputs: the file directory, the date of the file
	Outputs: none
*/
void searchDate(Date date, int directory);

/*
	this function allows the user to search a directory for a certain 
	file based on the date entered
	Inputs: the file directory, the date of the file
	Outputs: none
*/
void searchType(char* type, int directory);

/*****************************************************************************
Encryption & decryption
*****************************************************************************/

/*
	this function encrypts a file
	Inputs: File_t pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int encrypt(File_t* file);

/*
	this function decrypts a file
	Inputs: File_t pointer
	Outputs:1 if successful, 0 if unsuccessful
*/
int decrypt(File_t* file);

/*****************************************************************************
Compression and decompression
*****************************************************************************/

/*
	this function compresses a file
	Inputs: File_t pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int compress(File_t* file);

/*
	this function decompresses a file
	Inputs: File_t pointer
	Outputs: 1 if successful, 0 if unsuccessful
*/
int decompress(File_t* file);

/*****************************************************************************
Main Function
*****************************************************************************
/int main(void){
	
	return 0;
}

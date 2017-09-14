#include <stdio.h>

struct File
{
	char* name;
	char* type;
	double size;
	date_t date;
	file_t* nextp;
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

//general
void showMenu();
void addtoStack(Item item);
void removeFromStack(Item item);

//user login
void showLoginMenu();
int login(char* username, char* password);
void getUsername(User_t user);
void getPassword(User_t user);
void setPassword(User_t user, char* password);
void setUsername(User_t user, char* username);
void createNewUser(char* username, char* password);

//File information
void getFileName(file_t file);
void getFileLocation(file_t file);
void makeDirectory();
void getFileSize(file_t file);
void getDate(file_t file);
void getFileType(file_t file);
void setFileName(file_t file);
void deleteFile(file_t file);
void deleteDirectory(char* name);

//Sorting
void sort(int directory, int sort_type);

//searching
void searchName(char* name, int directory);
void searchDate(Date date, int directory);
void searchType(char* type, int directory);

//Encryption & decryption
double encrypt(file_t file);
void decrypt(file_t file);

//compression & decompression
void compress(file_t file);
void decompress(file_t file);


int main(void){
	
	return 0;
}

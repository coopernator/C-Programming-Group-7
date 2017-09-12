#include <stdio.h>

int main(void){
	
	return 0;
}

struct File
{
	char* name;
	char* type;
	double size;
	date_t date;
	file_t* nextp;

};

struct date
{
	int day;
	int month;
	int year;
};

struct User
{	
	username;
	password;
	char* status;
};
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
void getUsername();
void getPassword();
void setPassword(char* password);
void setUsername(char* username);
void createNewUser(char* username, char* password);

//File information
void getFileName();
void getFileLocation();
void makeDirectory();
void getFileSize();
void getDate();
void getFileType();
void setFileName();
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
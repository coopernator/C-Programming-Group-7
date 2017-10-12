#ifndef HELPER
#define HELPER
#include "user.h"
/*jonatan*/
void showMenu(int userType);

/*from monday 25/09/2017*/

/*james*/
void clear(void);

/*jonatan*/
int encryptDecrypt(char* filename,  char* password);

/*jonatan*/
int handleParsing(int argc, char* argv[], User_t* fileHeadp);

/*jonatan*/
void help();

/*jonatan*/
int contains(int argc, char* argv[], char* short_arg, char* long_arg);

/*jonatan*/
void getValue(int argc, char* argv[], char* short_arg1, 
	char* long_arg1, char* value[]);


#endif
#ifndef USER
#define USER

#define USERNAME_SIZE 10
#define PASS_SIZE 10
#define NAME_SIZE 10
#define MAX_USERNAME_SIZE 21
#define MAX_PASSWORD_SIZE 16
#define MAX_STATUS_SIZE 6

struct User
{	
	char username[MAX_USERNAME_SIZE];
	char password[MAX_PASSWORD_SIZE];
	int status;
	struct User* nextp;
};
typedef struct User User_t;

/*james*/
void modifyAccount(User_t* userHeadp, User_t* currentUserp, int mode);

/*huy*/
void setPassword(User_t *userp);
/*huy*/

/*james*/
int saveUserDatabase(User_t* userp);

void setUsername(User_t *userp);
/*huy*/
int createNewUser(User_t *userlistp, int status);

/*from monday 25/09/2017*/

/*james*/
User_t* getCurrentUser(char* name, User_t* userHeadp);

/*james*/
int readUserDatabase(User_t* userp);

/*james*/
int checkUser(User_t* userHeadp);

/*hoang*/
char *getUsername(User_t* userp);

/*hoang this function appears to be missing or not needed*/
/*char *getUsername(User_t* userp);*/

/*hoang*/
int loginAuthentication(char name[], char pass[], User_t* headp);

/**********************************************************
checkDuplicateUser- Hai
-This function checks if there is any duplicate user
(have the same name) in the provided linkedlist
-Inputs: 
	+ *headUserp: pointer to the head user of the linked list
	+ name[]: the name we use to look for duplicates
-Outputs:
	+ check: 1 if there is a duplicate, 0 otherwise
***********************************************************/
int checkDuplicateUser(User_t *headUser, char name[]); /*worked*/

/**********************************************************
displayUsers - Hai
-This function prints all users in a user linked list 
(could be admin or user linked list)
-Inputs: 
	+ *headUserp: pointer to the head user of the linked list
-Outputs:
	+ none
***********************************************************/
void displayUsers(User_t *headUserp); /*worked*/


/*James*/
User_t* copyUser(User_t* currentp);

/*Hoang*/
int deleteUser(User_t *userheadp, char name[]);
User_t *searchUser(User_t* userheadp, char name[]);



#endif
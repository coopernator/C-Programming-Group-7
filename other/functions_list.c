date_t getDate(File_t *filep);
char *getFileType(File_t *filep);
int setFileName(File_t *filep, File_t *headFilep);
File_t *searchFilename(File_t* head, char name[]);
int addFile(File_t* fileHead, char name[], char type[], date_t date); /*worked*/
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
int checkUser(User_t* userHeadp);
char *getUsername(User_t* userp);
User_t* getCurrentUser(char* name, User_t* userHeadp);
void clear(void);
int saveUserDatabase(User_t* userp);
int readUserDatabase(User_t* userp);

char *getFileName(File_t *filep);
int setFileName(File_t *filep, File_t *fileheadp, char owner[]);
File_t *searchFilename(File_t* head, char name[], char owner[]);
User_t *searchUsername(User_t* head, char name[]);
int addFile(File_t* filehead, char owner[],char name[], char type[]);
int deleteFile(File_t *filehead, char name[], char owner[]);
void displayUsers(User_t *headUserp); 
void displayFiles(File_t *filehead, char owner[]); 
int checkDuplicateUser(User_t *headUser, char name[]); 
int checkDuplicateFile(File_t *headFile, char name[], char owner[]); 

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

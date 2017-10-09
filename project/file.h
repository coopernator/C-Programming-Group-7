#ifndef FILE_HEADER
#define FILE_HEADER

#define MAX_FILENAME_SIZE 21
#define MAX_FILETYPE_SIZE 21
#define MAX_OWNER_SIZE 21
#define len(x) ((int)log10(x)+1)
#define frequencyArrLen 27
#include "user.h"



struct File
{
	char name[MAX_FILENAME_SIZE];
	char owner[MAX_OWNER_SIZE];
	char type[MAX_FILETYPE_SIZE];
	double size;
	struct File* nextp;
};
typedef struct File File_t;






/* Node of the huffman tree */
struct node{
    int frequency;
    char letter;
    struct node *left,*right;
};

typedef struct node node_t;

/*
input: mode 0 is edit own details
		mode 1 is edit others details (for admins only)
*/
void modifyFileDetails(User_t* currentUserp, File_t* fileHeadp);

/*hai*/
char *getFileType(File_t *filep);
/*int setFileName(File_t *filep);
int deleteFile(File_t *filep);
int deleteDirectory(char *namep);
File_t *searchName(File_t* head, char name[]);
int addFile(File_t* head, char name[], char type[], date_t date);
date_t getDate(File_t *filep);*/

/*from monday 25/09/2017*/

/**********************************************************
setFileName - Hai
-This function allows user to make change to filename
-Inputs: 
	+ *filep: pointer to the target file
	+ *headFilep: pointer to the head file of the linked list
	   where 'filep' belongs to
-Outputs:
	+ added: return 1 if successfully deleted a file, 0 otherwise
***********************************************************/
int setFileName(File_t *filep, File_t *fileheadp, char owner[]);

File_t *searchFilename(File_t* fileheadp, char name[], char owner[]);

/**********************************************************
addFile - Hai
-This function adds a new file to a linked list
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: name of the new file
	+ type[]: type of the new file
	+ date: date of the new file
-Outputs:
	+ added: return 1 if successfully added a new file, 0 otherwise
***********************************************************/
int addFile(File_t* filehead, char owner[],char name[], char type[]);

/**********************************************************
deleteFile - Hai
-This function deletes a file in a linked list by its name
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: name of the file we want to delete
-Outputs:
	+ added: return 1 if successfully deleted a file, 0 otherwise
***********************************************************/
int deleteFile(File_t *fileheadp, char name[], char owner[]);

/**********************************************************
checkDuplicateFile - Hai
-This function checks if there is any duplicate file 
(have the same name) in the provided linkedlist
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
	+ name[]: the name we use to look for duplicates
-Outputs:
	+ check: 1 if there is a duplicate, 0 otherwise
***********************************************************/
int checkDuplicateFile(File_t *headFile, char name[], char owner[]); 

/**********************************************************
displayFiles - Hai
-This function prints all files that a user has
-Inputs: 
	+ *headFilep: pointer to the head file of the linked list
-Outputs:
	none
***********************************************************/
void displayFiles(File_t *filehead, char owner[]);



/*******************************************************************************
saveFileDatabase - James
-This function saves the database linked list into a database to allow reuse
-Inputs: 
	+ File_t* filep: pointer to the head file of the file linked list
-Outputs:
	none
*******************************************************************************/
int saveFileDatabase(File_t* filep);

/*******************************************************************************
readFileDatabase - James
-This function reads the database and saves (overwrites) it into the filep LL
-Inputs: 
	+ File_t* filep: pointer to the head file of the file linked list
-Outputs:
	none
*******************************************************************************/
int readFileDatabase(File_t* filep);


/**************************************************************/
	/*functions not used yet*/
/**************************************************************/

/**********************************************************
getFileName -Huy
-This function return the filename
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a string that contains the filename
***********************************************************/
char *getFileName(File_t *filep);





/*Hai's compression stuff*/
void invertCode(int codeTable[],int codeTable2[]);
void decompress(FILE *inp, FILE *outp, node_t *treep);
void compress(FILE *inp, FILE *outp, int binaryTable[]);
void fill(int binaryTable[], node_t *treep, int Code);
void buildTree(node_t **tree);
int findSmaller (node_t *arr[], int differentFrom);
int compressHuffman(char filename[], int binaryTable[]);
int decompressHuffman(char filename[], node_t *treep);


#endif

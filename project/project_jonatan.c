#include <stdio.h> /*printf, remove, rename, */
#include <stdlib.h> /*fclose, fprintf, fopen, malloc, free*/
#include <string.h> /*strcmp, strcpy*/
#include "helper.h" /*handleParsing, help, contains, getValue*/
#include "file.h" /*buildTree, fill, invertCode, compressHuffman, 
					decompressHuffman,*/
#include "user.h" /*loginAuthentication*/

/*#define DEBUG_MODE*/
/*#define DEBUG_MODE_ENCRYPTION*/

/*****************************************************************************
showMenu - Jonatan
-This function displays the initial selection menu to the user based on what
type of user they are
-Inputs: 
	+ the userType (i.e. standard user or admininstrator)
-Outputs:
	+ none
*****************************************************************************/
void showMenu(int userType)
{
	char* options = "Logged in as Administrator";

	if(userType == 1)
	{
		/*administrator*/
		printf("%s \n\n", options);
		printf("1. Modify Details\t\t2. Modify User Details\t\t"
			"3. Encrypt/Decrypt \n4. Encrypt/Decrypt Users\t5. Exit\n\n");		
	}
	else if (userType == 2)
	{
		/*standard user*/
		options = "Logged in as standard user";
		printf("%s \n\n", options);
		printf("1. Modify Details\t\t2. Encrypt/Decrypt\t\t3. Exit\n\n");		
	}
}

/*****************************************************************************
encryptDecrypt - Jonatan
-This function encrypts and decrypts a text file with the password that is 
given
-Inputs: 
	+ the file name and the password to encrypt it with
-Outputs:
	+ integer(successful) 1 or 0 (unsuccessful)
*****************************************************************************/
int encryptDecrypt(char* filename,  char* password)
{
	int i = 0;
	char ch;

	FILE* original_filep = NULL;
	FILE* encrypted_filep = NULL;
	original_filep = fopen(filename, "r");
	encrypted_filep = fopen("encrypted.txt", "w");

	if(encrypted_filep==NULL)
	{
		printf("error opening encrypted_filep");
		return 0;
	}

	if(original_filep == NULL)
	{
		/*printf("Read error opening original file\n");*/
		remove("encrypted.txt");
		return 0;
	}

	int key_length;
	key_length = strlen(password);

	#ifdef DEBUG_MODE_ENCRYPTION
		printf("\n\nkeylength: %d\n", key_length);
	#endif
	
	char* ciphertext;

	do
	{
		ch = fgetc(original_filep);
		ciphertext = (char*) malloc(sizeof(char));
		ciphertext[i] = password[i % key_length] ^ ch; 

		if(ch != EOF)
		{
			fprintf(encrypted_filep, "%c",ciphertext[i]);
			#ifdef DEBUG_MODE_ENCRYPTION
				printf("ciphertext: %c\t", ciphertext[i] );
				printf("i: %d \t ch: %c \t password: %c \t ciphertext: %c\n",
				 i, ch, password[i % key_length], ciphertext[i]);
			#endif
			i++;
		}
		else
		{
			ciphertext[i] = '\0';
			
			#ifdef DEBUG_MODE_ENCRYPTION
				printf("end of file character reached\n");
			#endif
		}
	}while(ch != EOF);

	/*remove original file and rename the encrypted file to the original*/
	int removed;
	removed = remove(filename);
	
	int renamed;
	renamed = rename("encrypted.txt", filename);
	
	if(removed != 0)
	{
		printf("file test has not been removed\n");
		return 0;
	}

	if(renamed != 0)
	{
		printf("the file has not been renamed\n");
		return 0;
	}

	fclose(encrypted_filep);
	return 1;
} /*end encryptDecrypt*/

/*****************************************************************************
handleParsing - Jonatan
-This function handles any parsing that the program performs
-Inputs: 
	+ the argument count
	+ the argument vector
	+ the head node of the user list
-Outputs:
	+ integer(successful) 1 or 0 (unsuccessful)
*****************************************************************************/
int handleParsing(int argc, char* argv[], User_t* userHeadp)
{
	char* filename = "\0";
	char* filepassword  = "\0";
	char* userpassword = "\0";
	char* username = "\0";
	int status = 0;

	getValue(argc, argv, "-fn", "-filename", &filename);
	getValue(argc, argv, "-fp", "-filepassword", &filepassword);
	getValue(argc, argv, "-urn", "-username", &username);
	getValue(argc, argv, "-urp", "-userpassword", &userpassword);

	if((contains(argc, argv, "-urn", "username") == 1) && 
		(contains(argc, argv, "-urp", "userpassword") == 1) &&
		!(loginAuthentication(username, userpassword, userHeadp) > 0) )
	{
		printf("\nInvalid credentials!\n");
		return 1;
	}

	#ifdef DEBUG_MODE
			printf("\nfile_name: %s, password: %s \n"
				"username: %s, userpassword: %s\n",
				filename, filepassword, username, userpassword);
			printf("loginAuthentication %d\n", 
				loginAuthentication(username, userpassword, userHeadp));
	#endif

	if((contains(argc, argv, "-h", "-help") == 1) && argc == 2)
	{
		help();	
	}
	else if((contains(argc, argv, "-en", "-encrypt") == 1) && 
		(contains(argc, argv, "-urn", "username") == 1) && 
		(contains(argc, argv, "-urp", "userpassword") == 1) &&
		argc == 10)
	{
		if((username[0] != '\0') && (userpassword[0] !='\0') &&
			(filename[0] != '\0') && (filepassword[0] != 0))
		{
			status = encryptDecrypt(filename, filepassword);
		}

		if(status == 1)
		{
			printf("file successfully encrypted\n");
			return 0;
		}
		else
		{
			printf("error encrypting file\n");
			return 1;
		}
	}
	else if((contains(argc, argv, "-de", "-decrypt") == 1) && 
		(contains(argc, argv, "-urn", "username") == 1) && 
		(contains(argc, argv, "-urp", "userpassword") == 1) &&
		argc == 10)
	{
		if((username[0] != '\0') && (userpassword[0] !='\0') &&
			(filename[0] != '\0') && (filepassword[0] != 0))
		{
			status = encryptDecrypt(filename, filepassword);
		}

		if(status == 1)
		{
			printf("file successfully decrypted\n");
			return 0;
		}
		else
		{
			printf("error decrypting file\n");
			return 1;
		}
	}else if((contains(argc, argv, "-c", "-compress") == 1) && 
		(contains(argc, argv, "-urn", "username") == 1) && 
		(contains(argc, argv, "-urp", "userpassword") == 1) &&
		argc == 8)
	{
		if((username[0] != '\0') && (userpassword[0] !='\0') && 
			(filename[0] != '\0'))
		{
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

			check = compressHuffman(filename, binaryTable2);

			if(check == 1){
				printf("\nYOU HAVE SUCCESSFULLY COMPRESSED THE FILE.\n");
				return 0;
			}
			else{
				printf("\nERROR, UNSUCCESSFULLY COMPRESSED FILE.\n");
				return 1;
			}
			status = encryptDecrypt(filename, filepassword);
		}
	}
	else if((contains(argc, argv, "-dc", "-decompress") == 1) && 
		(contains(argc, argv, "-urn", "username") == 1) && 
		(contains(argc, argv, "-urp", "userpassword") == 1) &&
		argc == 8)
	{
		if((username[0] != '\0') && (userpassword[0] !='\0') &&
			(filename[0] != '\0'))
		{
			char decompressName[MAX_FILENAME_SIZE];
			int check;
			node_t *treep; 
			buildTree(&treep);
			strcpy(decompressName, "decompressed.txt");
		
			check = decompressHuffman(filename, treep);
			
			if(check == 1)
			{
				printf("\nYOU HAVE SUCCESSFULLY DECOMPRESSED THE FILE.\n");
				return 0;
			}
			else
			{
				printf("\nERROR, UNSUCCESSFULLY DECOMPRESSED FILE.\n");
				return 1;
			}
		}
	}
	else
	{
		printf("Invalid statements! use -h or -help for more info\n");
	}
	return 0;
} /*end handleParsing*/

/*****************************************************************************
help - Jonatan
-This function displays the help menu for command line parsing commands
-Inputs: 
	+ the argument count
	+ the argument vector
-Outputs:
	+ none
*****************************************************************************/
void help()
{
	clear();
	printf("\n\t\t\t\t\t\t_________File Manager 5000_________\n\n"
		"Outlined below are the commands that can be used to perform specific" 
		" functions on the File_Manager_5000\n\n"
		"command\t\t\t\t | Example\n\n"
		"  -en   |  -encrypt\t\t"
		"   ./File_Manager_5000.out -en -n [filename] -fp [filepassword] "
		"-urn [username] -urp [userpassword]\n"
		"  -de   |  -decrypt\t\t"
		"   ./File_Manager_5000.out -de -fn [filename] -fp [filepassword]"
		"-urn [username] -urp [userpassword]\n"
		"  -c    |  -compress\t\t"
		"   ./File_Manager_5000.out -c -fn [filename] -urn [username] -urp"
		" [userpassword]\n"
		"  -dc   |  -decompress\t\t"
		"   ./File_Manager_5000.out -dc -fn [filename] -urn [username] -urp"
		" [userpassword]\n\nKey\t\t\t\t | Description\n\n"
		"  -fn   |  -filename\t\t   name of file to perform action on\n"
		"  -fp   |  -filepassword\t   filepassword if required\n"
		"  -h    |  -help\t\t   show the help menu\n"
		"  -urn  |  -username\t\t   username of person in the system\n"
		"  -urp  |  -userpassword\t   password of person in the system\n");
} /*end help*/

/*****************************************************************************
contains - Jonatan
-This function checks if the given argument vector contains the 
given arguments
-Inputs: 
	+ the argument count
	+ the argument vector
	+ the short version of the command
	+ the long version of the command
-Outputs:
	+ added: count of how many times and argumen occurs
*****************************************************************************/
int contains(int argc, char* argv[], char* short_arg, char* long_arg)
{
	int i; 
	int count = 0;

	for(i = 1; i < argc; i++)
	{
		if((strcmp(argv[i], short_arg) == 0) || 
			(strcmp(argv[i], long_arg) ==0)){
			count++;
		}
	}

	if(count > 1)
	{
		printf("multiple use of command\n");
		return 0;
	}
	return count;
} /*end help*/

/*****************************************************************************
getValue - Jonatan
-This function returns the value that is requested
-Inputs: 
	+ the argument count
	+ the argument vector
	+ the short version of the command
	+ the long version of the command
	+ the value that is to be changed
-Outputs:
	+ none
*****************************************************************************/
void getValue(int argc, char* argv[], char* short_arg1, 
	char* long_arg1, char* value[])
{
	int i;

	for(i = 1; i < argc; i++)
	{
		if(((strcmp(argv[i], short_arg1) == 0) || 
			(strcmp(argv[i], long_arg1) ==0)) && 
			(argv[i+1][0] !='-'))
		{
			#ifdef DEBUG_MODE
				printf("argv[i+1]: %s\n", argv[i+1]);
			#endif
			*value = argv[i+1];
		}
	}
} /*end getValue*/

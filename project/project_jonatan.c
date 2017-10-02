#include <stdio.h> /*printf, remove, rename, */
#include <stdlib.h> /*fclose, fprintf, fopen, malloc, free*/
#include <string.h>
#include "helper.h"

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
	else if(userType == 3)
	{
		/*guest*/
		options = "Logged in as guest";
		printf("%s \n\n", options);
		printf("1. Compress/Decompress\t\t2. Exit\n\n");		
	}
}

/*
	author: Jonatan
*/
int encryptDecrypt(char* filename,  char* password)
{
	/*
		we might have to add an aditional field to the struct to see if the 
		file is encrypted or not it is, return 0
	*/
	int i = 0;
	char ch;

	FILE* original_filep = NULL;
	FILE* encrypted_filep = NULL;
	original_filep = fopen("test", "r");
	encrypted_filep = fopen("encrypted", "w");

	if(encrypted_filep==NULL)
	{
		printf("error opening encrypted_filep");
		return 0;
	}

	if(original_filep == NULL)
	{
		printf("Read error\n");
		return 0;
	}

	int key_length;
	key_length = strlen(password);

	#ifdef DEBUG_MODE
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
		
			#ifdef DEBUG_MODE
				printf("i: %d \t ch: %c \t password: %c \t ciphertext: %c\n",
				 i, ch, password[i % key_length], ciphertext[i]);
			#endif
			i++;
		}
		else
		{
			ciphertext[i] = '\0';
			
			#ifdef DEBUG_MODE
				printf("end of file character reached\n");
			#endif
		}
		
		
	}while(ch != EOF);

	int removed;
	removed = remove(filename);

	if(removed == 1)
	{
		printf("file has been removed\n");
	}
	char* newname;
	newname = strcat("_encrypted", filename);

	int renamed;
	renamed = rename(newname, filename);

	if(renamed == 1)
	{
		printf("the file has been renamed\n");
	}
	
	fclose(encrypted_filep);
	return 1;
} /*end encryptDecrypt*/
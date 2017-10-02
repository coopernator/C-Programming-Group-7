#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*#include "uielements.h"*/
void showMenu(int userType);
int main(void){
	showMenu(1);	
	return 0;
}

void showMenu(int userType){
	
	char* options = "Logged in as Administrator";
	
	printf("\e[1;1H\e[2J");

	if(userType == 1)
	{
	/*administrator*/
		printf("%s ____________________________________________________"
		"______________________________________________________________"
		"_________________\n\n", options);
	printf("1. Modify Details\t\t2. Modify User Details\t\t3. Encrypt/Decrypt "
		"\n4. Encrypt/Decrypt Users\t5. Exit\n");

	printf("_________________________________________________________________"
		"____________________________________________________________________"
		"_________________________\n");
		
	}
	else if (userType == 2)
	{
	/*standard user*/
		options = "Logged in as standard user";
		printf("%s _________________________________________________________"
		"___________________________________________________________________"
		"____________\n\n", options);
	printf("1. Modify Details\t\t\t2. Encrypt/Decrypt"
		" 3. Compresses/Decompress\n\t3. Exit\n");

	printf("_________________________________________________________________"
		"__________________________________________________________________"
		"___________________________\n");
		
	}
	else if(userType == 3)
	{
		/*guest*/
		options = "Logged in as guest";
		printf("%s _________________________________________________________"
		"___________________________________________________________________"
		"____________\n\n", options);
	printf("1. Compress/Decompress 5. Exit\n");

	printf("______________________________________________________________"
		"___________________________________________________________________"
		"_____________________________\n");
		
	}
	printf("> ");
}



/*
	i
	nt i;
		char* currentDirectory = "~/User/Desktop/";
		char* stack = "stack";
	int option;

	printf("This is the show menu function\n");*/	
	/*printf("%s_______________________________________________________________________________"
		"_______________________________________________________________________________\n", currentDirectory);
	printf("Name\t\t\t\t\t\t\t\t\t\tType\tSize\tDate Modified\tDate Created\t\n");
	printf("\n\n\n\n\n\n\n\n");

	for(i = 0; i < 15; i++){
		printf("|                                                                             |\n");
	}
	printf("%s_______________________________________________________________________________"
		"_______________________________________________________________________________\n", stack);
	printf("\n\n\n\n\n\n\n\n");*/
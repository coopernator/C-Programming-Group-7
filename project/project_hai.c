#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "file.h"
#include "user.h"

/*#define len(x) ((int)log10(x)+1)*/

int englishLetterFrequencies [27] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 130};



/**********************************************************
getFileName
-This function returns the filename
-Inputs: 
	+ *filep: pointer to the target file
-Outputs:
	+ namep: pointer to a string that contains the filename
**********************************************************
char *getFileName(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *namep =(char*) malloc(len + 1);
	strcpy(namep, filep->name);
	return namep;
} getFileName*/

/**********************************************************
addFile
-This function adds a new file to a linked list
-Inputs: 
	+ *filehead: pointer to the head file of the linked list
	+ name[]: name of the new file
	+ type[]: type of the new file
	+ date: date of the new file
-Outputs:
	+ added: return 1 if successfully added a new file, 0 otherwise
***********************************************************/
int addFile(File_t* filehead, char owner[],char name[], char type[]){
	File_t *currentp = filehead;
	int added = 0;

	/*loop each element in the linked list until nextp is NULL*/
	while(currentp->nextp != NULL){
		currentp = currentp->nextp;
	}
	/*after the loop, currentp now points to the last 
	element in the linked list*/
	
	if(checkDuplicateFile(filehead, name, owner) != 1){
		currentp->nextp = (File_t*) malloc(sizeof(File_t));
		strcpy(currentp->nextp->name, name);
		strcpy(currentp->nextp->type, type);
		strcpy(currentp->nextp->owner, owner);
		currentp->nextp->size = 0;
		currentp->nextp->nextp = NULL;
		added = 1;
	}
	return added;
}


char *getFileType(File_t *filep){
	int len;
	len  = strlen(filep->name);
	char *typep =(char*) malloc(len + 1);
	strcpy(typep, filep->name);
	return typep;
}

int setFileName(File_t *filep, File_t *fileheadp, char owner[]){
	char name[MAX_FILENAME_SIZE];
	
	printf("Please enter a new filename:");
	fscanf(stdin, "%[MAX_FILE_NAME-1]s", name);
	
	if(!checkDuplicateFile(fileheadp, name, owner)){
		filep->name[0] = '\0';
		strcpy(filep->name, name);
		return 1;
	}
	
	printf("FILENAME ALREADY EXISTS.\n");
	return 0;
}

int deleteFile(File_t *headFilep, char name[]){ 
	File_t *foundp = NULL;
	File_t *currentp = headFilep;
	
	if(headFilep == NULL){
		printf("ERROR, THERE IS NO FILE TO DELETE.\n");
		return 0;
	}
	
	foundp = searchFilename(headFilep, name);
	if(foundp == NULL){
		printf("ERROR, FILE DOES NOT EXIST.\n");
		return 0;
	}
	else{
		while( strcmp(currentp->nextp->name, foundp->name) ){
				currentp = currentp->nextp;
		}
	}
	
	currentp->nextp = foundp->nextp;
	return 1;
}

File_t *searchFilename(File_t* headFilep, char name[]){
	File_t *currentp = headFilep;
	int check = 0;
	
	while( currentp != NULL ){
		if(strcmp(currentp->name, name) == 0){
			check =1;
		}
		else{
			currentp = currentp->nextp;
		}
		
		if(check)
			break;
	}
	
	return currentp;
}

/*
date_t getDate(File_t *filep){
	date_t date;
	
	date.day = filep->date.day;
	date.month = filep->date.month;
	date.year = filep->date.year;
	
	return date;
}*/

void displayUsers(User_t *headUserp){
	User_t *currentp = headUserp;
	
	if(currentp == NULL)
		printf("THERE IS NO ACCOUNT IN THIS LINKED LIST.\n");
	else{
		while(currentp != NULL){
			printf("%s\n", currentp->username);
			currentp = currentp->nextp;
		}
	}
}

void displayFiles(File_t *filehead, char owner[]){
	File_t *currentp = filehead;
	
	if(currentp->nextp == NULL)
		printf("THERE IS NO FILE.\n");
	else{
		/*loop each element in the linked list until currentp is NULL*/
		while(currentp != NULL){
			if( strcmp(currentp->owner, owner)==0 ){
				printf("%-10.10s %-10.10s %-10.10s %.3f\n", 
					currentp->owner, currentp->name,
					currentp->type, currentp->size);
			}
			currentp = currentp->nextp;
		}
	}
}

int checkDuplicateUser(User_t *headUserp, char name[]){
	int check = 0;
	User_t *currentp = headUserp;
	
	/*loop each element in the linked list until currentp is NULL*/
	while(currentp != NULL){
		if(strcmp(currentp->username, name) == 0){
			check = 1;
			break;
		}
		currentp = currentp->nextp;
	}	
	return check;
}

int checkDuplicateFile(File_t *filehead, char name[], char owner[]){
	int check = 0;
	File_t *currentp = filehead;
	
	/*loop each element in the linked list until currentp is NULL*/
	while(currentp != NULL){
		if( (strcmp(currentp->name, name)==0) && (strcmp(currentp->owner, owner)==0) ){
			check = 1;
			break;
		}
		currentp = currentp->nextp;
	}
	return check;
}





/*COMPRESSION STUFF



*/




/*finds and returns the small sub-tree in the forrest*/
int findSmaller (Node *array[], int differentFrom){
    int smaller;
    int i = 0;

    while (array[i]->value==-1)
        i++;
    smaller=i;
    if (i==differentFrom){
        i++;
        while (array[i]->value==-1)
            i++;
        smaller=i;
    }

    for (i=1;i<27;i++){
        if (array[i]->value==-1)
            continue;
        if (i==differentFrom)
            continue;
        if (array[i]->value<array[smaller]->value)
            smaller = i;
    }

    return smaller;
}

/*builds the huffman tree and returns its address by reference*/
void buildHuffmanTree(Node **tree){
    Node *temp;
    Node *array[27];
    int i, subTrees = 27;
    int smallOne,smallTwo;

    for (i=0;i<27;i++){
        array[i] = malloc(sizeof(Node));
        array[i]->value = englishLetterFrequencies[i];
        array[i]->letter = i;
        array[i]->left = NULL;
        array[i]->right = NULL;
    }

    while (subTrees>1){
        smallOne=findSmaller(array,-1);
        smallTwo=findSmaller(array,smallOne);
        temp = array[smallOne];
        array[smallOne] = malloc(sizeof(Node));
        array[smallOne]->value=temp->value+array[smallTwo]->value;
        array[smallOne]->letter=127;
        array[smallOne]->left=array[smallTwo];
        array[smallOne]->right=temp;
        array[smallTwo]->value=-1;
        subTrees--;
    }

    *tree = array[smallOne];

return;
}

/* builds the table with the bits for each letter. 1 stands for binary 0 and 2 for binary 1 (used to facilitate arithmetic)*/
void fillTable(int codeTable[], Node *tree, int Code){
    if (tree->letter<27)
        codeTable[(int)tree->letter] = Code;
    else{
        fillTable(codeTable, tree->left, Code*10+1);
        fillTable(codeTable, tree->right, Code*10+2);
    }

    return;
}

/*function to compress the input*/
void compressFile(FILE *input, FILE *output, int codeTable[]){
    char bit, c, x = 0;
    int n,length,bitsLeft = 8;
    int originalBits = 0, compressedBits = 0;

    while ((c=fgetc(input))!=10){
        originalBits++;
        if (c==32){
            length = len(codeTable[26]);
            n = codeTable[26];
        }
        else{
            length=len(codeTable[c-97]);
            n = codeTable[c-97];
        }

        while (length>0){
            compressedBits++;
            bit = n % 10 - 1;
            n /= 10;
            x = x | bit;
            bitsLeft--;
            length--;
            if (bitsLeft==0){
                fputc(x,output);
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
        }
    }

    if (bitsLeft!=8){
        x = x << (bitsLeft-1);
        fputc(x,output);
    }

    /*print details of compression on the screen*/
    fprintf(stderr,"Original bits = %dn",originalBits*8);
    fprintf(stderr,"Compressed bits = %dn",compressedBits);
    fprintf(stderr,"Saved %.2f%% of memoryn",((float)compressedBits/(originalBits*8))*100);

}

/*function to decompress the input*/
void decompressFile (FILE *input, FILE *output, Node *tree){
    Node *current = tree;
    char c,bit;
    char mask = 1 << 7;
    int i;

    while ((c=fgetc(input))!=EOF){

        for (i=0;i<8;i++){
            bit = c & mask;
            c = c << 1;
            if (bit==0){
                current = current->left;
                if (current->letter!=127){
                    if (current->letter==26)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }

            else{
                current = current->right;
                if (current->letter!=127){
                    if (current->letter==26)
                        fputc(32, output);
                    else
                        fputc(current->letter+97,output);
                    current = tree;
                }
            }
        }
    }

    return;
}

/*invert the codes in codeTable2 so they can be used with mod operator by compressFile function*/
void invertCodes(int codeTable[],int codeTable2[]){
    int i, n, copy;

    for (i=0;i<27;i++){
        n = codeTable[i];
        copy = 0;
        while (n>0){
            copy = copy * 10 + n %10;
            n /= 10;
        }
        codeTable2[i]=copy;
    }

return;
}






void createHuffman(char filename[], int compress){
Node *tree;
    int codeTable[27], codeTable2[27];    
    FILE *input, *output;

    buildHuffmanTree(&tree);

    fillTable(codeTable, tree, 0);

    invertCodes(codeTable,codeTable2);


    input = fopen(filename, "r");
    output = fopen("output.txt","w");

    if (compress==1)
        compressFile(input,output,codeTable2);
    else
        decompressFile(input,output, tree);
} 
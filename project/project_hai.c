#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "file.h"
#include "user.h"

#define len(x) ((int)log10(x)+1)




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
	FILE *fp;
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
		fp = fopen(name, "w");
		fclose(fp);
		added = 1;
	}
	return added;
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

int deleteFile(File_t *fileheadp, char name[], char owner[]){ 
	File_t *foundp = NULL;
	File_t *currentp = fileheadp;
	
	if(fileheadp->nextp == NULL){
		printf("ERROR, THERE IS NO FILE TO DELETE.\n");
		return 0;
	}
	
	foundp = searchFilename(fileheadp, name, owner);
	if(foundp == NULL){
		printf("ERROR, FILE DOES NOT EXIST.\n");
		return 0;
	}
	else{
		while( strcmp(currentp->nextp->name, foundp->name) ){
				currentp = currentp->nextp;
		}
		
		remove(name);
	}
	
	currentp->nextp = foundp->nextp;
	return 1;
}

File_t *searchFilename(File_t* fileheadp, char name[], char owner[]){
	File_t *currentp = fileheadp;
	
	if(fileheadp->nextp == NULL){
		printf("THERE IS NO FILE.");
		return NULL;
	}
	
	while( currentp != NULL ){
		if( (strcmp(currentp->name, name)==0 ) && (strcmp(currentp->owner, owner)==0) ){
			return currentp;
		}
		else{
			currentp = currentp->nextp;
		}
	}
	
	return NULL;
}


void displayUsers(User_t *headUserp){
	User_t *currentp = headUserp->nextp;
	
	if(headUserp->status == 1){
		if(currentp == NULL)
		printf("FATAL ERROR!!! THERE IS NO ADMIN.\n");
		else{
			while(currentp != NULL){
				printf("Name: %s, Status: %d.\n", currentp->username,currentp->status);
				currentp = currentp->nextp;
			}
		}
	}
	else if(headUserp->status == 2){
		if(currentp == NULL)
		printf("THERE IS NO USER.\n");
		else{
			while(currentp != NULL){
				printf("Name: %s, Status: %d.\n", currentp->username,currentp->status);
				currentp = currentp->nextp;
			}
		}
	}
}

void displayFiles(File_t *filehead, char owner[]){
	File_t *currentp = filehead;
	File_t *temp = filehead;
	int numFile = 0;
	
	while(temp != NULL){
		if(strcmp(temp->owner, owner)==0){
			numFile++;
		}
		temp = temp->nextp;
	}
	
	if(currentp->nextp == NULL)
		printf("THERE IS NO FILE IN DATABASE.\n");
	else if(numFile == 0){
		printf("THIS USER HAS NO FILES.");
	}
	else{
		/*loop each element in the linked list until currentp is NULL*/
		while(currentp != NULL){
			if( strcmp(currentp->owner, owner)==0 ){
				printf("%-20.20s %-20.20s %-10.10s %.3f\n", 
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
		if( (strcmp(currentp->name, name)==0) ){
			check = 1;
			break;
		}
		currentp = currentp->nextp;
	}
	return check;
}





/*COMPRESSION STUFF



*/




/*finds and returns the small sub-tree*/
int findSmaller (node_t *arr[], int differentFrom){
    int smaller, i = 0;
    
    while (arr[i]->value==-1){
        i++;
	}
	
    smaller=i;
	
    if (i==differentFrom){
        i++;
        while (arr[i]->value==-1){
            i++;
		}
		
        smaller=i;
    }

    for (i=1;i<27;i++){
        if (arr[i]->value==-1){
            continue;
		}
        if (i==differentFrom){
            continue;
		}
        if (arr[i]->value < arr[smaller]->value){
            smaller = i;
		}
    }

    return smaller;
}

/*builds the huffman tree and returns its address by reference*/
void buildTree(node_t **tree){
	int frequencies [27] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 130};
    node_t *temp;
    node_t *arr[27];
	int smallOne,smallTwo;
    int i, sub = 27;
    

    for (i=0; i<27; i++){
        arr[i] = malloc(sizeof(node_t));
		arr[i]->right = NULL;
        arr[i]->left = NULL;
		arr[i]->value = frequencies[i];
        arr[i]->letter = i;
    }

    while (sub > 1){
        smallOne=findSmaller(arr,-1);
        smallTwo=findSmaller(arr,smallOne);
        temp = arr[smallOne];
        arr[smallOne] = malloc(sizeof(node_t));
        arr[smallOne]->value = temp->value + arr[smallTwo]->value;
        arr[smallOne]->letter = 127;
		arr[smallOne]->right = temp;
        arr[smallOne]->left = arr[smallTwo];
        arr[smallTwo]->value = -1;
        sub--;
    }

    *tree = arr[smallOne];
}

/* builds the table and assign the bit for each letter: 1 stands for binary 0 and 2 for binary 1*/
void fill(int binaryTable[], node_t *treep, int binary){
    if (treep->letter < 27)
        binaryTable[(int)treep->letter] = binary;
    else{
        fill(binaryTable, treep->left, binary*10+1);
        fill(binaryTable, treep->right, binary*10+2);
    }

}

/*function to compress the input*/
void compress(FILE *inp, FILE *outp, int binaryTable[]){
    char bit, ch, x = 0;
    int n, len, left = 8;
    int original = 0, compressed = 0;

    while ((ch=fgetc(inp)) != EOF){
        original++;
		
        if (ch==32){
			n = binaryTable[26];
            len = len(binaryTable[26]);
            
        }
        else{
			n = binaryTable[ch-97];
            len = len(binaryTable[ch-97]);
            
        }

        while (len>0){
			
            compressed++;
            bit = n%10 - 1;
            n = n/10;
            x = x | bit;
			len--;
            left--;
            
            if (left==0){
                fputc(x, outp);
                left = 8;
				x = 0;
            }
			
            x = x << 1;
        }
    }

    if (left != 8){
        x = x << (left - 1);
        fputc(x, outp);
    }

    printf("Originally, the file is: %d bits.\n", original*8);
    printf("After compressed, the file is: %d bits.\n", compressed);
    printf("Saved %.2f%% of memory.\n", ((float)compressed/(original*8))*100);

}

void decompress (FILE *inp, FILE *outp, node_t *treep){
    node_t *currentp = treep;
    char sign = 1 << 7;
	char ch, bit;
    int i;

    while ( (ch=fgetc(inp)) != EOF ){

        for (i=0; i<8; i++){
            bit = ch & sign;
            ch = ch << 1;
            if (bit==0){
                currentp = currentp->left;
                if (currentp->letter != 127){
                    if (currentp->letter == 26){
                        fputc(32, outp);
					}
                    else{
                        fputc(currentp->letter+97, outp);
					}
                    currentp = treep;
                }
            }
            else{
                currentp = currentp->right;
				
                if (currentp->letter != 127){
					
                    if (currentp->letter == 26){
                        fputc(32, outp);
					}
                    else{
                        fputc(currentp->letter+97, outp);
					}
					
                    currentp = treep;
                }
            }
        }
    }
}


/*invert the codes in binaryTable2 so they can be used with mod operator by compressFile function*/
void invertCode(int binaryTable[],int binaryTable2[]){
    int i, num , temp;

    for (i=0; i<27; i++){
		temp = 0;
        num = binaryTable[i];
        
        while (num > 0){
            temp = temp*10 + num%10;
            num = num/10;
        }
		
        binaryTable2[i] = temp;
    }

}

void update(FILE *inp, FILE *outp){
	int ch;
	
	for(ch = fgetc(inp); ch != EOF ; ch = fgetc(inp)){
		fputc(ch, outp);
	}
	
}


int compressHuffman(char filename[], int binaryTable[]){
	
    FILE *inp, *comp;
	
	
    inp = fopen(filename, "r");
	
	if(inp == NULL){
		printf("FILE INPUT ERROR.");
		return 0;
	}
	else{
		comp = fopen("compressed.txt","w");
		compress(inp, comp, binaryTable);
		fclose(comp);
		fclose(inp);

	}
	
	return 1;
}

int decompressHuffman(char filename[], node_t *treep){
	
    FILE *inp, *decomp;
	
    inp = fopen(filename, "r");
	
	if(inp == NULL){
		printf("FILE INPUT ERROR.");
		return 0;
	}
	else{
		decomp = fopen("decompressed.txt","w");
		decompress(inp, decomp, treep);
		fclose(decomp);
		fclose(inp);
			
	}
	
	return 1;
} 

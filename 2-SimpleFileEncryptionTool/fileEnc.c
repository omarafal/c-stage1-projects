#include "fileEnc.h"

void perr(const char *errMsg){
    fprintf(stderr, "%s", errMsg);
    exit(EXIT_FAILURE);
}

FILE *readFile(const char *fileName){
    if (strlen(fileName) > 255){
        perror("The name of the file is too long. Exiting.\n");
    }

    FILE *pF = fopen(fileName, "r");
    
    if(pF == NULL){
        perr("No such file found.");
    }

    printf("File found: %s\n", fileName);
    return pF;
}

unsigned int getSizeOf(const char *fileName){
    struct stat file;

    if(stat(fileName, &file) == 0){
        return file.st_size;
    }
    return 0;
}

char *grabFileContent(FILE *filePointer, unsigned int fileSize){
    char *buff;
    char *content = (char *)malloc(fileSize);

    if(fileSize == 0){
        perr("File is empty.");
    }

    fread(content, 1, fileSize, filePointer); // at this point, file already exists
    
    return content;
}

char *encryptContent(char *content, unsigned int key, unsigned int fileSize){
    // if any non-alphabet character, just put as is
    char letter;
    int i = 0;

    char *encContent = (char *)malloc(fileSize+1); // encrypted content

    char newLetter;
    for(int i = 0; i < fileSize; i++){
        letter = *(content + i);

        // check if letter is not alphabetical
        if(!(letter >= CHAR_A && letter <= CHAR_Z) && !(letter >= CHAR_a && letter <= CHAR_z)){
            encContent[i] = letter;
            continue;
        }
        
        if(letter >= CHAR_A && letter <= CHAR_Z){
            newLetter = (letter + key) % (CHAR_Z+1);
            encContent[i] = newLetter < CHAR_A ? newLetter + CHAR_A : newLetter;
        }
        else if(letter >= CHAR_a && letter <= CHAR_z){
            newLetter = (letter + key) % (CHAR_z+1);
            encContent[i] = newLetter < CHAR_a ? newLetter + CHAR_a : newLetter;
        }
    }

    encContent[fileSize] = '\0';

    return encContent;
}
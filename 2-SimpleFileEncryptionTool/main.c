/*
Simple File Encryption Tool
Description: Read a file, encrypt text using Caesar Cipher, write back to a file.

Concepts: File I/O, character manipulation.
*/

#include "fileEnc.h"

int main(int argc, char *argv[]){

    if(argc < 3){
        perr("Too few arguments passed.");
    }

    char *fileName = argv[1];
    unsigned int key = (unsigned int) abs(atoi(argv[2]));
    unsigned int fileSize = getSizeOf(fileName);

    if(key == 0){
        perr("You have entered an invalid key.\n");
    }

    printf("%hu\n", key);

    FILE * pF = readFile(fileName);
    char *content = grabFileContent(pF, fileSize);

    char *encContent = encryptContent(content, key, fileSize);

    printf("========= Encrypted Text =========\n");
    printf("%s", encContent);

    fclose(pF);
    free(content);
    free(encContent);

    return 0;
}
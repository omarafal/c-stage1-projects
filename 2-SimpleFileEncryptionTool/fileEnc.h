#ifndef FILE_ENC_H
#define FILE_ENC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define CHAR_A 65
#define CHAR_Z 90
#define CHAR_a 97
#define CHAR_z 122

void perr(const char *errMsg);
FILE *readFile(const char *fileName);
unsigned int getSizeOf(const char *fileName);
char *grabFileContent(FILE *filePointer, unsigned int fileSize);
char *encryptContent(char *content, unsigned int key, unsigned int fileSize);

#endif
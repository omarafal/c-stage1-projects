/*
Student Record Management System
Description: Input, save, and read student data (name, ID).

Concepts: Structs, arrays, file I/O, sorting/searching.
*/

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

typedef char ID[8]; // example -> YYxxxxx

typedef struct {
    char fName[15];
    char lName[15];
    ID id;
} Student;

int main(){

    FILE *pDB;

    // if pDB
    char cmd[6];
    char id[8] = "0";
    char buffer[sizeof(cmd) + sizeof(id) + 2]; // + 2 for the space and \0
    bool done = false;
    
    // READ FILE VARS
    char studentIDFF[8];
    char studentFF[50]; // student from file

    // WRITE FILE VARS
    char studentTF[50] = ""; // student to file

    printf("=============== Student Database Manager ===============\n");
    // "read ID" retrieve student data
    // "write" will create a new student going to prompts

    do{

        printf("\nEnter \"help\" to see a list of available commands.\n");
        printf(">> ");

        if(fgets(buffer, sizeof(buffer), stdin)){
            sscanf(buffer, "%5s %7s", cmd, id);
        }

        if (strcmp(cmd, "help") == 0){
            printf("\nAVAILABLE COMMANDS:\n");
            printf("help -- show a list of available commands\n");
            printf("read [ID] -- grab information about a student with their ID\n");
            printf("write -- start prompting to enter\n");
            printf("exit -- exit the program\n");
        }
        else if (strcmp(cmd, "read") == 0){
            if(strlen(id) == 0){
                printf("Please enter a valid ID.\n");
                continue;
            }

            pDB = fopen("student_db.txt", "r");

            if(pDB == NULL){
                printf("No database found. Start by entering some students.\n");
                continue;
            }

            // grab student
            while(fgets(studentFF, sizeof(studentFF), pDB)){
                sscanf(studentFF, "%s", studentIDFF);

                if(strcmp(studentIDFF, id) == 0){
                    break;
                }
            }

            if(feof(pDB)){ // make sure newline exists at end of file
                printf("No such student exists with this ID.\n");
            }
            else{
                printf("Student found: %s\n", studentFF);
            }

            fclose(pDB);
        }
        else if (strcmp(cmd, "write") == 0){
            memset(studentTF, 0, sizeof(studentTF));
            Student st;
            
            printf("CREATING A NEW STUDENT\n");
            
            printf("First Name: ");
            scanf("%15s", &st.fName);
            printf("Last Name: ");
            scanf("%15s", &st.lName);
            printf("ID: ");
            scanf("%8s", &st.id);
            
            fgets(buffer, sizeof(buffer), stdin); // clear buffer
            
            printf("First: %s\nLast: %s\nID: %s\n", st.fName, st.lName, st.id);
            
            strcat(studentTF, st.id);
            strcat(studentTF, " ");
            strcat(studentTF, st.fName);
            strcat(studentTF, " ");
            strcat(studentTF, st.lName);
            strcat(studentTF, "\n");

            printf("Student: %s", studentTF);
            
            pDB = fopen("student_db.txt", "a");

            fwrite(studentTF, sizeof(char), strlen(studentTF), pDB);

            if(ferror(pDB)){
                perror("\nSomething went wrong.\n");
            }
            else{
                printf("\nData written successfully.\n");
            }

            fclose(pDB);
        }
        else if (strcmp(cmd, "exit") == 0){
            printf("Goodbye!");
            break;
        }
        else{
            printf("This is not a valid option, enter \"help\" to see available options.");
        }
    } while(true);

    return 0;
}
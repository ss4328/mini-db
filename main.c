#include <stdio.h>
#include <stdlib.h>
#include <MacTypes.h>
#include <string.h>

char update[] = "UPDATE";
char insert[] = "INSERT";
char select[] = "SELECT";
char delete[] = "DELETE";
char create[] = "CREATE";
char drop[] = "DROP";
char deleted[] = "/deleted/";

//char quit[] = "QUIT\n";
//char table1[] = "table1.csv";
//char table2[] = "table2.csv";

char input[100];
char inputString[10][15];


//char fields[12][10];


int getCSVColumnsCount(char fileName[]){
    int numberOfColumns=0;

    FILE * fPointer1;
    fPointer1 = fopen(fileName, "r");
    char singleLine1[500];
    fgets(singleLine1, 500, fPointer1);

    char* token = strtok(singleLine1, ",");
    while (token != NULL) {
//        printf("%s\n", token);
        numberOfColumns++;
        token = strtok(NULL, ",");
    }

    fclose(fPointer1);

    return numberOfColumns;
}

Boolean string_equals(char str1[], char str2[])
{

    if (strcmp(str1, str2) == 0){
        return true;
    }
    else return false;
}

Boolean isValidCommand (char input[]){
    if ((string_equals(input, update) || string_equals(input, insert) || string_equals(input, select) || string_equals(input, delete) || string_equals(input, drop))){
        return true;
    }
    else return false;
}

void performDropOperation(){
    remove(strtok(inputString[2], "\n"));
}


//deletes specific lines from file by creating a new file of same name, writing it the same as line by line minus the selected lines, and then deleting the original file
void performDeleteOperationOnFile(char fileName[]){
    printf("Here in delete operation \n");

    int queryRowIndex = inputString[4][5] - '0';
    printf("Row number: %d \n", queryRowIndex);

    int CSVColumnsCount = getCSVColumnsCount(inputString[2]);

    //open file on read mode
    FILE * fPointer;
    fPointer = fopen(fileName, "r");

    //open file on write mode
    FILE * fWritePointer;
    fWritePointer = fopen("duplicate.csv", "w");
    int iterator =0;


    char singleLine[500];
    char singleLineCopy[500];
    char singleLineCopyCopy[500];



    //iterating over each line to check if it meets the requirement

    printf("\n");
    printf("Deleted Lines: \n");
    printf("---------------------------------------\n");
    while(!feof(fPointer)){
        fgets(singleLine, 500, fPointer);
        fgets(singleLine, 500, fWritePointer);
        strcpy(singleLineCopy, singleLine);
        strcpy(singleLineCopyCopy, singleLine);

        char tokenArray[12][100];
        char* token = strtok(singleLineCopy, ",");
        int i=0;


        while (token != NULL) {
//                printf("%s\n", token);
            if(i<CSVColumnsCount){
                strcpy(tokenArray[i],token);
                token = strtok(NULL, ",");
                i++;
            }
            else{
                i=0;
            }
        }

        if (strcmp(tokenArray[queryRowIndex], strtok(inputString[6], "\n"))!=0) {
//            puts(singleLine);
            fputs(singleLine,stdout);
            fprintf(fWritePointer, strcat(singleLineCopyCopy, "\n"), iterator + 1);
        }
    }
    fclose(fPointer);
    fclose(fWritePointer);
    printf("\n");
    printf("Printed all matching queries from table1.csv \n");
}


void performSelectOperationOnFile(char fileName[]){
    printf("Here in select operation on file function \n");

    int queryRowIndex = inputString[5][5] - '0';
    printf("Row number: %d \n", queryRowIndex);

    int CSVColumnsCount = getCSVColumnsCount(inputString[3]);

    printf("The number of columns in csv: %d \n", CSVColumnsCount);
    FILE * fPointer;
    fPointer = fopen(fileName, "r");
    char singleLine[500];
    char singleLineCopy[500];


    //iterating over each line to check if it meets the requirement

    printf("\n");
    printf("Results: \n");
    printf("---------------------------------------\n");
    while(!feof(fPointer)){
        fgets(singleLine, 500, fPointer);
        strcpy(singleLineCopy, singleLine);

        char tokenArray[12][100];
        char* token = strtok(singleLineCopy, ",");
        int i=0;
        //tokenizes a single line to an array


        while (token != NULL) {
//                printf("%s\n", token);
            if(i<CSVColumnsCount){
                strcpy(tokenArray[i],token);
                token = strtok(NULL, ",");
                i++;
            }
            else{
                i=0;
            }
        }

        if(strcmp(tokenArray[queryRowIndex], strtok(inputString[7], "\n"))==0) {
            puts(singleLine);
        }
    }
    fclose(fPointer);
    printf("\n");
    printf("Printed all matching queries from table1.csv \n");
}

void performSelectOperation(){

    if(sizeof(inputString)<5){
        FILE * fPointer1;

        fPointer1 = fopen(inputString[3], "r");

        char singleLine1[500];

        while(!feof(fPointer1)){
            fgets(singleLine1, 500, fPointer1);
            puts(singleLine1);
        }
        fclose(fPointer1);
        printf("Printed all queries from table2 \n");
    }
    else{
        performSelectOperationOnFile(inputString[3]);
    }



}

void loadFileAndRun(){
    printf("here in loadFileAndRun \n");
    if(strcmp(inputString[0], select)==0){
        printf("u chose the select functionality \n");
        performSelectOperation();
    }
    else if(strcmp(inputString[0], update)==0){
        printf("u chose the update functionality \n");
    }
    else if(strcmp(inputString[0], insert)==0){
        printf("u chose the insert functionality \n");
    }
    else if(strcmp(inputString[0], delete)==0){
        printf("u chose the delete functionality \n");
        performDeleteOperationOnFile(inputString[2]);
    }
    else if(strcmp(inputString[0], drop)==0){
        performDropOperation();
    }
    else{
        printf("unrecognized command in LDAR \n");
    }

}

int main() {

    Boolean moreCommands = true;


    char quit[] ="QUIT\n";

    while(moreCommands) {
        printf("\n");
        printf("\n");
        printf("Please provide a valid command to continue: SELECT, INSERT INTO, DELETE FROM, UPDATE, QUIT \n");
        int i, j, ctr;
        printf("---------------------------------------\n");

        printf("Command: ");
        fgets(input, sizeof input, stdin);

        j = 0;
        ctr = 0;
        for (i = 0; i <= (strlen(input)); i++) {
            // if space or NULL found, assign NULL into inputString[ctr]
            if (input[i] == ' ' || input[i] == '\0') {
                inputString[ctr][j] = '\0';
                ctr++;  //for next word
                j = 0;    //for next word, init index to 0
            } else {
                inputString[ctr][j] = input[i];
                j++;
            }
        }
        printf(" %s\n", inputString[0]);

        if (strlen(inputString[0]) < 2) {
            printf(" Please enter a valid command. Input command too short. \n");
            moreCommands = false;
        } else if (string_equals(inputString[0], quit)) {
            printf("You chose to quit the application");
            moreCommands = false;
        } else if (isValidCommand(inputString[0])) {
            loadFileAndRun();
        } else {
            printf("Unrecognized command. \n");
            printf("Please provide a valid command to continue: SELECT, INSERT INTO, DELETE FROM, UPDATE, QUIT \n");
        }

    }
    return 0;
}

// SELECT * FROM table1.csv WHERE Field5 = 3
// DROP TABLE table1.csv
// DELETE FROM table1.csv WHERE Field5 = 1
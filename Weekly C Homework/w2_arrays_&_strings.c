#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 30

char string1[12] = "hello";
char string2[12] = "hello\n";
char string3[12] = "hello\n\0you\n";
char string4[12] = "0123456789AB";

void printArray(char a[], int length){
    printf("The current array is: ");
    printf("[");
    for (int i=0; i+1<=length; i++){
        
        if (a[i] == '\0') printf("\\0");
        else if (a[i] == '\n') printf("\\n");
        
        else  printf("%c",a[i]);
        if (i+1<length) printf(",");
    }
    printf("]\n");
}

void printString(char str[]){
    
    printf("The current string is: ");
    printf("\"");

    for (int j=0; j < strlen(str); j++){
        putchar(str[j]);
    }
    printf("\"");
    printf("\n");
    
}

void readLine(char str[], int length){
    int k=0;
    
    while(1){
        str[k] = getchar();
        if (str[k] == '\n'){
            str[k] = '\0';
            return;
        }
        if (k < length-1) k++;
    }
}

int findFirstOccurence(char str[], char aChar){
    for (int l=0; l<30; l++) if (str[l]==aChar) return l;
    return -1;
}

int readInt(char str[], int length){
 int len;
 int i=0;
    while (i < length && str[i] >= '0' && str[i] <= '9') {
        len = len*10 + str[i] - '0';
        i++;
    }
    
    if (i != 0) return len; 
    else return -1;
}

void insertChar(char str[], char aChar, int index){
    int len = strlen(str)+1;
    for (int i=len; i>=index; i--) str[i] = str[i-1];
    str[index] = aChar;
}
    
void replaceChars(char str[], char fromString[], char toChar){
    int len1 = strlen(str);
    int len2 = strlen(fromString);
    
    for (int i=0; i<len1; i++){
        for (int j=0; j<len2; j++){
            if (str[i] == fromString[j]) str[i] = toChar;
        }
    }
}

int main (void){
    int x=0;
    char inputString[LENGTH]={'\0'};
    char inputString1[LENGTH]={'\0'};
    char currString[LENGTH]={'\0'};
    char toChar[LENGTH]={'\0'};
    
    do {
        printf("Command? ");
        readLine(inputString, LENGTH);
        switch (inputString[0]) {
            case 'q':
            printf("Bye!\n");
            break;
            
            case 'p':
            printString(currString);
            break;
            
            case 'a':
            printArray(currString, LENGTH);
            break;
            
            case 's':
            printf("Please enter a string? ");
            readLine(currString, LENGTH);
            break;
            
            case 'o':
            printf("Find first occurrence of which character? ");
            readLine(inputString,2);
            int Occ = findFirstOccurence(currString, inputString[0]);
            printf("The first occurrence of '%c' is at index %d\n", inputString[0], Occ);
            break;
            
            case 'x':
            x = readInt(currString, LENGTH);
            printf("%d\n",x);
            break;
            
            case 'i':
            printf("Insert which character? ");
            readLine(inputString, LENGTH);
            char iChar = inputString[0];
            printf("At what index? ");
            readLine(inputString, LENGTH);
            int index = readInt(inputString, LENGTH);
            insertChar(currString, iChar, index);
            break;
            
            case 'r':
            printf("Replace which characters? ");
            readLine(inputString, LENGTH);
            printf("with which character? ");
            readLine(toChar[0], LENGTH);
            replaceChars(currString, inputString1, toChar[0]);
            break;
            
            default:
            printf("Unknown command '%c'\n", inputString[0]);
            break;
            }
        } 
        while (inputString[0] != 'q');
}

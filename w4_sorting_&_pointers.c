#include <stdio.h>
#include <string.h>

#define LENGTH 100

void printString(char string[]){

    for (int i=0; i<LENGTH; i++){
        if (string[i] == '\0') printf("\\0");
        else printf("%c",string[i]);
    }
    printf("\n");
}

void insertName(char *startPos[], int *nrNames, char newName[]){
    strcpy(startPos[*nrNames],newName);
    startPos[*nrNames+1] = startPos[*nrNames]+strlen(newName)+1;
    *nrNames =  *nrNames+1;
}

void printNames(char names[], char *startPos[], int nrNames){
    int startIndex=0;
    int stringPlusNullLength=0;
    
    for (int i=0; i<nrNames; i++){
        if (i==0) startIndex = 0;
        else startIndex = startPos[i]-names;
        
        stringPlusNullLength = strlen(startPos[i])+1;
        //if (*startPos[i] == '\0') return;
        printf("startPos[%d]=%02d length=%02d string=\"%s\"\n",i,startIndex,stringPlusNullLength,startPos[i]);
    }
}

int totalLength(char *startPos[], int nrNames){
    int unga=0;
    for (int i=0; i<nrNames; i++){
        unga+=strlen(startPos[i])+1;
    }
    return unga;
}

int lookupNamePos(char names[], char *startPos[], int nrNames, char name[]){
    int binary=0;
    int index=-1;
    
    for (int i=0; i<nrNames; i++){
        binary=strcmp(startPos[i],name);
        if (binary==0) index = startPos[i]-names;
        else if (binary==1) index=-1;
        }
    return index;
}

void removeName(char *startPos[], int *nrNames, char remName[]) {
    
    for(int i=0; i < *nrNames; i++){
        if (strcmp(remName, startPos[i])== 0) {
            startPos[i] = startPos[*nrNames-1];
            startPos[*nrNames-1] = startPos[*nrNames];
            (*nrNames) -=1;
            break;
        }
    }
}

void swapNames(char *startPos[], int i, int j){
    //Check to see if input is correct
    // printf("%s\n", startPos[i]);
    // printf("%s\n", startPos[j]);
    
    char *temp;
    
    //Swapping
    temp = startPos[i];
    startPos[i] = startPos[j];
    startPos[j] = temp;
    
    //Check to see if function is correct
    // printf("%s\n", startPos[i]);
    // printf("%s\n", startPos[j]);
}

void insertionSortNames(char *startPos[], int nrNames){
    int i.j;
    
    for (i=1; i<nrNames; i++){
        for (j=i; j>0; j--){
            if (strcmp(startPos[j],startPos[j-1])<0)
                swapNames(startPos, j, j-1);
        }
    }
}

int main(void){
    char cmd;
    int bunga=0;
    int chunga=0;
    char names[LENGTH] = {'\0'};
    int nrNames=0;
    char name[LENGTH] = {'\0'};
    char * startPos[LENGTH] = {names};
    
    int ind1, ind2;
    
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch (cmd){

            case 'q':
            printf("Bye!\n");
            break;
            
            case 'p':
            printString(names);
            break;
            
            case 'i':
            printf("Name? ");
            scanf("%s", name);
            insertName(startPos,&nrNames,name);
            break;
            
            case 'n':
            printNames(names,startPos,nrNames);
            break;
            
            case 'e':
            bunga = totalLength(startPos,nrNames);
            printf("Total length is %d\n",bunga);
            break;
            
            case 'l':
            printf("Name? ");
            scanf(" %s", name);
            chunga = lookupNamePos(names, startPos, nrNames, name);
            printf("\"%s\" has index %d\n",name,chunga);
            break;
            
            case 'r':
            printf("Name? ");
            scanf(" %s", name);
            removeName(startPos,&nrNames, name);
            break;
            
            case 's':
            printf("Indices? ");
            scanf(" %d %d",&ind1,&ind2);
            swapNames(startPos,ind1,ind2);
            
            //Check to see if output is correct
            //printf("%s\n", startPos[ind1]);
            //printf("%s\n", startPos[ind2]);
            break;
            
            case 'o':
            insertionSortNames(startPos, nrNames);
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while (cmd != 'q');
}

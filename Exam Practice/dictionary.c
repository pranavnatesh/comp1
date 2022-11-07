#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXWORDS 10
#define MAXLENGTH 30

int nrWords(char *dict[]){
    int count=0;
    
    for (int i=0; i<MAXWORDS; i++){
        if (dict[i] != NULL) count++;
    }
    return count;
}

void addWord(char *dict[], char word[]){
    
    int fullcheck = nrWords(dict);
    
    if (fullcheck == 10){
        printf("The dictionary is full.\n");
        return;
    }
    
    for (int i=0; i<MAXWORDS; i++){
        if (dict[i] == NULL){
            dict[i] = (char *) malloc ((strlen(word)+1)*sizeof(char));
            strcpy(dict[i],word);
            break;
        }
    }
}

void printDict(char *dict[]){
    
    int emptycheck = nrWords(dict);
    if (emptycheck == 0){
        printf("The dictionary is empty.\n");
        return;
    }
    
    else {
        printf("Dictionary: \n");
        for (int i=0; i<MAXWORDS; i++){
            if (dict[i] !=  NULL){
                printf("- %s\n",dict[i]);
            }
        }
    }
}

int findWord(char *dict[], char word[]){
    int i=0;
 
    while (dict[i] != NULL){
        if (strcmp(dict[i],word)==0){
            return i;
        }
        i++;
    }
    return -1;
}

void removeWord(char *dict[], char word[]){
    
    int index = findWord(dict, word);
    
    if (index ==-1){
        printf("The word \"%s\" is not in the dictionary.\n", word);
        return;
    }
    
    free(dict[index]);
    
    for (int i=index; i<MAXWORDS-1; i++) dict[i]=dict[i+1];
    dict[MAXWORDS-1]=NULL;
}

void swapWords(char *dict[], char word1[], char word2[]){
    
    char *temp;
    int ind1 = findWord(dict, word1);
    int ind2 = findWord(dict, word2);
    
    if (ind1==-1 || ind2==-1){
        printf("Cannot swap words. At least one word is missing in the dictionary.\n");
        return;
    }
    
    else {
        temp = dict[ind1];
        dict[ind1] = dict[ind2];
        dict[ind2] = temp;
    }
}

int longestWord(char *dict[], int from){
    
    int words = nrWords(dict);
    int maxLen = 0;
    int maxInd = 0;
    
    if (dict[0]==NULL || from>=words) return -1;
    
    for (int i=from; i<MAXWORDS; i++){
        if (dict[i] != NULL){
            int len = strlen(dict[i]);
            if(len>maxLen){
                maxLen=len;
                maxInd=i;
            }
        }
    }
    return maxInd;
}

void sortDict(char *dict[], int sortedUntil){
    int n = nrWords(dict);
    int l = longestWord(dict, sortedUntil);
    
    if (n==sortedUntil) return;
    
    if (l!=sortedUntil){
        swapWords(dict, dict[sortedUntil], dict[l]);
        printf("swapped %d and %d\n",l, sortedUntil);
    }
    
    sortedUntil++;
    sortDict(dict, sortedUntil);
}

int main (void){
    char cmd;
    char *dict[MAXWORDS] = {'\0'};
    char word[MAXLENGTH] = {'\0'};
    char word1[MAXLENGTH] = {'\0'};
    
    int nrw;
    int ind;
    int lng;
    
    do {
    printf("Command [qnapfrslo]? ");
    scanf(" %c", &cmd);
    switch(cmd){
        case 'q':
        printf("Bye!\n");
        
        for (int i=0; i<MAXWORDS; i++){
            free(dict[i]);
        }
        return 0;
        break;
        
        case 'n':
        nrw = nrWords(dict);
        printf("The dictionary contains %d words\n", nrw);
        break;
        
        case 'a':
        printf("Word? ");
        scanf(" %s", word);
        addWord(dict, word);
        break;
        
        case 'p':
        printDict(dict);
        break;
        
        case 'f':
        printf("Word? ");
        scanf(" %s", word);
        ind = findWord(dict, word);
        printf("The index of \"%s\" is %d.\n", word, ind);
        break;
        
        case 'r':
        printf("Word? ");
        scanf(" %s", word);
        removeWord(dict, word);
        break;
        
        case 's':
        printf("First word? ");
        scanf(" %s", word);
        printf("Second word? ");
        scanf(" %s", word1);
        swapWords(dict, word, word1);
        break;
        
        case 'l':
        lng = longestWord(dict, 0);
        if (lng==-1) break;
        printf("The longest word in the dictionary is \"%s\".\n", dict[lng]);
        break;
        
        case 'o':
        sortDict(dict,0);
        break;
        
        default:
        printf("Unknown command '%c'\n", cmd);
        break;
        }
    } while (cmd != 'q');
}

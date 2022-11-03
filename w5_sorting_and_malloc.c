#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person {
    char *name;
    float height;
}person;

person *removeAllPersons(struct person *persons, int nrPersons){
    if (persons != NULL) {
    for (int i=0; i<nrPersons; i++){
        if(persons[i].name != NULL){
            free(persons[i].name);
            persons[i].name = NULL;
        }
    }
    free(persons);
    
    }
    return NULL;
}

void printPersons (struct person persons[], int nrPersons, int from, int to){
    int iteration=0;
    
if (persons == NULL){
    printf("[]\n");
    return;
}
    printf("[");
    for (from=0; from<to; from++){
        if (persons[from].name != NULL){ 
            if (iteration>0) printf(",");
            printf("(\"%s\",%.3f)", persons[from].name, persons[from].height);
            iteration++;
        }
    }
    printf("]\n");
}

void insertPerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if (newHeight <= 0){
        printf("Height must be larger than zero\n");
        return;
}
    if (persons[newEntry].name == NULL){
        persons[newEntry].name = (char *) malloc ((strlen(newName)+1)*sizeof(char));
        strcpy (persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
    }
    
    else if (persons[newEntry].name != NULL){
        printf("Entry %d is already occupied by (\"%s\",%.3f)\n",newEntry, persons[newEntry].name, persons[newEntry].height);
    }
}

void replacePerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if (newHeight <= 0){
        printf("Height must be larger than zero\n");
        return;
}
    if (persons[newEntry].name == NULL){
        persons[newEntry].name = (char *) malloc ((strlen(newName)+1)*sizeof(char));
        strcpy (persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
    }

    else if (persons[newEntry].name != NULL){
        free(persons[newEntry].name);
        persons[newEntry].name = (char *) malloc ((strlen(newName)+1)*sizeof(char));
        strcpy (persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
    }
}

void maxHeight (struct person persons[], int nrPersons, float *max){

   *max = persons[0].height;

    for (int i=0; i<nrPersons; i++){
        if (persons[i].height > *max){
           *max = persons[i].height;
        }
    }
    return; 
}

float minHeight (struct person persons[], int nrPersons){
    float min=0;
    int i=0;
    
    while(i<nrPersons){
        if(persons[i].height!=0){
        min=persons[i].height;
        break;
        }
    else i++;
    }
    
    for (int i=0; i<nrPersons; i++){
        if (persons[i].height <= min && persons[i].height != 0){
           min = persons[i].height;
            }
    }
    return min;
}

void merge(struct person persons[], int left, int mid, int right){
    struct person tmp[right-left+1];
    int pos = 0;
    int lpos = left;
    int rpos = mid+1;
    
    while (lpos <= mid && rpos <= right){
        if (persons[lpos].height < persons[rpos].height)
            tmp[pos++] = persons[lpos++];
        else
            tmp[pos++] = persons[rpos++];
    }
    
    while (lpos <= mid) tmp[pos++] = persons[lpos++];
    while (rpos <= right) tmp[pos++] = persons[rpos++];
    // Copy back
    for (int i=0; i < pos; i++) persons[i+left] = tmp[i];
}

/*void merge(struct person persons[], int left, int mid, int right) {
   int lpos, rpos, i;
   int temp[right-left+1];

   for(lpos = left, rpos = mid + 1, i = left; lpos <= mid && rpos <= right; i++) {
      if(persons[lpos].height <= persons[rpos].height)
         temp[i] = persons[lpos++].height;
      else
         temp[i] = persons[rpos++].height;
   }
   
   while(lpos <= mid)    
      temp[i] = persons[lpos++].height;

   while(rpos <= right)   
      temp[i] = persons[rpos++].height;

   for(i = left; i <= right; i++)
      temp[i] = persons[i].height;
      
}*/

void mergeSort(struct person persons[], int left, int right){
    int mid = (left+right)/2;
    if (left < right){
        mergeSort(persons, left, mid);
        mergeSort(persons, mid+1, right);
        merge(persons, left, mid, right);
    }
}

void bubbleSort(struct person persons[], int nrPersons, int* swapped){
    int i, j;
    struct person temp;
    
    int count=0;
    *swapped = 0;
    
    for (i = 0; i < nrPersons-1; i++){
        for (j = 0; j < (nrPersons-i-1); j++){
            if (persons[j].height > persons[j+1].height){
                temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
                (*swapped)++;
                
                printf("after swapping: ");
                printPersons(persons,nrPersons,0,nrPersons);
                //printf("swapcheck=%d\n", (*swapped));
            }
            if (persons[j].height == persons[j+1].height && strcmp(persons[j].name, persons[j+1].name) > 0 ){
                temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
                count++;
                
                printf("after swapping: ");
                printPersons(persons,nrPersons,0,nrPersons);    
                //printf("count=%d\n", countSame);
                }
        }
    }
    (*swapped)+=count;
}




int main(void){
    char cmd;
    person *persons = NULL;
    int nrPersons = 0;
    char name[80]={'\0'};
    float tall=0;
    int index=0;

    float minmin=0;
    float maxmax=0;
    float ranger=0;
    
    int swap=0;
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch(cmd){
            case 'q':
            printf("Bye!\n");
            persons = removeAllPersons(persons, nrPersons);
            return 0;
            break;
            
            case 'n':
            persons = removeAllPersons(persons, nrPersons);
            printf("Entries? ");
            scanf(" %d", &nrPersons);
            
            if (nrPersons == 0) {
                persons = NULL;
                break;
            }
            
            persons = (person*) malloc(nrPersons*sizeof(person));
            
            for (int i=0; i<nrPersons; i++){
              persons[i].name = NULL;
              persons[i].height =0.0;
            }
            
           /*for(int i=0; i <nrPersons; i++){
                printf("nugte[%d].name=%5.1s nugte[%d].height=%5.1f\n",i,persons[i].name,i,persons[i].height);
            }*/
            
            if (persons == NULL) printf("Malloc returned NULL dipshit");
            break;
            
            case 'p':
            printPersons(persons, nrPersons,0,nrPersons);
            break;
            
            case 'i':
            printf("Index? ");
            scanf(" %d", &index);
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %f", &tall);
            
            insertPerson(persons, nrPersons, index, name, tall);
            break;
            
            case 'r':
            printf("Index? ");
            scanf(" %d", &index);
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %f", &tall);

            replacePerson(persons, nrPersons, index, name, tall);
            break; 
            
            case 'h':
            if (persons == NULL){
                printf("Min: %.3f\nMax: %.3f\nRange: %.3f\n", minmin, maxmax, ranger);
                break;
            }
            minmin=minHeight(persons,nrPersons);
            maxHeight(persons,nrPersons,&maxmax);
            ranger = maxmax-minmin;
            printf("Min: %.3f\nMax: %.3f\nRange: %.3f\n", minmin, maxmax, ranger);
            break;
            
            case 'm':
            mergeSort(persons, 0, nrPersons);
            break;
            
            case 'b':
            bubbleSort(persons, nrPersons, &swap);
            printf("Swapped %d times\n", swap);
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while (cmd != 'q');

}

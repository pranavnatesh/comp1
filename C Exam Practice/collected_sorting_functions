/*
COLLECTED SORTING FUNCTIONS
- Week 4: Swap and Insertion sort
- Week 5: Bubble sort
- Books: Swap and Bubble sort
- Dictionary: Recursive sort
*/

/*
WEEK 4 
startPos[] is the array with data that needs to be sorted,
NrNames is the number of entries in the array,
and i and j are the indices to be swapped.
*/

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

/*
WEEK 5
persons[] is the array that needs to be sorted,
nrPersons is the number of entries,
and swapped is the total number of iterations the algorithm makes.
*/

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

/*
Books
Swap function has the same parameters as week 4,
sortBooks uses Bubble Sort, standard format except the swapping is done by calling swapBooks.
*/

void swapBooks(struct book books[], int index1, int index2){
    
    struct book temp = {'\0'};
    temp = books[index1];
    books[index1] = books[index2];
    books[index2] = temp;
    
}

void sortBooks(struct book books[]){
    
    for (int i=0; i<MAXBOOKS; i++){
        for (int j=0; j<MAXBOOKS-i; j++){
            if (books[j].name != NULL && books[j+1].name != NULL){
                if (strcmp(books[j].name, books[j+1].name) > 0){
                    swapBooks(books,j,j+1);
                }
            }
        }
    }
}

/*
Dictionary
Swap is the same excet the indices are not given so they are found by calling a findWord function.
The function sorts until the longest word is at the beginning of the array. 
Longest word returns the index of the longest word.
If the function has gone through the entire array then stop.
the position of the longest word and sortedUntill update every iteration.
*/

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBOOKS 62
#define MAXCATEGORIES 10
#define MAXLENGTH 30

typedef struct book {
    char *name;
    char *categories[MAXCATEGORIES];
    int pages;
}books;


void addBook(struct book books[], char *name, int pages){
    
    for (int i=0; i<MAXBOOKS; i++){
        if (books[i].name==NULL){
            books[i].name = (char *) malloc ((strlen(name)+1)*sizeof(char));
            strcpy(books[i].name, name);
            books[i].pages = pages;
            break;
        }
    }
}

void printBooks(struct book books[]){

    printf("\n");
    
    for (int i=0; i<MAXBOOKS; i++){
        if (books[i].name!=NULL){
            
            printf("Name: %s\n", books[i].name);
            
            printf("Categories: ");
            
            if (books[i].categories[0]==NULL) printf("\n");
            
            for (int j=0; j<MAXCATEGORIES; j++){
                if (books[i].categories[j]!=NULL){
                    printf("%s", books[i].categories[j]);

                    if (books[i].categories[j+1]!=NULL) printf(", ");
                    
                    else printf("\n");
                    }
                }

            printf("Pages: %d\n",books[i].pages);
            printf("\n");
        }
    }
    return;
}

int findBookIndex(struct book books[], char *name){
    
    for (int i=0; i<MAXBOOKS; i++){
        if (books[i].name != NULL){
            if (strcmp(books[i].name, name) == 0) return i;
        }
    }
    return -1;
}

void addCategory(struct book books[], char *name, char *category){
    
    int ind = findBookIndex(books,name);
    if (ind == -1){
        printf("Book not found in library!\n");
        return;
    }
    
    int len = strlen(category)+1;
    for (int i=0; i<MAXCATEGORIES; i++){
        if (books[ind].categories[i]==NULL){
            books[ind].categories[i] = (char *) malloc (len*sizeof(char));
            strcpy(books[ind].categories[i], category);
            break;
        }
    }   
}

void removeBook(struct book books[], char *name){
    
    int ind = findBookIndex(books,name);
    
    free(books[ind].name);
    for (int j=0; j<MAXCATEGORIES; j++) free(books[ind].categories[j]);
    books[ind].pages = 0;
    
    for (int i=ind; books[i].name!=NULL; i++) books[i]= books[i+1];
    
}

void printNamesOfCategories(struct book books[], char *category){
    
    for (int i=0; i<MAXBOOKS; i++){
        if (books[i].name != NULL){
            for (int j=0; j<MAXCATEGORIES; j++){
                if (books[i].categories[j] != NULL){
                    if (strcmp(books[i].categories[j], category) == 0) printf("%s\n",books[i].name);
                }
            }
        }
    }
}

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


int main(void){

    char cmd;

    char name[MAXLENGTH];
    char category[MAXLENGTH];
    int pgs;
    int index;
    
    int ind1;
    int ind2;
    
    struct book books[MAXBOOKS]={'\0'};
    
    for (int i=0; i<MAXBOOKS; i++){
        books[i].name = NULL;  
        (books[i]).pages = 0;
        
        for (int j=0; j<MAXCATEGORIES; j++){
            (books[i]).categories[j] = NULL;    
        }
    }
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){

        case 'q':
        printf("Bye!");
        if (books != NULL) {
        for (int i=0; i<MAXBOOKS; i++){
        if(books[i].name != NULL){
            free(books[i].name);
            books[i].name = NULL;
                }
            }
        }
        return 0;
        break;
        
        case 'a':
        printf("Name? ");
        scanf(" %[^\n]", name);
        printf("Number of pages? ");
        scanf(" %d", &pgs);
        addBook(books,name,pgs);
        break;
        
        case 'p':
        if (books[0].name == NULL){
            printf("The library is empty!\n");
            break;
        }
        printBooks(books);
        break;
        
        case 'f':
        printf("Name? ");
        scanf(" %[^\n]", name);
        index = findBookIndex(books,name);
        if (index == -1){
            printf("Book not found in library!\n"); 
            break;
        }
        printf("Book %s has %d pages.\n", books[index].name, books[index].pages);
        break;
        
        case 'c':
        printf("Name? ");
        scanf(" %[^\n]", name);
        
        index = findBookIndex(books,name);
        if (index == -1){
            printf("Book not found in library!\n");
            break;
        }
        
        printf("Category? ");
        scanf(" %[^\n]", category);
        addCategory(books, name, category);
        break;
        
        case 'r':
        printf("Name? ");
        scanf(" %[^\n]", name);
        index = findBookIndex(books,name);
        if (index == -1){
            printf("%s not found in library.\n", name);
            break;
        }
        removeBook(books, name);
        break;
        
        case 'k':
        printf("Category? ");
        scanf(" %[^\n]", category);
        printNamesOfCategories(books, category);
        break;
        
        case 's':
        printf("Name? ");
        scanf(" %[^\n]", name);
        ind1 = findBookIndex(books,name);
        
        printf("Name? ");
        scanf(" %[^\n]", name);
        ind2 = findBookIndex(books,name);
        
        swapBooks(books,ind1,ind2);
        break;
        
        case 'o':
        sortBooks(books);
        break;
        
        default:
        printf("Unknown command '%c'\n",cmd);
        break;
        
        }
    } while (cmd != 'q');
}

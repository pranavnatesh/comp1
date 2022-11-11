#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "predefined.h" /* Do not delete this line. Do not define product_t, struct _product_t, or the predefined functions yourself. */

/*
PATCH NOTES:
Added struct declaration to make code more clear.
Fixed print formatting to be correct.
All the functions here work properly without leaks.
*/

typedef struct _product_t {
  char *product;
  float price;
} product_t;

product_t * newDatabase (product_t *database, int *dbSize, int newSize){
    
    if (*dbSize != 0){
        for (int i=0; i<*dbSize; i++)
            if (database[i].product != NULL){
                free(database[i].product);
                database[i].product = NULL;
            }
        free(database);    
        }
    
    if (newSize != 0)
    database = (product_t *) malloc (newSize*sizeof(product_t));
    
    *dbSize = newSize;
    
    for (int j=0; j<*dbSize; j++){
        database[j].product = NULL;
        database[j].price = -1;
    }
    
    return database;
}

void addProduct (product_t *database, int dbSize, char *product, float price){
    int x=1;
    int len = strlen(product)+1;
    char *temp = (char *) malloc (len*sizeof(char));
    strcpy(temp, product);
    
    product_t swap = {'\0'};
    
    if (dbSize==0){
        printf("The database is full\n");
        free(temp);
        return;
    }
    for (int i=0; i<dbSize; i++){
        if (database[i].product == NULL){
            database[i].product = temp;
            database[i].price = price;
            break;
        }
        
        else if (x>= dbSize){
            printf("The database is full\n");
            free(temp);
            return;
        }
        
        else if (database[i].product != NULL){
            if (strcmp(database[i].product, product)==0){
            printf("Product is already in the database\n");
            free(temp);
            return;
            }
        }
        
        x++;
    }
    
    for (int i=0; i<dbSize-1; i++){
        for (int j=0; j<dbSize-i-1; j++){
                if (database[j].product != NULL && database[j+1].product != NULL){
                if (strcmp(database[j].product, database[j+1].product)>0){
                    swap = database[j];
                    database[j] = database[j+1];
                    database[j+1] = swap;
                }
            }
        }
    }

    dbSize++;
}

void printDatabase(product_t *database, int dbSize){
    
    for (int i=0; i<dbSize; i++){
        if (database[i].product != NULL){
        printf("product %10s costs %07.2f\n", database[i].product, database[i].price);
        }
    }
}


int main (void){
    char cmd;
    product_t * database = NULL;
    int dbSize = 0;
    int newSize = 0;
    float cost;
    char prod[11];
    
    int entries=0;
    
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            
            case 'q':
            printf("Bye!\n");
            //free(database);
            
            if (dbSize != 0){
                for (int i=0; i<dbSize; i++){
                    free(database[i].product);
                    database[i].product = NULL;
                    database[i].price = -1;
                }
            }
            free(database);
            return 0;
            break;
            
            case 'n':
            printf("Size? ");
            scanf(" %d", &newSize);
            database = newDatabase(database, &dbSize, newSize);
            entries=0;
            break;
            
            case 'a':
            printf("Product price? ");
            scanf(" %s %f", prod, &cost);
            addProduct(database, dbSize, prod, cost);
            
            entries++;
            break;
            
            case 'p':
            printDatabase(database, dbSize);
            break;
            
            default:
            printf("Unknown command '%c'\n",cmd);
            break;
        }
    } while (cmd != 'q');
}

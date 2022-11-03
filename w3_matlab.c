#include <stdio.h>

#define MAXSIZE 10


void print (float matrix[MAXSIZE][MAXSIZE], int rows, int columns, char name){
    printf("Matrix %c (%d X %d):\n", name, rows, columns);
    
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            printf("%8.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

void add (
float matrixA[MAXSIZE][MAXSIZE], 
int rowsA, int columnsA, float matrixB[MAXSIZE][MAXSIZE], 
int rowsB, int columnsB,float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC){ 
    
    for (int i=0; i<rowsC; i++){
            for (int j=0; j<columnsC; j++){
                matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
            }
    }
}

void mult (
float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA,
float matrixB[MAXSIZE][MAXSIZE], int rowsB, int columnsB,
float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC) {

int i=0;
int j =0;
int k=0;
int temp=0;

while (i<rowsA){
    while (j<columnsB){
        while(k<columnsA){
            temp=temp+(matrixA[i][k]*matrixB[k][j]);
            k++;
        }
        matrixC[i][j]=temp;
        temp=0;
        k=0;
        j++;
    }
    j=0;
    i++;
    
    }
}

  /* for (int i = 0; i < rowsA; i++) {
      for (int j = 0; j < columnsB; j++) {
         matrixC = 0;
         for (int k = 0; k < columnsA; k++) {

        }
      }
   }
}*/



int main(void){
    char cmd;
    
    int rijA;
    int kolomA;
    
    float matrixA[MAXSIZE][MAXSIZE]={0};
    float matrixB[MAXSIZE][MAXSIZE]={0};
    float matrixC[MAXSIZE][MAXSIZE]={0};
    float transpose[MAXSIZE][MAXSIZE]={0};
    
    int rowsA=1;
    int columnsA=1;
    int rowsB=1;
    int columnsB=1;
    int rowsC=1;
    int columnsC=1;

    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case 'q':
            printf("Bye!\n");
            break;
            
            case 'a':
            print (matrixA,rowsA,columnsA,'A');
            break;
            
            case 'I':
            printf("Size of matrix A (rows columns)? ");
            scanf(" %d %d", &rijA, &kolomA);
            
            if (rijA != kolomA || rijA > 10 || kolomA > 10 || rijA == 0 || kolomA == 0){
                printf("Rows & columns must be equal and between 1 and 10\n");
                break;
            }
            else{
                rowsA = rijA;
                columnsA = kolomA;
            }
            
            for (int k = 0; k < rowsA; k++) {
                for (int l = 0; l < columnsA; l++) {
                    if (k == l) matrixA[k][l] = 1;
                    else matrixA[k][l] = 0;
                }
            }
            break;
            
            case 'A':
            printf("Size of matrix A (rows columns)? ");
            scanf(" %d %d", &rijA, &kolomA);
            
            if (rijA > 10 || kolomA > 10 || rijA == 0 || kolomA == 0){
                printf("Rows & columns must be between 1 and 10\n");
                break;
            }
            else{
                rowsA = rijA;
                columnsA = kolomA;
            }
            
            for (int m=0; m<rowsA; m++){
                printf("Row %d? ", m);
                for (int n=0; n<columnsA;n++){
                scanf(" %f", &matrixA[m][n]);
                }
            }
            break;
            
            case 'b':
            print (matrixB,rowsB,columnsB,'B');
            break;
            
            case 'c':
            print (matrixC,rowsC,columnsC,'C');
            break;
            
            case 'B':
            rowsB = rowsA;
            columnsB = columnsA;
            
            for (int x=0; x < rowsA; x++){
                for (int y=0; y < columnsA; y++){   
                matrixB[x][y] = matrixA[x][y];
                    }
                }
            break;
            
            case '+':
             if (rowsA == rowsB && columnsA == columnsB){
                rowsC = rowsA;
                columnsC = columnsA;
                //printf("r=%d,c=%d\n", rowsC,columnsC);
                }
    
                else {
                printf("Dimensions of A & B do not match\n");
                break;
                }
            
            add (matrixA,rowsA,columnsA,matrixB,rowsB,columnsB,matrixC,rowsC,columnsC);
            break;
            
            case 't':
            rijA = rowsA;
            kolomA = columnsA;
            
            for (int x=0; x < rowsA; x++){
                for (int y=0; y < columnsA; y++){   
                transpose[x][y] = matrixA[x][y];
                    }
                }
            
              for (int i=0; i<rijA; i++){
                    for (int j=0; j<kolomA; j++){
                        matrixA[j][i]=transpose[i][j];
                        
                    }       
             }
             rowsA = kolomA;
             columnsA = rijA;
             break;
            
            case '*':
            if (columnsA != rowsB){
                printf("Dimensions of A & B do not match\n");
                break;
            }
            else {
                rowsC = rowsA;
                columnsC = columnsB;
                mult (matrixA,rowsA,columnsA,matrixB,rowsB,columnsB,matrixC,rowsC,columnsC);
                break;
            }
            break;
    
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        
        } 
        
    } while (cmd != 'q');
}

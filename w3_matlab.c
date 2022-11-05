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

void printRecursive (float matrixA[MAXSIZE][MAXSIZE],
int rowsA, int columnsA, int currentRow, int currentColumn){
    
    //Enter recursion by printing the current row and column
    printf("enter printRecursive with current row=%d column=%d\n", currentRow, currentColumn);
    
    //If the recursion reaches the last character, print at which position that is
    if (currentRow == rowsA){
        printf("finished the recursion with current row=%d column=%d\n", currentRow, currentColumn);
        return;
    }
    
    //Increment columns before rows. Note that currentColumn++ causes an infinite loop here.
    int nextRow = currentRow;
    int nextColumn = currentColumn+1;

    //Once done imcrementing through columns, increment one row and repeat.
    if (nextColumn == columnsA){
        nextColumn = 0;
        nextRow++;
    }
    //Function call (see explainer below)
    printRecursive (matrixA, rowsA, columnsA, nextRow, nextColumn);
    
    /*Note that this will interrupt the following lines (90 & 91) until the function 
    returns after the stop check is triggered a when the recursion should eventually stop.
    
    Then the compiler will return to line 79 on the "return-1"th fucntion where it will
    execute line 90 & 91. When that is complete, it will return to the "return-2"th function
    and will repeat this process until the first iteration of the function has executed fully.
    
    This is why the print exit statement prints in reverse, because the first function call
    is the last to actually be executed by the compiler!*/
    
    printf("%8.2f\n", matrixA[currentRow][currentColumn]);
    printf("exit printRecursive with current row=%d column=%d\n", currentRow, currentColumn);
}


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
            
            case 'p':
            printRecursive(matrixA,rowsA,columnsA,0,0);
            break;
    
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        
        } 
        
    } while (cmd != 'q');
}

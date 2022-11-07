#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define START 'S'
#define DESTINATION 'D'
#define PATH '+'
#define WALL '#'
#define UNSEEN '.'
#define SEEN '~'

typedef struct {
    int x;
    int y;
} position_t;

typedef struct {
    char *grid;
    int maxX;
    int maxY;
} navigation_t;

int max(int a, int b){
    if (a > b)
        return a;
    else
        return b;
}

void newGrid(navigation_t *nav){
    int tempX;
    int tempY;
    
    printf("Number of rows? ");
    scanf(" %d", &tempY);
    printf("Number of columns? ");
    scanf(" %d", &tempX);
    
    if (tempX < 2 || tempY < 2){
        printf("The number of rows and columns must be at least two\n");
        return;
    }
    
    else{
        (*nav).maxX = tempX;
        (*nav).maxY = tempY;
    }
    
    if ((*nav).grid != NULL){
        free((*nav).grid);
        (*nav).grid = NULL;
        (*nav).grid = (char * ) malloc (((*nav).maxX*(*nav).maxY) * sizeof(char));
    }
    
    else (*nav).grid = (char * ) malloc (((*nav).maxX*(*nav).maxY) * sizeof(char));
}

void inputGrid(navigation_t nav){
    char input = '\0';
    int rows = nav.maxY;
    int columns = nav.maxX;
    int SPcounter=0;
    
    for (int i=0; i<rows; i++){
        printf("Input row %d: ", i);
        for (int j=0; j<columns; j++){
            scanf(" %c", &input);
            if (input == 'S'){
                SPcounter++;
                if (SPcounter > 1){
                    input='#';
                    printf("Extra starting point\n");
                    SPcounter--;
                }
            }
            nav.grid[(i*columns)+j] = input;
        }
    }
}

void printGrid(navigation_t nav){
    int prows = nav.maxY;
    int pcolumns = nav.maxX;
    
    for (int i=0; i<prows; i++){
        for (int j=0; j<pcolumns; j++){
            printf("%c",nav.grid[(i*pcolumns)+j]);
            if (j==pcolumns-1) printf("\n");
        }
    }
}

position_t findStart(navigation_t nav){
    position_t pos;
    int frows = nav.maxY;
    int fcolumns = nav.maxX;
    int SCounter=0;
    int DCounter=0;
    
    for (int i=0; i<frows; i++){
        for (int j=0; j<fcolumns; j++){
            if (nav.grid[(i*fcolumns)+j] == 'S'){
                SCounter++;
                pos.x=j;
                pos.y=i;
            }
            else if (nav.grid[(i*fcolumns)+j] == 'D') DCounter++;
        }
    }
    
    if (SCounter == 0){
        printf("Grid contains no starting point\n");
        pos.x = -1;
        pos.y = -1;
    }
    
    if (DCounter == 0){
        printf("Grid contains no destination\n");
        pos.x = -1;
        pos.y = -1;
        return pos;
    }
    return pos;
}

int findPath(navigation_t nav, int x, int y, int length){
    int nlength;
    int elength;
    int slength;
    int wlength;
    
    if (x > nav.maxX-1 || x<0 || y>nav.maxY-1 || y<0) return 0;
    if (nav.grid[(y*nav.maxX)+x] == WALL) return 0;
    if (nav.grid[(y*nav.maxX)+x] == PATH) return 0;
    if (nav.grid[(y*nav.maxX)+x] == START && length > 0) return 0;
    if (nav.grid[(y*nav.maxX)+x] == DESTINATION) return length;
    
    //mark x,y as part of solution path (if x,y isn’t the start)
    if (nav.grid[(y*nav.maxX)+x] != START) nav.grid[(y*nav.maxX)+x] = PATH;
    
    // try to find a path in North, East, South, and West directions
    // note the clever use of = instead of ==
    // the extra brackets are to avoid a warning
    
        if ((nlength = findPath(nav,x,y-1,length+1))) return nlength;
        if ((elength = findPath(nav,x+1,y,length+1))) return elength;
        if ((slength = findPath(nav,x,y+1,length+1))) return slength;
        if ((wlength = findPath(nav,x-1,y,length+1))) return wlength;
        
    // if we get here we didn’t find a solution in N,E,S, or W directions
    
    //mark x,y as seen (if x,y isn’t the start)
    if (nav.grid[(y*nav.maxX)+x] != START) nav.grid[(y*nav.maxX)+x] = SEEN;
    return 0;
}

void resetPath(navigation_t nav){
    int frows = nav.maxY;
    int fcolumns = nav.maxX;
    
     for (int i=0; i<frows; i++){
        for (int j=0; j<fcolumns; j++){
            if (nav.grid[(i*fcolumns)+j] == PATH || nav.grid[(i*fcolumns)+j] == SEEN) nav.grid[(i*fcolumns)+j] = UNSEEN;
        }
    }
}

int main(void){
    char cmd;
    
    navigation_t nav;
    nav.grid = NULL;
    nav.maxX = 0;
    nav.maxY = 0;
    
    position_t pos1;
    pos1.x=0;
    pos1.y=0;
    
    int fx=0;
    int fy=0;
    int len=0;

    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch(cmd){
            case 'q':
            printf("Bye!\n");
            free(nav.grid);
            return 0;
            break; 
            
            case 'i':
            newGrid(&nav);
            inputGrid(nav);
            break; 
            
            case 'p':
            printGrid(nav);
            break;
            
            case 's':
            pos1=findStart(nav);
            if (pos1.x != -1 && pos1.y != -1) printf("The start is at x=%d and y=%d\n", pos1.x, pos1.y);
            break;
            
            case 'f':
            //Find Start and initialise coordinates
            len=0;
            pos1=findStart(nav);
            fx=pos1.x;
            fy=pos1.y;
            
            //Find the path, and print the length which is returned
            len=findPath(nav,fx,fy,len);
            
            //If no path is found, print a warning and then the grid
            if (len == 0){
                printf("No path found\n");
                printGrid(nav);
                break;
            }
            
            //Otherwise print path length and the new grid
            else{
                printf("Found a path of length %d\n", len);
                printGrid(nav);
            }
            break;
            
            case 'r':
            resetPath(nav);
            break;

            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while (cmd != 'q');
}

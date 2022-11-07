#include <stdio.h>

int main (void){
    
printf("** Complex Calculator **\n");

char cmd;
float curr_re = 0;
float curr_im = 0;
float new_re = 0;
float new_im = 0;

int n;
int factor;

while (cmd != 'q'){

printf("Operation [0+-*crpq]? ");
scanf(" %c", &cmd);

    if (cmd == 'q'){
    
    if (curr_im>=0){
    printf("Current value is %f+%fi\n", curr_re, curr_im);
    }
    
    else printf("Current value is %f%fi\n", curr_re, curr_im);
    
    printf("Bye!\n");
    return 0;
        }
    
    else if (cmd == '+'){
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
        curr_re += new_re;
        curr_im += new_im;
    }
    
    else if (cmd == '-'){
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
        curr_re -= new_re;
        curr_im -= new_im;
    }
    
    else if (cmd == '0'){
        curr_re = 0;
        curr_im = 0;
    }
    
    else if (cmd == 'c'){
        curr_im = -curr_im;
    }
    
    else if (cmd == '*'){
        printf("Complex operand? ");
        scanf(" %f %f", &new_re, &new_im);
        float temp_re = curr_re*new_re - curr_im*new_im;
        float temp_im = curr_re*new_im + curr_im*new_re;
        
        curr_re = temp_re;
        curr_im = temp_im;
    }

    else if (cmd == 'r'){
        printf("Natural operand? ");
        scanf(" %d", &n);
        float temp_re = curr_re;
        float temp_im = curr_im;
        
        if (n == 0){
            curr_re = 1;
            curr_im = 0;
        }
        
        else if (n > 0){
            for (int i=1; i<n; i++){
                
                factor = curr_re;
                curr_re = curr_re*temp_re - curr_im*temp_im;
                curr_im = temp_re*curr_im + factor*temp_im;
            }
    }
}

     else if (cmd == 'p'){
        int plot_re = curr_re;
        int plot_im = -curr_im;
            for (int y=-10; y<=10; y++){
                for (int x=-10; x<=10; x++){
                    if (plot_re == x && plot_im == y){
                        printf("*");
                        }
                    else if (x == 0 && y == 0){
                        printf("+");
                        }
                    else if (x == 0){
                        printf("|");
                        }
                    else if (y == 0){
                        printf("-");
                        }
                    else {
                        printf(".");
                        }
                    }
                printf("\n");
            }
    }  



    
    else if (cmd != 'q'){
    printf("Invalid command '%c'\n", cmd);
        }

    if (curr_im>=0){
    printf("Current value is %f+%fi\n", curr_re, curr_im);
    }
    else printf("Current value is %f%fi\n", curr_re, curr_im);
    }
}

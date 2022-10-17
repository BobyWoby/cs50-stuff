#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do{

        height = get_int("Height: ");
    }
    while(height < 1 || height >= 9);
    int width = height;
    for(int i = 0; i < height; i++){

        for(int j = 0; j < height *2 + 1; j++){
            //creates the space between the staircases
            if(j == height){
                printf("  ");
            }
            //makes the left staircase
            else if(j <= width-2){
                printf(" ");
            }
            //makes the right staircase
            else if(j >= -1 * width+(2*height + 2)){
                printf("");
            }
            //prints the bricks
            else{
                 printf("#");
            }
        }
        width--;
        printf("\n");
    }


}
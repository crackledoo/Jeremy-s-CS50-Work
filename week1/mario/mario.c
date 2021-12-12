#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for height
    int height;
    do
    {
        height = get_int("Pyramid height: ");
    }
    while (height < 1 || height > 8);

//Initialize stats
    int c = 0;
    int h = height;

//Opener
    while (c < height)
    {
        int s = h - 1;
        int b = c+1;

//Space feature 1
        while (s>0)
        {
            printf(" ");
            s--;
        }
//Brick feature 1
        while (b>0)
        {
            printf("#");
            b--;
        }
//Midspace!
        printf("  ");

//Brick feature 2
        while (b < ( c + 1 ))
        {
            printf("#");
            b++;
        }

//Closure (don't we all need some?)
    c++;
    h--;
    printf("\n");
    }
}
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int sp;
    do
    {
        sp = get_int("Starting population: ");
    }
    while (sp < 9);

    // Prompt for end size
    int ep;
    do
    {
        ep = get_int("Ending population: ");
    }
    while (ep < sp);

    // Calculate number of years to reach threshold
    int t = 0;
    while (sp < ep)
    {
        sp = sp + ((sp / 3) - (sp / 4));
        t++;
    }

    // Print number of years
    printf("Years: %i\n", t);

}


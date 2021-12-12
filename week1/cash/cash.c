#include <stdio.h>
#include <cs50.h>
#include <math.h>

float cash;
int owe;
int c = 0;
void quarter(void);
void dime(void);
void nickel(void);
void penny(void);

int main(void)
{
//Acquire number
    do
    {
        cash = get_float("Cash owed: ");
    }
    while (cash < 0);
//Rounding
    owe = round(cash * 100);
//Counting coins
    while (owe >= 25)
    {
        quarter();
    }
    while (owe >= 10)
    {
        dime();
    }
    while (owe >= 5)
    {
        nickel();
    }
    while (owe >= 1)
    {
        penny();
    }
//Statement
    printf("%i\n", c);
}

void quarter(void)
{
    owe -= 25;
    c++;
}

void dime(void)
{
    owe -= 10;
    c++;
}

void nickel(void)
{
    owe -= 5;
    c++;
}

void penny(void)
{
    owe -=1;
    c++;
}
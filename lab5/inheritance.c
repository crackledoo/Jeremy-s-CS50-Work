// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    //Allocate memory for new person
    person *n = malloc(sizeof(person));
    if (n == NULL)
    {
        printf("Memory allocation error\n");
        return n;
    }
    generations--;
    // Generation with parent data
    if (generations >= 1)
    {
        // Recursively create blood type histories for parents
        for (int i = 0; i < 2; i++)
        {
            person *p = create_family(generations);
            n->parents[i] = p;
            // Randomly assign child alleles based on parents
            n->alleles[i] = p->alleles[rand() % 2];
        }

    }

    // Generation without parent data
    else
    {
        // Randomy assign grandmost parent alleles
        for (int i = 0; i < 2; i++)
        {
            n->parents[i] = NULL;
            n->alleles[i] = random_allele();
        }
    }

    //Return youngest person
    return n;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    if (p == NULL)
    {
        printf("Person location error\n");
        return;
    }
    //Handle base case
    else if (p->parents[0] == NULL)
    {
        free(p);
    }
    //Recursivley free parents
    else
    {
        for (int i = 0; i < 2; i++)
        {
            free_family(p->parents[i]);
        }
        //Free person
        free(p);
    }
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

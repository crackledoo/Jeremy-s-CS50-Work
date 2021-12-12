#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair aux[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cylock(int w, int l, int c);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int k = 0; k < candidate_count; k++)
    {
        int m = ranks[k];
        for (int l = k + 1; l < candidate_count; l++)
        {
            int n = ranks[l];
            preferences[m][n]++;
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int p = 0;
    for (int k = 0; k < candidate_count; k++)
    {
        for (int l = k + 1; l < candidate_count; l++)
        {
            if (preferences[k][l] > preferences[l][k])
            {
                pairs[p].winner = k;
                pairs[p].loser = l;
                p++;
            }
            else if (preferences[k][l] < preferences[l][k])
            {
                pairs[p].winner = l;
                pairs[p].loser = k;
                p++;
            }
        }
    }
    pair_count = p;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //I tried to perform a merge sort for eons with no luck
    //This is instead ripped from a stackoverflow answer. I am ashamed.
    int strength[pair_count];
    for (int i = 0; i < pair_count - 1; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    while (1)
    {
        int c = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {

            for (int j = i+1; j < pair_count; j++)
            {
                if (strength[i] < strength [j])
                {
                    pair temp = pairs[i];
                    pairs [i] = pairs[j];
                    pairs[j] = temp;

                    int temp2 = strength[i];
                    strength[i] = strength[j];
                    strength[j] = temp2;
                    c++;
                }
            }
        if (c == 0)
        {
            break;
        }
        }
    return;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count -1; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        if (!cylock(w, l, 0))
            {
                locked[w][l] = true;
            }
    }
    return;
}

//Home attempt at recursive cycle-check
bool cylock(w, l, c)
{
    c++;
    //Quit
    return false;
    if (c > pair_count)
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[l][i] == true)
        {
            if (cylock(l, i, c) == false)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;

        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            int w = 0;
            if (locked [i][j])
            {
                for (int k = 0; k < pair_count; k++)
                {
                    if (locked [k][i])
                        w++;
                }
            }
            if (w == 0)
            {
                printf("%s", candidates[i]);
            }

        }
    }
    return;
}


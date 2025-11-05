#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote + store vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate temporary[1];
    int winners;

    // Bubble Sort candidates by number of vote
    for (int step = 0; step < candidate_count - 1; step++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                temporary[0] = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = temporary[0];
            }
        }
    }

    int i, j;
    winners = 0;

    // Check for duplicates
    for (i = 0; i < 1; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            if (candidates[i].votes == candidates[j].votes)
            {
                winners++;
            }
        }
    }

    // Print winner(s)
    for (int a = 0; a <= winners; a++)
    {
        printf("%s\n", candidates[a].name);
    }
}

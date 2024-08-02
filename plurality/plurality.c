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

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
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
        if (!vote(name))
        {
            printf("Invalid Candidate\n");
        }
        else
        {
            printf("Vote Counted\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int vote_counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            vote_counter++;
        }
    }
    if (vote_counter != 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(candidates[i].name, candidates[j].name) != 0)
            {
                if (candidates[i].votes > candidates[j].votes)
                {
                    int temp = candidates[j].votes;
                    candidates[j].votes = candidates[i].votes;
                    candidates[i].votes = temp;
                    string temps = candidates[j].name;
                    candidates[j].name = candidates[i].name;
                    candidates[i].name = temps;
                }
            }
        }
    }
    int highest_votes = candidates[0].votes;
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes == highest_votes)
        {
            printf("%s\n", candidates[k].name);
        }
    }

    return;
}

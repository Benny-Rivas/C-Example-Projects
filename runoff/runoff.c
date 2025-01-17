#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int valid_vote_counter = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            valid_vote_counter++;
            preferences[voter][rank] = i;
            break;
        }
    }

    if (valid_vote_counter != 1)
    {
        printf("Invalid Vote\n");
        return false;
    }
    else
    {
        return true;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int pref_tab = 0;
        bool voted = false;
        while (!voted)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if (preferences[i][pref_tab] == j && candidates[j].eliminated == false)
                {
                    candidates[j].votes++;
                    voted = true;
                    break;
                }
                else if (preferences[i][pref_tab] == j && candidates[j].eliminated == true)
                {
                    while (!voted)
                    {
                        pref_tab++;

                        for (int l = 0; l < candidate_count; l++)
                        {
                            if (preferences[i][pref_tab] == l && candidates[l].eliminated == false)
                            {
                                candidates[l].votes++;
                                voted = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int whos_left = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            whos_left++;
        }
    }
    int score_array[whos_left];
    int score_index = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            score_array[score_index] = candidates[i].votes;
            score_index++;
        }
    }

    for (int k = 0; k < whos_left; k++)
    {
        for (int i = 0; i < whos_left; i++)
        {
            if (score_array[i + 1] != score_array[whos_left])
            {
                if (score_array[i] < score_array[i + 1])
                {
                    int temp = score_array[i];
                    score_array[i] = score_array[i + 1];
                    score_array[i + 1] = temp;
                }
            }
        }
    }

    return score_array[whos_left - 1];
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int whos_left = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            whos_left++;
        }
    }
    int tie_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            tie_count++;
        }
    }
    if (tie_count == whos_left)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

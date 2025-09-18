#include <cs50.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[voter][rank] is candidate index
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

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
    // Check for usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum candidates is %i\n", MAX_CANDIDATES);
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
        printf("Maximum voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query each rank for voter i
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, if invalid print and exit with message for this vote
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                // j-- or continue? We follow CS50's expected behaviour: don't let them re-enter
                // rank here. The distribution code expects an "Invalid vote." message and continues
                // to next rank/voter.
            }
        }
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Tabulate votes for non-eliminated candidates
        tabulate();

        // Check if election has a winner
        if (print_winner())
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone remaining is a winner
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
        // Repeat
    }

    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // For every voter, add vote to their highest-ranked non-eliminated candidate
    for (int i = 0; i < voter_count; i++)
    {
        for (int r = 0; r < candidate_count; r++)
        {
            int cand = preferences[i][r];
            if (!candidates[cand].eliminated)
            {
                candidates[cand].votes++;
                break;
            }
            // otherwise continue to next preference
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = voter_count / 2; // need strictly greater than this
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes for any remaining candidate
int find_min(void)
{
    int min_votes = INT_MAX;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if all non-eliminated candidates have the same vote count
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate all candidates who have min votes
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

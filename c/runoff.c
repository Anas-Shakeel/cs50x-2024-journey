/*
Runoff.c

In This Problem, we are going to implement another elections technique/system
called "Ranks Preference Voting".

In Plurality, each voter got to vote for only one candidate, in runoff, voters
can rank all of the candidates in sequence.

Ranked preference ballot:
_______
:vote :
: 1.  :
: 2.  :
: 3.  :
:_____:

Voters vote for all the candidates and rank them.
So if "candidate 1" doesn't win, their next preference would be "candidate 2",
and if "candidate 2" doesn't win also, their next preference would
be "candidate 3" and so on!

Runoff Vote:
    - every voter ranks their preferences (1st, 2nd, 3rd, ....)
    - If a candidate has a majority (more than the half) of the votes,
        they are the winner.
    - Otherwise eliminate the candidate with the fewest votes and re-run
        the elections without them.
    - Keep repeating that process until someone wins a majority of votes.

 */

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
    /*
    ? TODO ?
    - Look for a candidate called name
    - If candidate found, Update 'preferences' so that they are the `voter's` `rank` pref. & return True
    - If no candidate found, don't update any preferences and return False
     */

    // Iterate through the candidates & look for `name` candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Candidate found! proceed...
            // Store the index of candidate in pref[voter_num][rank]
            preferences[voter][rank] = i;

            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    /*
    Update vote counts for all non-eliminated candidates (Candidates[].votes)
    "Recall that each voter votes for their highest preference candidate who
    has not yet been eliminated."

    Go-through each of the voters & update the vote counts of candidates,
        - making sure to only update vote count for non-eliminated candidates
    */

    int preference; // whom did the voter voted for...
    // Iterate through Candidates
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Update the vote counts
            preference = preferences[i][j]; // store the preference
            if (!candidates[preference].eliminated)
            {
                candidates[preference].votes++; // increase voter's preference's votes
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    /*
    Print who winner of the elections, if there is a a winner yet!

    - If any candidate has more than half the vote,
        print out their name and return true.
    - If nobody has yet won the election! return False
    */

    int half_votes = voter_count / 2; // votes needed to win the election
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > half_votes)
        {
            // Won the election
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    /*
    Return the minimum number of votes of anyone who is still in election

    */
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            // Votes are less, update (store the lesser votes)
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    /*
    Accept the minimum number of votes `min` as input
    - Return `true`:
        - if the election is tied between all of the remaining candidates
        - return `false` otherwise

    FOR THE ELECTION TO BE CONSISIDERED AS TIE!
        every (non-eliminated) candidate must have the same number of votes
    */

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                // Not a tie (votes aren't same)
                return false;
            }
        }
    }

    // It is a tie!
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    /*
    Eliminate anyone still in race who has the `min` number of votes.
     */

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && (candidates[i].votes == min))
        {
            // Eliminate the candidate[i]
            candidates[i].eliminated = true;
        }
    }

    return;
}

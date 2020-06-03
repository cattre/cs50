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

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
/*
int ranks[9][3] =
{
    {0,1,2},
    {0,1,2},
    {0,1,2},
    {1,2,0},
    {1,2,0},
    {2,0,1},
    {2,0,1},
    {2,0,1},
    {2,0,1}
};
*/
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

//        record_preferences(ranks[i]); // temp

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
//            printf("preference %i:%i = %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
//                printf("if, pairs %i winner: %i loser: %i\n", pair_count, pairs[pair_count].winner, pairs[pair_count].loser);
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
//                printf("else, pairs %i winner: %i loser: %i\n", pair_count, pairs[pair_count].winner, pairs[pair_count].loser);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp_pair;

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] >
            preferences[pairs[i].winner][pairs[i].loser])
            {
                temp_pair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp_pair;
//                printf("if\n");
            }
//            printf("sorted pairs %i: %i:%i\n", i, pairs[i].winner,pairs[i].loser);
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
//        printf("i: %i\n", i);
        bool is_winner = false;

        for (int j = i - 1; j >= 0; j--)
        {
//            printf("j: %i\n", j);
//            printf("%i winner: %i, %i loser: %i\n", i, pairs[i].loser, j, pairs[j].winner);
            if (pairs[i].loser == pairs[j].winner)
            {
//                printf("match\n");
                for (int k = j - 1; k >= 0; k--)
                {
//                    printf("k: %i\n", k);
                    if (pairs[k].loser == pairs[i].winner)
                    {
                        is_winner = true;
//                        printf("true\n");
                    }
                }
            }
        }
        if (!is_winner)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
//            printf("locked winner: %i locked loser: %i\n", pairs[i].winner, pairs[i].loser);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;

    for (int i = 0; i < candidate_count; i++)
    {
        bool is_loser = false;
        
        for (int j = 0; j < pair_count;  j++)
        {
//            printf("pair %i locked: %d\n", j, locked[pairs[j].winner][pairs[j].loser]);
            if (locked[pairs[j].winner][pairs[j].loser] == true
            && pairs[j].loser == i)
            {
                is_loser = true;
                break;
            }
        }
        if (is_loser == false)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
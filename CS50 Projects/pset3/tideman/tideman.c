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
    int margin;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void store_pairs(int win, int lose);
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
    printf("\nPreferences-------------\n");
    for (int i = 0; i < candidate_count; i++) // tests if "record_references" functions properly
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\nPaired-------------\n");
    add_pairs();
    for (int l = 0; l < pair_count; l++) // tests if pairs are created properly
    {
        printf("winner: %i, loser: %i, margin: %i\n", pairs[l].winner, pairs[l].loser, pairs[l].margin);
    }
    printf("\nSorted-------------\n");
    sort_pairs();
    for (int o = 0; o < pair_count; o++) // tests that pairs are sorted in decreasing order of strength
    {
        printf("winner: %i, loser: %i, margin: %i\n", pairs[o].winner, pairs[o].loser, pairs[o].margin);
    }
    printf("\nLocked-------------\n");
    lock_pairs();
    for (int m = 0; m < pair_count; m++) // tests that locked pairs are created correctly
    {
        for (int n = 0; n < pair_count; n++)
        {
            printf("%d ", locked[m][n]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote ---------------------------------
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

// Update preferences given one voter's ranks -----------------------
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other --------------------
void add_pairs(void)
{
    // The function should add all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
    // The function should update the global variable pair_count to be the number of pairs of candidates. (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).

    for (int r = 0; r < candidate_count; r++)
    {
        for (int c = 0; c < candidate_count; c++)
        {
            if (r == c || preferences[r][c] == 0) break;
            if (preferences[r][c] > preferences[c][r])
            {
                store_pairs(r,c);
            }
            else if (preferences[c][r] > preferences[r][c])
            {
                store_pairs(c,r);
            }
        }
    }
    return;
}

// assist add_pairs in creating the pairs, populates pairs array with preferences data --------------------------------
void store_pairs(int win, int lose)
{
    pairs[pair_count].winner = win;
    pairs[pair_count].loser = lose;
    pairs[pair_count].margin = preferences[win][lose] - preferences[lose][win];
    pair_count++;
}

// Sort pairs in decreasing order by strength of victory ------------------------------------
void sort_pairs(void)
{
    // The function should sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.

    int index = 0;
    for (int i = 0; i < pair_count - 1; i++)
    {
        pair temp = pairs[i];
        bool replace = false;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (temp.margin < pairs[j].margin)
            {
                replace = true;
                temp = pairs[j];
                index = j;
            }
        }
        if (replace)
        {
            pairs[index] = pairs[i];
            pairs[i] = temp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles (used "sorted" instead of "pairs") ---------------------
void lock_pairs(void)
{
    // The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.
    // locked[i][j] means i is locked in over j
    // locked starts fully true (all zeros)

    // lock in pairs in order of strength
    // run pair_count number of times
    // cannot lock in pairs such that all of the pairs are j's

    for (int i = 0; i < pair_count - 1; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election ------------------------
void print_winner(void)
{
    // The function should print out the name of the candidate who is the source of the graph. You may assume there will not be more than one source.
    // TODO

    // iterate through the layers of locked
    // whatever layer is never a j of another is the winner
    int congrats = 0;
    int possible[candidate_count];
    for (int k = 0; k < candidate_count; k++)
    {
        possible[k] = k;
    }
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (i == j || locked[i][j] == true)
            {
                continue;
            }
            for (int l = 0; l < candidate_count; l++) // remove the j from the possible array of winners
            {
                if (possible[l] == locked[i][j])
                {
                    possible[l] = -1;
                }
            }
        }
    }
    for (int m = 0; m < candidate_count; m++)
    {
        if (possible[m] < 0)
        {
            continue;
        }
        else
        {
            congrats = possible[m];
            break;
        }
    }
    printf("%s\n", candidates[congrats]);
    return;
}

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    int total = 0;
    int character;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        // convert word to uppercase
        if (isupper(word[i]))
        {
            character = word[i];
        }
        else
        {
            character = toupper(word[i]);
        }
        // take the ASCII value of individual chars and subtract by 65 to get position in points array
        // add the points values together
        if (character >= 65 && character <= 90)
        {
            total += POINTS[character - 65];
        }
    }
    return total;
}

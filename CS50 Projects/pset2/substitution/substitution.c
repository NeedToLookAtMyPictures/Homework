#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void make_cipher(string text, string cipher);
bool is_valid(string key);

int main(int argc, string argv[])
{
    if (argc != 2) // user isn't cooperating
    {
        printf("./substitution key\n");
        return 1;
    }
    else
    {
        if (strlen(argv[1]) != 26) // key must be 26 chars long
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else // actual code body
        {
            if (is_valid(argv[1])) // executes if key only has letters
            {
                string plain = get_string("plaintext: ");
                make_cipher(plain, argv[1]);
                printf("ciphertext: %s\n", plain);
                return 0;
            }
            else
            {
                printf("Please only use alphabetical characters in the key without any copies\n");
                return 1;
            }
        }
    }
}

bool is_valid(string key)
{
    for (int i = 0, l = strlen(key); i < l; i++)
    {
        if (key[i] < 65 || (key[i] > 90 && key[i] < 97) || key[i] > 122)
        {
            return false;
        }
        // make sure there aren't any duplicate characters in a semi-valid key
        for (int j = i + 1, le = strlen(key); j < le; j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}

void make_cipher(string text, string cipher)
{
    int swap;
    // determine ASCII value of text[i] if upper subtract 65 to get relative cipher character, if lower subtract 97
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            if (isupper(text[i])) // minus 65
            {
                swap = (text[i] - 65);
                text[i] = toupper(cipher[swap]);
            }
            else // minus 97
            {
                swap = (text[i] - 97);
                text[i] = tolower(cipher[swap]);
            }
        }
    }
}

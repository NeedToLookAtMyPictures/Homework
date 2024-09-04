#include <cs50.h>
#include <stdio.h>
#include <string.h>
// https://cs50.harvard.edu/x/2023/psets/1/credit/

string get_card(long num);
void is_fraudulent(long check);

string card = "";

int main(void)
{
    // input credit card number
    long number = 0;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);
    card = get_card(number);

    // determine if fraudulent
    if (strcmp(card, "INVALID") == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        is_fraudulent(number);
    }
}

string get_card(long num)
{
    // determine length of num
    int len = 0;
    long temp = num;
    for (int i = 0; temp > 0; i++)
    {
        temp /= 10;
        len++;
    }

    // determine if starting digits are valid for card issuer
    if ((len == 13 && num / 1000000000000 == 4) || (len == 16 && num / 1000000000000000 == 4))
    {
        return "VISA";
    }
    else if ((len == 16) && (num / 100000000000000 == 51 || num / 100000000000000 == 52 || num / 100000000000000 == 53 ||num / 100000000000000 == 54 || num / 100000000000000 == 55))
    {
        return "MASTERCARD";
    }
    else if ((len == 15) && (num / 10000000000000 == 34 || num / 10000000000000 == 37))
    {
        return "AMEX";
    }
    else
    {
        return "INVALID";
    }
}

void is_fraudulent(long check) // broken not adding correctly on some cards
{
    // iterate up check
    // multiply odd chars by 2 and add to a temp
    // add even chars to a temp
    int odd = 0;
    int even = 0;
    int temp = 0;
    int count = 0;
    while (check > 0)
    {
        temp = check % 10;
        check = check / 10;
        if (count % 2 == 0) // even
        {
            if (temp >= 10)
            {
                even += temp % 10;
                temp = temp / 10;
                even += temp;
            }
            else
            {
                even += temp;
            }
        }
        else // odd
        {
            temp *= 2;
            if (temp >= 10)
            {
                even += temp % 10;
                temp = temp / 10;
                even += temp;
            }
            else
            {
                even += temp;
            }
        }
        temp = 0;
        count++;
    }
    if ((even + odd) % 10 == 0)
    {
        printf("%s\n", card);
    }
    else
    {
        printf("INVALID\n");
    }
}

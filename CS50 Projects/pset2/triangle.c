#include <cs50.h>
#include <stdio.h>


bool triangle_valid(int legs[]);

int main(void)
{
    // get side lengths, ensure positivity
    int sides[3];
    for(int i = 0; i < 3; i++)
    {
        do
        {
            sides[i] = get_int("What is the length of a side of the triangle? ");
        }
        while (sides[i] < 0);
    }
    if(triangle_valid(sides) == 0)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
}


// checks that no one side is greater than the others summated
bool triangle_valid(int legs[])
{
    if (legs[1] + legs[2] <= legs[3] || legs[2] + legs[3] <= legs[1] || legs[1] + legs[3] <= legs[2])
    {
        return true;
    }
    else
    {
        return false;
    }
}

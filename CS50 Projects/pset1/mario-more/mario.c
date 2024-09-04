#include <cs50.h>
#include <stdio.h>

int get_height(void);
void make_pyramid(int height);

int main(void)
{
    // user decides height of pyramid
    int height = get_height();
    // construct pyramid in layers
    make_pyramid(height);
}

int get_height(void)
{
    int h;
    do
    {
        h = get_int("What is the height of the pyramid? ");
    }
    while (h <= 0 || h > 8);
    return h;
}

void make_pyramid(int height)
{
    // same num of layers as height
    for (int r = 0; r < height; r++)
    {
        // adds spaces to right side hashes
        for (int sp = 0; sp < height - r - 1; sp++)
        {
            printf(" ");
        }
        // layers increase in size as i increases
        for (int cr = height - r - 1; cr < height; cr++)
        {
            printf("#");
        }
        printf("  ");
        // layers equivalent to r plus one
        for (int cl = 0; cl < r + 1; cl++)
        {
            printf("#");
        }
        printf("\n");
    }
}

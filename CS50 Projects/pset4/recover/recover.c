#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./recover _.jpg\n");
        return 1;
    }

    if (argv[1] == NULL)
    {
        printf("File cannot be read\n");
        return 1;
    }

    //Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("File cannot be opened\n");
        return 1;
    }

    uint8_t buffer[BLOCK];

    char *filename = malloc(8 * sizeof(char));

    FILE *img;

    int counter = 0;
    bool writing = false;
    while(fread(buffer, 1, 512, card) == 512)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //start of jpg
        {
            if (counter == 0) //first jpg
            {
                sprintf(filename, "%03i.jpg", counter); //create jpg
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                fclose(img); //close previous jpg
                sprintf(filename, "%03i.jpg", counter); //create jpg
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            counter++;
        }
        else
        {
            if(counter > 0)
            {
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                continue;
            }
        }
    }
    fclose(img);
    fclose(card);
    free(filename);
}

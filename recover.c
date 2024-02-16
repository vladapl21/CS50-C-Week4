#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];

    char filename[8] = {0};

    // While there's still data left to read from the memory card
    int counter = 0;
    FILE *img = NULL;
    while (fread(buffer, sizeof(uint8_t) * 512, 1, card) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03d.jpg", counter++);
            img = fopen(filename, "w");
        }

        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t) * 512, 1, img);
        }
    }
    // close last opened img
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}

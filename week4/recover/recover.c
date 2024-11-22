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
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    FILE *output = NULL;
    char filename[8];
    int jpeg_count = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if block starts with JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG if exists
            if (output != NULL)
            {
                fclose(output);
            }

            // Create new JPEG file
            sprintf(filename, "%03i.jpg", jpeg_count);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                fclose(card);
                return 1;
            }
            jpeg_count++;
        }

        // Write block to output file if JPEG is open
        if (output != NULL)
        {
            fwrite(buffer, 512, 1, output);
        }
    }

    // Close remaining files
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(card);
    return 0;
}

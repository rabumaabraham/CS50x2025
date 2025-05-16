#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for correct command-line usage
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create buffer to store blocks
    uint8_t buffer[BLOCK_SIZE];

    // File pointer for recovered JPEGs
    FILE *img = NULL;

    // Filename buffer
    char filename[8]; // e.g., "000.jpg"

    // Image counter
    int img_count = 0;

    // Flag for whether we're currently writing an image
    int writing = 0;

    // Read the card file block by block
    while (fread(buffer, BLOCK_SIZE, 1, input) == 1)
    {
        // Check for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a JPEG, close it
            if (writing)
            {
                fclose(img);
            }

            // Create new JPEG file
            sprintf(filename, "%03i.jpg", img_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output file.\n");
                fclose(input);
                return 1;
            }

            fwrite(buffer, BLOCK_SIZE, 1, img);
            writing = 1;
            img_count++;
        }
        else if (writing)
        {
            // Continue writing to current JPEG
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(input);
    return 0;
}

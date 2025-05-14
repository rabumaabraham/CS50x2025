#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for pyramid height until valid input is given
    do
    {
        // Prompt for the height
        printf("Height: ");
        // Check if input is an integer and store it in the variable 'height'
    } while (scanf("%d", &height) != 1 || height < 1 || height > 8);

    // Loop to print each row of the pyramid
    for (int i = 1; i <= height; i++)
    {
        // Print leading spaces
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Print hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Newline after each row
        printf("\n");
    }

    return 0;
}

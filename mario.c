// Build two sided pyramid with gap

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int height = 0;
    // Checks for correct user input
    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }
    // Iterates over rows
    for (int i = 0; i < height; i++)
    {
        // Prints leading spaces based on row
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // Prints left hand hashes based on row
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        // Prints right hand hashes based on row
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
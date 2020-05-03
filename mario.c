// Build a right aligned half pyramid

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    // Prompts user until integer between 1 and 8 entered
    while (height < 1 || height > 8)
    {
        height = get_int("Height:");
    }
    // Iterates through rows
    for (int i = 0; i < height; i++)
    {
        // Prints leading spaces based on row number
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // Prints hashes based on row number
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
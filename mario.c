#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height=0;
    while(height<1 || height>8)
    {
        height = get_int("Height:");
    }
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<height-i-1; j++)
        {
            printf(" ");
        }
        for(int k=0; k<i+1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
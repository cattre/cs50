#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    int h = get_positive_int("Height: ");
    
    for(int i=0; i<h; i++)
    {
        for(int k=i; k<h-1; k++)
        {
                printf(" ");
        }
        for(int j=0; j<i+1; j++)
        {
            printf("#");
        }
        
        printf(" ");
        
        for(int j=0; j<i+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// get positive integer
int get_positive_int (string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n<1 || n>8);
    return n;
}

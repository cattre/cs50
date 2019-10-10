#include <stdio.h>
#include <cs50.h>
#include <math.h>

float gpf(string prompt);

int main(void)
{
    float dollars = gpf("Change owed:");
    int cents = round(dollars*100);
    int q = cents/25; // Number of quarters
    int d = (cents%25)/10; // Number of dimes
    int n = ((cents%25)%10)/5; // Number of nickels
    int c = (((cents%25)%10)%5);
    printf("%i\n",q+d+n+c);
}

float gpf(string prompt)
{
    float f;
    do
    {
        f = get_float("%s",prompt);
    }
    while (f<0);
    return f;
}
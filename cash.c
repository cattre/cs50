// Returns number of coins in change
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Prompts user for change needed
    float dollars = get_float("Change owed: ");
    int cents = round(dollars * 100);
    // Gets number of quarters
    int coins = cents / 25;
    // Gets remaining change
    int left = cents % 25;
    // Adds number of dimes
    coins = coins + left / 10;
    // Gets remaining change
    left = left % 10;
    // Adds number of nickels
    coins = coins + left / 5;
    //Gets remaining change
    left = left % 5;
    // Adds number of cents
    coins = coins + left / 1;
    printf("%i\n", coins);
}
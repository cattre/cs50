// Checks if credit card number is a valid format

#include <stdio.h>
#include <cs50.h>
#include <math.h>

string get_card_type(long cardNo);

int main(void)
{
    int checksum = 0;
    int a;
    int b;
    int c;

    long cardNo = get_long("Number: ");
    string type = get_card_type(cardNo);

    // Iterates through card number from right to left
    for (long i = 100; i < cardNo * 100; i *= 100)
    {
        // Gets every second digit and multiplies by 2
        a = ((cardNo % i) / (i / 10)) * 2;
        // Checks if result is two digits and splits if so
        if (a > 9)
        {
            b = a % 10;
            a = a / 10;
        }
        else
        {
            b = 0;
        }
        // Gets every other digit
        c = ((cardNo % (i / 10)) / (i / 100));
        checksum = checksum + a + b + c;
    }
    // Checks that last digit is 0
    if (checksum % 10 == 0)
    {
        printf("%s\n", type);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Gets card number and checks for correct format
string get_card_type(long cardNo)
{
    string type;
    long am_len = 10000000000000; // AMEX 15 digit card number
    long mc_len = 100000000000000; // MasterCard 16 digit card number
    long v_len1 = 1000000000000; // VISA 13 digit card number
    long v_len2 = 1000000000000000; // VISA 16 digit card number

    // Checks for 15 digit numbers starting 34 or 37
    if (cardNo / am_len == 34 || cardNo / am_len == 37)
    {
        type = "AMEX";
    }
    // Checks for 16 digit numbers starting 51, 52, 53, 54 or 55
    else if (cardNo / mc_len == 51 || cardNo / mc_len == 52
             || cardNo / mc_len == 53 || cardNo / mc_len == 54
             || cardNo / mc_len == 55)
    {
        type = "MASTERCARD";
    }
    // Checks for 13 or 16 digit numbers starting 4
    else if (cardNo / v_len1 == 4 || cardNo / v_len2 == 4)
    {
        type = "VISA";
    }
    else
    {
        type = "INVALID";
    }

    return type;
}
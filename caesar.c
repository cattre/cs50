#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

void encrypt_text(int key, string text);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage ./caesar key\n");
    }
    else
    {
        // Converts second argument to integer
        int key = atoi (argv[1]);
        // Checks that key is numeric and greater than 0
        if (key < 1)
        {
            printf("Usage: ./caesar key");
        }
        else
        {
            string plaintext = get_string("plaintext: ");
            encrypt_text(key, plaintext);
        }
    }
}

void encrypt_text(int key, string text)
{
    printf("ciphertext: ");
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        char c = text[i];
        if (c >= 'A' && c <= 'Z')
        {
            if ((c + key) / 'Z' > 0)
            {
                c = ((c + key) % 'Z') + 'A' - 1;
            }
            else
            {
                c = (c + key);
            }
        }
        else if (c >= 'a' && c <= 'z')
        {
            if ((c + key) / 'z' > 0)
            {
                c = ((c + key) % 'z') + 'a' - 1;
            }
            else
            {
                c = (c + key);
            }
        }
        printf("%c", c);
    }
    printf("\n");
}
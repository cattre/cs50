#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt_text(int key, string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    else
    {
        // Converts second argument to integer
        int keynum = atoi(argv[1]);

        // Checks that key is numeric and greater than 0
        string key = argv[1];
        for (int i = 0, j = strlen(key); i < j; i++)
        {
            if (isdigit(key[i]) == false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        string plaintext = get_string("plaintext: ");
        encrypt_text(keynum, plaintext);
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
            if ((c + key) > 'Z')
            {
                c = ((c + key - 'Z') % 26) + 'A' - 1;
            }
            else
            {
                c = (c + key);
            }
        }
        else if (c >= 'a' && c <= 'z')
        {
            if ((c + key) > 'z')
            {
                c = ((c + key - 'z') % 26) + 'a' - 1;
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
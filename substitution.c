#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_key(string key);
void encrypt_text(string key, string text);

int main(int argc, string argv[])
{
    // Checks that a single key has been provided
    if (argc != 2)
    {
        printf("Single key not provided\n");
        return 1;
    }

    string key = argv[1];
    int check = check_key(key);
    if (check == 1)
    {
        return 1;
    }

    // Prompts user for plaintext
    string plaintext = get_string("plaintext: ");
    encrypt_text(key, plaintext);
}

// Checks for valid key
int check_key(string key)
{
    int keylen = strlen(key);

    // Iterates through characters in key
    for (int i = 0; i < keylen; i++)
    {
        char kchar = key[i];

        // Checks character is alphabetic
        if (!isalpha(kchar))
        {
        printf("Key is not alphabetic\n");
        return 1;
        }

        // Checks characters only used once
        for (int j = 0; j <= keylen; j++)
        {
            char kchar2 = key[j];
            int count = 0;

            if (kchar == kchar2)
            {
                count++;
                if (count > 1)
                {
                    printf("Characters used more than once in key\n");
                    return 1;
                }
            }
        }
    }

    // Checks that key is 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    return 0;
}

// Encrypts plaintext using key and prints ciphertext
void encrypt_text(string key, string text)
{
    printf("ciphertext: ");
    // Iterates through characters in plaintext
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        char pchar = text[i];
        int pint = 0;
        // Substitutes uppercase characters with key
        if (pchar >= 'A' && pchar <= 'Z')
        {
            pint = pchar - 'A';
            pchar = toupper(key[pint]);
        }
        // Substitutes lowercase characters with key
        else if (pchar >= 'a' && pchar <= 'z')
        {
            pint = pchar - 'a';
            pchar = tolower(key[pint]);
        }
        printf("%c", pchar);
    }
    printf("\n");
}
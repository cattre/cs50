#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void encrypt_text(string key, string text);

int main(int argc, string argv[])
{
    // Checks that a single key has been provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string key = argv[1];
    // Checks that key is 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Iterates through characters in key to check all are alphabetic
    for (int i = 0, j = strlen(key); i < j; i++)
    {
        if (!isalpha(key[i]))
        {
        printf("Usage: ./substitution key\n");
        return 1;
        }
    }
    // Prompts user for plaintext
    string plaintext = get_string("plaintext: ");
    encrypt_text(key, plaintext);
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
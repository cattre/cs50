// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2000;

// Hash table
node *table[N];

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *loadedDict = fopen(dictionary, "r");
    if (loadedDict == NULL)
    {
        return false;
    }

    while (true)
    {
        char word[LENGTH + 1] = "";
        char ch;
            
        // Loop for maximum possible characters
        for (int i = 0; i < LENGTH + 1; i++)
        {

            // Get next character
            ch = fgetc(loadedDict);

            // Stop if end of file reached
            if (ch == EOF)
            {
                break;
            }

            // Check for newline
            if (ch == '\n')
            {
                // Create a node and allocate a memory position
                node *n = malloc(sizeof(node));
                if (n == NULL)
                {
                    return false;
                }
                n->next = NULL;

                // Apply hash function
                int index = hash(word);

                // Store node if hash index is free
                if (table[index] == NULL)
                {
                    // Store node in hash index
                    table[index] = n;
                }
                else
                {
                    // Find first free position to store node
                    node *tmp = table[index];
                    while (tmp != NULL)
                    {
                        if (tmp->next == NULL)
                        {
                            tmp->next = n;
                            break;
                        }
                        else
                        {
                            tmp = tmp->next;
                        }
                    }
                }

                // Store word in node
                for (int j = 0; word[j] != '\0'; j++)
                {
                    n->word[j] = word[j];
                    n->word[j + 1] = '\0';
                }
                break;
            }

            // Write character to temp word array
            word[i] = ch;
        }

        // Stop if end of file reached
        if (ch == EOF)
        {
            break;
        }
    }

    // Close dictionary file
    fclose(loadedDict);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashResult = 0;

    // Iterate through letters
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashResult += word[i] * (i + 1);
    }

    if (hashResult > N)
    {
        hashResult %= N;
    }

    return hashResult;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    // Iterate though table array
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            count++;
            node *tmp = table[i];
            while (tmp->next != NULL)
            {
                count++;
                tmp = tmp->next;
            }
        }
    }

    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char lowercase[strlen(word)];

    // Convert to lowercase
    for (int i = 0; i <= strlen(word); i++)
    {
        lowercase[i] = tolower(word[i]);
    }

    // Apply hash function
    int index = hash(lowercase);
    node *tmp = table[index];

    while (tmp != NULL)
    {
        // Check if word found at location
        if (!strcmp(tmp->word, lowercase))
        {
            return true;
        }
        // Go to next location
        else
        {
            tmp = tmp->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i <= N; i++)
    {
        // Assign node to current table index
        node *n = table[i];

        while (n != NULL)
        {
            node *tmp = n->next;
            // Free previous node
            free(n);
            // Assign next address to n
            n = tmp;
        }
    }
    return true;
}

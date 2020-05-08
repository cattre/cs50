#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

void count(string text);
float LETTERS = 0;
float WORDS = 0;
float SENTENCES = 0;

int main(void)
{
    int index;
    float s;
    float l;
    string text = get_string("Text: ");
    count(text);
    // Calculates letters per 100 words
    l = (LETTERS / WORDS) * 100;
    // Calculates sentences per 100 words
    s = (SENTENCES / WORDS) * 100;
    // Coleman-Liau index calculation
    index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counts letters, words and sentences from text input
void count(string text)
{
    // Iterates through characters in string
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        // Increases letter count if character is a letter
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            LETTERS++;
        }
        // Increases word count if character is a space
        if (text[i] == ' ')
        {
            WORDS++;
        }
        // Increases sentence count if character is end punctation
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            SENTENCES++;
        }
    }
    // Increases word count by 1 to count final word
    if (LETTERS > 0)
    {
        WORDS++;
    }
}
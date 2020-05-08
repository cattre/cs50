#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

void count(string text);
float LETTERS=0;
float WORDS=0;
float SENTENCES=0;

int main(void)
{
    int index;
    float s;
    float l;
    string text = get_string("Text: ");
    count(text);
    l = (LETTERS / WORDS) * 100;
    s = (SENTENCES / WORDS) * 100;
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

void count(string text)
{
    for (int i=0, j=strlen(text); i<j; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            LETTERS++;
        }
        if (text[i] == ' ')
        {
            WORDS++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            SENTENCES++;
        }
    }
    if (LETTERS>0)
    {
        WORDS++;
    }
}
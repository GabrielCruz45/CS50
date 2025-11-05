#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int readability(string text);
void print_grade_level(int grade);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Determine readability grade
    int grade = readability(text);

    // Output grade level
    print_grade_level(grade);
}

int readability(string text)
{
    float letters = 0.0, words = 0.0, sentences = 0.0;

    // Check each individual char from "string-array"
    for (int i = 0; text[i] != 0; i++)
    {
        // Check if char is a letter
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    words++;

    // L is average number of letter per 100 words
    float L = letters / words * 100;

    // S number of sentences per 100 words
    float S = sentences / words * 100;

    // Coleman-Lieau index
    double index = (0.0588 * L) - (0.296 * S) - 15.8;

    // Round index
    int grade = round(index);

    // Output grade
    return grade;
}

void print_grade_level(int grade)
{
    // Check input variable and print grade level
    if (grade > 0 && grade < 17)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

    return;
}

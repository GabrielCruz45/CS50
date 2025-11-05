#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int command_line_input_check(int argc, string key);
void cipher_the_text(string key, char plaintext[], int text_length);

int main(int argc, string argv[])
{
    int a = argc;
    string key = argv[1];

    // Check for input errors
    if (command_line_input_check(argc, key) > 0)
    {
        printf("Wrong command-line argument!");
        return 1;
    }

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    int b = strlen(plaintext);

    // printf("%s, %s, %i\n", key, plaintext, b);

    // Creat cipher text based on key and plaintext and print
    cipher_the_text(key, plaintext, b);

    // Newline
    printf("\n");
    // End program
    return 0;
}

int command_line_input_check(int argc, string s)
{
    char c, d;
    int i;
    // printf("%i\n%s\n", argc, key);

    // Check if command-line input is correct and output error message
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY \n");
        return 1;
    }
    else if (strlen(s) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check for non-alphabetic characters
    for (i = 0; s[i] != 0; i++)
    {
        c = s[i];
        // printf("%c\n", c);

        if (isalpha(c) == 0)
        {
            printf("Key must contain only alphabetical characters.\n");
            return 1;
        }
    }

    // Check for duplicate characters
    for (i = 0; s[i + 1] != 0; i++)
    {
        c = s[i];

        for (int j = 0 + i; s[j + 1] != 0; j++)
        {
            d = s[j + 1];

            if (tolower(c) == tolower(d))
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // If no errors are present
    return 0;
}

void cipher_the_text(string key, string plaintext, int text_length)
{
    // Declare variables
    char ciphertext[text_length];
    char c;
    int a;

    // Check char by char of string input
    for (int i = 0; plaintext[i] != 0; i++)
    {
        // Check if letter
        if (isalpha(plaintext[i]))
        {
            // Check if upper case
            if (isupper(plaintext[i]))
            {
                // Explicitly convert char to int & figure out postion in abcs (1 - 26)
                a = (int) plaintext[i] - 65;

                // Change plaintext char to ciphertext char
                c = key[a];

                // Change to uppercase if needed
                c = toupper(c);

                // Input cipher char to ciphertext string
                ciphertext[i] = c;
            }

            else // if (islower(plaintext[i]))
            {
                // Explicitly convert char to int & figure out postion in abcs (1 - 26)
                a = (int) plaintext[i] - 97;

                // Change plaintext char to ciphertext char
                c = key[a];

                // Change to uppercase if needed
                c = tolower(c);

                // Input cipher char to ciphertext string
                ciphertext[i] = c;
            }
        }

        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Output ciphertext
    printf("ciphertext: %s", ciphertext);

    return;
}

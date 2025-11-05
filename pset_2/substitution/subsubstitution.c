#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(void)
{
    char key[26] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

    char c, d;
    int i;
    //Check for duplicate characters
    for (i = 0; key[i + 1] != 0; i++)
    {
        c = key[i];
        printf("%c\n", c);

        for (int j = 0 + i; key[j + 1] != 0; j++)
        {
            d = key[j + 1];
            printf("%c\n", d);

            printf("%c = %c ?\n", c, d);

            if (c == d)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    //If no errors are present
    return 0;
}
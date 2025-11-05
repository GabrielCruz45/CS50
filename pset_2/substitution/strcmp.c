#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //string s[26] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};
    //string t[26] = {q, w, e, r, t, y, u, i, o, p, a, s, d, f, g, h, j, k, l, z, x, c, v, b, n, m};


    string plaintext = get_string("plaintext: ");//'QWERTYUIOPASDFGHJKLZXCVBNM';
    string key = get_string("Key: ");
    int b = strlen(plaintext);

    char ciphertext[b];

    //Declare variables
    char c;
    int a;

    //Check char by char of string input
    for (int i = 0; plaintext[i] != 0; i++)
    {
        //Check if letter
        if (isalpha(plaintext[i]))
        {
            //Check if upper case
            if (isupper(plaintext[i]))
            {
                //Explicitly convert char to int & figure out postion in abcs (1 - 26)
                a = (int) plaintext[i] - 65;

                //Change plaintext char to ciphertext char
                c = key[a];

                //Change to uppercase if needed
                c = toupper(c);

                //Input cipher char to ciphertext string
                ciphertext[i] = c;
            }

            else //if (islower(plaintext[i]))
            {
                //Explicitly convert char to int & figure out postion in abcs (1 - 26)
                a = (int) plaintext[i] - 97;

                //Change plaintext char to ciphertext char
                c = key[a];

                //Change to uppercase if needed
                c = tolower(c);

                //Input cipher char to ciphertext string
                ciphertext[i] = c;
            }
        }

        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    //Output ciphertext
    printf("%s\n", ciphertext);

}
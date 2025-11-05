#include <cs50.h>
#include <math.h>
#include <stdio.h>

long user_prompt(void);
int checksum(long card, int decimal);
string check_card_type(long card, int decimal_places);
void validation_print(string card_type, int validity);
int how_many_decimal_places(long n);

int main(void)
{
    // Prompt user for input (get_long)
    long card = user_prompt();

    // Check decimal places
    int decimal_places = how_many_decimal_places(card);

    // Checksum Algorithm
    int validity = checksum(card, decimal_places);

    // Check Card length and digits
    string card_type = check_card_type(card, decimal_places);

    // Print AMEX, VISA, MASTERCARD or INVALID
    validation_print(card_type, validity);
}

long user_prompt(void)
{
    long n = get_long("Number: ");
    return n;
}

int checksum(long card, int decimal)
{
    int checksum, suma_pares = 0, suma_impares = 0, o, par;
    int w, x, y, z;
    long a, b, m;

    for (int i = 0; i < decimal; i++)
    {
        a = pow(10, i);
        b = pow(10, i + 1);

        m = card % a;

        o = ((card % b) - m) / a;

        // Pares
        if ((i + 1) % 2 == 0)
        {
            par = o * 2;

            if (par > 9)
            {
                for (int j = 0; j < 2; j++)
                {
                    x = pow(10, j);
                    y = pow(10, j + 1);

                    w = par % x;

                    z = ((par % y) - w) / x;

                    suma_pares += z;
                }
            }
            else
            {
                suma_pares += par;
            }
        }
        // Impares
        else
        {
            suma_impares += o;
        }
    }

    // Suma de pares e impares
    checksum = suma_pares + suma_impares;

    // Checksum
    if (checksum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string check_card_type(long card, int decimal_places)
{
    string invalid = "INVALID", visa = "VISA", mastercard = "MASTERCARD", american_express = "AMEX";

    // VISA
    if (decimal_places == 13)
    {
        int check_digits = card / pow(10, 12);
        if (check_digits == 4)
        {
            return visa;
        }
        else
        {
            return invalid;
        }
    }
    // AMEX
    else if (decimal_places == 15)
    {
        int check_digits = card / pow(10, 13);
        if (check_digits == 34 || check_digits == 37)
        {
            return american_express;
        }
        else
        {
            return invalid;
        }
    }
    // MASTERCARD OR VISA
    else if (decimal_places == 16)
    {
        int check_digits = card / pow(10, 14);
        if (check_digits > 50 && check_digits < 56)
        {
            return mastercard;
        }
        else if (check_digits > 39 && check_digits < 50)
        {
            return visa;
        }
        else
        {
            return invalid;
        }
    }
    // INVALID
    else
    {
        return invalid;
    }
}

void validation_print(string card_type, int validity)
{
    if (validity == 1)
    {
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int how_many_decimal_places(long n)
{
    int counter = 0;
    float check = 0;
    long power_of_ten = pow(10, counter);

    do
    {
        check = n / power_of_ten;
        counter++;
        power_of_ten = pow(10, counter);
    }
    while (check > 1);

    counter--;

    return counter;
}

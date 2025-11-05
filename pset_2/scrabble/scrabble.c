#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    char c;
    int a, b, score = 0;

    // Se va char por char del string
    for (int i = 0; word[i] != 0; i++)
    {
        // Se verifica si es una letra
        if (isalpha(word[i]))
        {
            // Se verifica si es mayúscula o minúscula y se convierte en mayúscula
            c = toupper(word[i]);
            // Se convierte el char en int
            a = (int) c;
            // Se computa para comparar letra con Points[]
            b = a - 65;
            // Se extrae la puntuación de la letra y se añade al score
            score += POINTS[b];
        }
    }
    // Output score of word
    return score;
}

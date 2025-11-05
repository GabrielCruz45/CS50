#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_blocks(int usuario);

int main(void)
{
    // Get size of grid.
    int n = get_size();

    // Prints grid of bricks
    print_blocks(n);
}

// It's has no input so "void" is used;
// the format for declaring functions is
// 'output type  name of function(input)'
int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while ((8 < n) || (n < 1));
    return n; // return will output the value
}

// No tiene un data type como output so se utiliza el 'void'
void print_blocks(int usuario)
{

    // **Filas**
    for (int fila = 0; fila < usuario; fila++)
    {
        int g = fila;

        // Empieza a imprimir **Columna**
        while (usuario > g + 1)
        {
            printf(" ");
            g++;
        }

        // Se imprime la primera sección de 'bloques' de acuerdo a la fila
        for (int i = 0; fila >= i; i++)
        {
            printf("#");
        }

        // Espacios entre medio
        printf("  ");

        // Segunda sección de bloques'
        for (int j = 0; fila >= j; j++)
        {
            printf("#");
        }

        // Cambio de fila
        printf("\n");
    }
}

// const int n = 3; // const makes it so that it can't be changed from here on; it's a feature of C

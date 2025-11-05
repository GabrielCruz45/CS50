#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get user input (user's name) and store on variable
    string name = get_string("What's your name? ");

    // print on console "hello, (name)"
    printf("\nhello, %s\n", name);

    // return 0 if successful run
    return 0;
}

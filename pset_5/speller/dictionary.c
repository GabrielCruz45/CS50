// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N][LENGTH + 1];

// Global nodes array check
bool initialization_check[N][LENGTH + 1];

// Global Variable for size function
unsigned int global_counter = 0;

// Populate initialization_check array
void populate_initialization_check_array(void)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            initialization_check[i][j] = false;
        }
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word), word_length = strlen(word);

    if (initialization_check[index][word_length] == false)
    {
        return false;
    }

    if (word_length == 0 || word_length > 46)
    {
        return false;
    }

    if (strcasecmp(table[index][word_length]->word, word) == 0)
    {
        return true;
    }
    else
    {
        node *cursor;

        cursor = table[index][word_length];

        while (cursor->next != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }

            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file_pointer = fopen(dictionary, "r");
    if (file_pointer == NULL)
    {
        printf("Could not open file successfully!\n");
        fclose(file_pointer);
        return false;
    }

    char *temporary_string = (char *) malloc((sizeof(char) * LENGTH) + 1);
    if (temporary_string == NULL)
    {
        printf("Error allocating memory!\n");
        free(temporary_string);
        return false;
    }
    int index, word_length;

    // Copy word from file to temporary string array
    while (fscanf(file_pointer, "%s", temporary_string) != EOF)
    {
        global_counter++;

        // Create new_node and check for error
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Error creating new_node!");
            free(new_node);
            return false;
        }

        // Populate new_node; Copy word from temporary string variable to new node
        strcpy(new_node->word, temporary_string);
        new_node->next = NULL; // It's good practice to initialize empty pointers to NULL.

        index = hash(new_node->word);
        word_length = (strlen(new_node->word));

        if (initialization_check[index][word_length] != false)
        {
            new_node->next = table[index][word_length]->next;
            table[index][word_length]->next = new_node;
        }
        else
        {
            initialization_check[index][word_length] = true;
            table[index][word_length] = new_node;
        }
    }

    fclose(file_pointer);

    free(temporary_string);
    temporary_string = NULL;

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (global_counter == 0)
    {
        return 0;
    }
    else
    {
        return global_counter;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;

    // Traverse table/inizialization_check in x direction
    for (int i = 0; i < N; i++)
    {
        // Traverse table/inizialization_check in y direction
        for (int j = 0; j <= LENGTH + 1; j++)
        {
            // You only free have to free memory you've allocated
            if (initialization_check[i][j] == true)
            {
                cursor = table[i][j];

                // 2 scenarios:
                // 1. The linked list has more than 2 nodes; free those up
                if (cursor->next != NULL)
                {
                    while (cursor->next != NULL)
                    {
                        tmp = cursor;
                        free(tmp);
                        cursor = cursor->next;
                    }

                    // When you've reached the end of the linked list, free that last node
                    tmp = cursor;
                    free(tmp);
                    tmp = NULL;
                }
                // 2. The linked list has only one node; free that only node
                else
                {
                    tmp = cursor;
                    free(tmp);
                    tmp = NULL;
                }
            }
        }
    }

    return true;
}

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
bool  loaded = false;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    if (table[hash(word)] == NULL) {
        return false;
    }
    
    char word_copy[LENGTH + 1];
    strcpy(word_copy, word);
    // Convert word to uppercase
    for (int i = 0; word_copy[i]; i++) {
        word_copy[i] = toupper(word_copy[i]);
    }
    
    for (node *it = table[hash(word)]; it != NULL; it = it->next) {
        char dict_word[LENGTH + 1];
        strcpy(dict_word, it->word);
        // Convert dictionary word to uppercase
        for (int i = 0; dict_word[i]; i++) {
            dict_word[i] = toupper(dict_word[i]);
        }
        
        if (strcmp(dict_word, word_copy) == 0) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash << 2) ^ toupper(word[i]);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) {
        loaded = false;
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF) {
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            loaded = false;
            return false;
        }
        strcpy(n -> word, word);
        n -> next = table[hash(word)];
        table[hash(word)] = n;
    }
    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!loaded) {
        return 0;
    }
    else {
        int count = 0;
        for (int i = 0; i < N; i++) {
            for (node *it = table[i]; it != NULL; it = it->next) {
                count++;
            }
        }
        return count;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (!loaded) {
        return false;
    }
    for (int i = 0; i < N; i++) {
        while (table[i] != NULL) {
            node *tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
    }
    loaded = false;
    return true;
}
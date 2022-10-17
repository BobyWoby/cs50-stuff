// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define BLOCK_SIZE 1220
//245
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 677;
int dictionarySize = 0;

// Hash table
node *table[N];

bool list_push(node *head, char word[]);
int getLength(node *head);

void free_list(node *node);
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    char *tmp = malloc((LENGTH + 1) *(sizeof(char)));
    for(int i = 0; i < strlen(word); i++){
        tmp[i] = '\0';
        tmp[i] = tolower(word[i]);
    }
    tmp[strlen(word)] = '\0';
    node *current = table[index];
    while(current != NULL){
        if(strcmp(current->word, tmp) == 0){
            free(tmp);
            return true;
        }
            current = current->next;
    }
    free(tmp);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    int hash = 0;

    hash = 26 * (toupper(word[0]) - 'A');
    if(isalpha(word[1])){
        hash += toupper(word[1]) - 'A';
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if(file == NULL){
        return false;
    }
    char word[LENGTH + 1];
    while(fscanf(file, "%s", word) != EOF){
        unsigned int hashVal = hash(word);
        node *newNode = malloc(sizeof(node));
        if(newNode == NULL){
            return false;
        }
        strcpy(newNode->word, word);

        node *head = malloc(sizeof(node));
        if(head == NULL){
            table[hashVal] = newNode;
            dictionarySize++;
        }
        else{
            newNode->next = table[hashVal];
            table[hashVal] = newNode;
            dictionarySize++;
        }
        //free(newNode);
        free(head);
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    while (table[i] != NULL)
    {
        node *tmp = table[i] ->next;
        free(table[i]);
        table[i] = tmp;
    }
    return true;
}

void free_list(node *node){
    if(node->next == NULL){
        free(node);
    }
    else{
        free_list(node->next);
    }
}

// bool list_push(node *head, char word[]) {
//     node *current = head;
//     while(current->next != NULL) {
//         current = current->next;
//     }
//     /* now we can add a new variable */
//     current->next = malloc(sizeof(node));
//     if(current->next == NULL){
//         free(current);
//         return false;
//     }
//     for(int i = 0; i < strlen(word);i++){
//         current->next->word[i] = word[i];
//     }
//     current->next->next = NULL;
//     free(current);
//     return true;
// }

// int getLength(node *head){
//     int count = 0;
//     node *temp = head;
//     while(temp != NULL){
//         temp = temp->next;
//         count++;
//     }

//     return count;
// }

//      if(table[hashVal] == NULL){
    //         table[hashVal] = malloc(sizeof(node));
    //         if(table[hashVal] == NULL){
    //             unload();
    //             return false;
    //         }
    //         strcpy(table[hashVal]->word, word);
    //         table[hashVal]->next = NULL;
    //         dictionarySize++;
    //     }
    //     else{
    //         node *tmp = malloc(sizeof(node));
    //         if(tmp == NULL){
    //             unload();
    //             return false;
    //         }
    //         strcpy(tmp->word, word);
    //         tmp->next = table[hash(word)];
    //         table[hash(word)] = tmp;
    //         char empty[LENGTH + 1];
    //         strcpy(word, empty);
    //     }
    // }
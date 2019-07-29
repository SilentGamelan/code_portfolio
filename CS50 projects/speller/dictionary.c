/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// declaring as global, as unable to modify speller.c in order to call and pass pointer
trie *root = NULL;
// similarly here, no elegant way of counting words without simply calling another function which recursively 
// traverses trie a la destroy_tries()
unsigned int wcount = 0;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    trie *trav = root;
    char c = *word;
    int node_id;
    // not putting robust input validation, as handled within speller.c (only alphabet and ')
    while(*word != '\0'){
        c = *word++;
        if(c == '\''){
            node_id = NODE_MAX - 1;
        } else{
            c = tolower(c);
            node_id = c - ALPHA_OFFSET;
        }
        
        if(trav->node[node_id] == NULL){
            return false;
        } else{
            trav = trav->node[node_id];
        }
    }
    return trav->isword;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if(fp == NULL){
        fprintf(stdout, "ERROR - could not open dictionary file \"%s\".\n", dictionary);
        return false;
    }
    
    if((create_node(&root)) == false){
        fprintf(stderr, "ERROR - could not create root node.");
        return false;
    }
    
    trie *trav = root;
    char c;
    int node_id;
    while(true){
        c = fgetc(fp);
        
        if(feof(fp)){
            break;
        }
        
        if(c == '\n' && trav != root){
            trav->isword = true;
            trav = root;
            wcount++;
        }
        // couldn't think of a more elegant way to incorporate " ' " without repeating even more code
        // this way, only alpha chars and ' are used to traverse/create nodes
        if(isalpha(c) || c == '\''){
            if(c == '\''){
                node_id = NODE_MAX - 1;
            } else {
                c = tolower(c);
                node_id = c - ALPHA_OFFSET;    
            }
            
            if(trav->node[node_id] == NULL){
                if(create_node(&(trav->node[node_id])) == false){
                    fprintf(stderr, "ERROR -- Could not create node\n");
                    return false;
                }
            }
            
            trav = trav->node[node_id];
        }
    }
    
    if(fclose(fp) == EOF){
        return false;
    } else {
        return true;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wcount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    trie *trav = root;
    destroy_tries(trav);
    root = NULL;
  
    return true;   
}


/* recursively frees all existent nodes, including root */
void destroy_tries(trie *trav){
    for(int i = 0; i < NODE_MAX; i++){
      if(trav->node[i] != NULL){
          destroy_tries(trav->node[i]);
      }
    }
    free(trav);
}

bool create_node(trie **tp){
    *tp = malloc(sizeof(trie));
    
    if(*tp == NULL){
        return false;
    }
    else{
        for(int i = 0; i < NODE_MAX; i++){
            (*tp)->node[i] = NULL;
        }
    }
    
    (*tp)->isword = false;
    return true;
}
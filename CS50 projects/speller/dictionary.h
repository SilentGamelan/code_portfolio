/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
// need an extra node for apostrophe as well as alpha chars
#define NODE_MAX 27
// translate characters to tries.node index by subtracting ALPHA_OFFSET
#define ALPHA_OFFSET 97
#include <stdbool.h>


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct _trie{
    bool isword;
    struct _trie *node[NODE_MAX];
} trie;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/** my functions
 * **************/
/* mallocs node, and directly alters trie pointer. Returns False on malloc failure */
bool create_node(trie **tp);
void destroy_tries(trie *trav);


#endif // DICTIONARY_H

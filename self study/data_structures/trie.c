#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define DATA_MAX 20
#define NODE_MAX 10
#define KEY_MAX 6

typedef struct _trie{
    char value[20];
    struct _trie *node[NODE_MAX];
} trie;

int insert(trie *trav, char value[], char key[]);
trie* create_node(void);
bool validate(char value[]);
void destroy_tries(trie *trav);
int main(void){
    
    trie *root = create_node();
    if(root == NULL){
        fprintf(stdout, "ERROR - COULD NOT ALLOCATE ROOT NODE");
        return -1;
    }
    
    trie *trav = root;
    
    int cmd = 0;
    // note this needs to be an int in order to hold BOTH CR and LF characters!
    int flushme = 0;
    char value[DATA_MAX] = "";
    char key[KEY_MAX] = "";
    
    while(cmd != 'x' && cmd !='X'){
        printf("(e)nter new value, (s)earch for value, e(x)it.\n");
        printf("$: ");
        if((cmd = getchar()) == EOF){
            if(ferror(stdin)){
                fprintf(stdout, "Error at menu prompt:\n");
                perror("Error Message");
            }
        }
      //  value[strcspn(value, "\n")] = 0;
        while((flushme = getchar()) != '\n' && getchar()!=EOF);
        switch(cmd){
            case 'x':
            case 'X':
                break;
            case 'e':
            case 'E':
                printf("\nEnter value to add to trie: ");
                if(fgets(value, DATA_MAX, stdin) == NULL){
                    if(ferror(stdin)){
                        fprintf(stdout, "add value fgets ERROR");
                        perror("Error Message");
                    }
                } else if (value[strlen(value)-1]== '\n'){
                    value[strcspn(value, "\n")] = 0;
                    while((flushme = getchar()) != '\n' && getchar()!=EOF);
                    
                }
                /* method to get round very annoying C issue of fgets() appending \n before \0
                 * thanks to Tim Čas on stackoverflow q:2693776 */
            
                do{
                    printf("\nEnter 4-digit key (year): ");
                    if(fgets(key, KEY_MAX, stdin) == NULL){
                        if(ferror(stdin)){
                            fprintf(stdout, "add value fgets ERROR");
                            perror("Error Message");
                        }
                    } else if (value[strlen(value)-1]== '\n'){
                        value[strcspn(value, "\n")] = 0;
                        while((flushme = getchar()) != '\n' && getchar()!=EOF);
                    }
                    
                } while(!(validate(key)));
                
                insert(trav, value, key);
                break;
            case 's':
            case 'S':
                printf("**TODO**\n");
                break;
            default:
                break;
        }
        
        trav = root;   
    }

    destroy_tries(trav);
    return 0;
    
}

int insert(trie *trav, char value[], char key[]){
    int keyint = 0;
    char c;
    
    for(int i = 0; i < strlen(key); i++){
        c = key[i];
        keyint = atoi(&c);
        if(trav->node[keyint] == NULL){
            if( ( trav->node[keyint] = create_node() ) == NULL ){
                fprintf(stdout, "ERROR: Could not create node at key value %.*s", i, key);
                return false;
            }
        }
        trav = trav->node[keyint];
    }
    
    if(trav->value[0]){
        fprintf(stdout, "Error, node at key %s is not empty. (contains: \"%s\")\n", key, trav->value);
        return false;
    }
    
    strcpy(trav->value, value);
    return true;
}


trie* create_node(){
    trie *tp = calloc(1, sizeof(trie));
    if(tp != NULL){
        for(int i = 0; i < NODE_MAX; i++){
            tp->node[i] = NULL;
        }
        memset(tp->value, 0, DATA_MAX);
    }
    return(tp);
}

/* Checks that the key is numeric only */
bool validate(char valme[]){
    int len = strlen(valme);
    for(int i = 0; i < len; i++){
        if(!(isdigit(valme[i]))){
            return false;
        }
    }
    return true;
}

void destroy_tries(trie *trav){
    for(int i = 0; i < NODE_MAX; i++){
      if(trav->node[i] != NULL){
          destroy_tries(trav->node[i]);
      }
    }
    free(trav);
}


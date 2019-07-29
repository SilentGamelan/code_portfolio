/**
 *  hashtable.c
 * -------------
 * Simple implementation of a hashtable with chaining.
 * Hash is the most bare-bones I could think of; sorting on numeric value of surname initial as hash table index.
 * 
 * Assumes no duplicates, valid alphabetic input
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_LEN 26
#define NAME_LEN 10

struct node{
    char forename[NAME_LEN];
    char surname[NAME_LEN];
    unsigned int uid;
    struct node *last;
    struct node *next;
};

int hash(char name[]);
void purgebuffer(char array[]);
bool add_user(struct node* table[], char forename[], char surname[], unsigned int id);
bool create_node(struct node **np);
bool search(char forename[], char surname[], struct node *table[]);
void destroy_table(struct node *table[]);
void destroy_list(struct node *np);
void free_node(struct node *delnode);
    
int main(void){

    struct node *table[TABLE_LEN] = {0};
    char forename[NAME_LEN];
    char surname[NAME_LEN];
    char input[NAME_LEN];
    int cmd;
    int flushme;
    unsigned int id = 0;
    
    do{
        printf("(e)nter name, (s)earch for name, (d)elete entry, e(x)it\n");
        printf("$: ");
        cmd = getchar();
        while((flushme = getchar()) != '\n' && flushme != EOF);
        
        switch(cmd){
            case 'e':
            case 'E':
                printf("Enter forename: ");
                fgets(input, NAME_LEN, stdin);
                purgebuffer(input);
                strcpy(forename, input);
                printf("Enter surname: ");
                fgets(input, NAME_LEN, stdin);
                purgebuffer(input);
                strcpy(surname, input);
                if(add_user(table, forename, surname, id)){
                    id++;
                } else{
                    fprintf(stderr, "ERROR: Unable to add user.\n");
                }             
                break;
            case 's':
            case 'S':
                printf("Search target forename: ");
                fgets(input, NAME_LEN, stdin);
                purgebuffer(input);
                strcpy(forename, input);
                printf("Search target surname: ");
                fgets(input, NAME_LEN, stdin);
                purgebuffer(input);
                strcpy(surname, input);
                search(forename, surname, table);
                break;
            case 'x':
            case 'X':
                printf("Exiting...\n");
                break;
            default:
                break;
        }
        
    } while (cmd != 'x' && cmd != 'X');

    destroy_table(table);
    return 0;
    
    
}



int hash(char name[]){
    return (tolower(name[0]) -'a');
}

bool add_user(struct node* table[], char forename[], char surname[], unsigned int id){
    int user_hash = hash(surname);
    struct node *np = table[user_hash];
    struct node *tp = NULL;
    
    if(np == NULL){
        if(!create_node(&np)){
            fprintf(stderr, "ERROR: Could not allocate root node at table position %d", user_hash);
            return false;
        }
        np->last = NULL;
        np->next = NULL;
    } else{
        tp = np;
        if(!create_node(&np)){
            fprintf(stderr, "ERROR: Could not allocate node in chained list\n");
            return false;
        }
        np->next = tp;
        np->last = NULL;
        tp->last = np; 
    }

    np->uid = id;
    strcpy(np->forename, forename);
    strcpy(np->surname, surname);
    table[user_hash] = np;
    return true;
    
}


void purgebuffer(char array[]){
    int flushme = 0;
    
    if (array[strlen(array)-1]== '\n'){
        /* method to get round very annoying C issue of fgets() appending \n before \0
        * thanks to Tim Čas on stackoverflow q:2693776 */
         array[strcspn(array, "\n")] = 0;
    } else {
        while((flushme = getchar()) != '\n' && flushme!=EOF);
    }
}

bool create_node(struct node **np){
        if((*np = malloc(sizeof(struct node))) == NULL){
            return false;
        } else{
            return true;
        }
}

// have placed in wrapper, in case require custom code in future (error checks, etc)
void free_node(struct node * delnode){
    free(delnode);
}

void destroy_table(struct node *table[]){
    struct node *np = NULL;
    for(int i = 0; i < TABLE_LEN; i++){
        if(table[i] != NULL){
            np = table[i];
            destroy_list(np);
            np = NULL;
        }
    }
}

void destroy_list(struct node *np){
    
    if(np->next != NULL){
        destroy_list(np->next);
    }
    free_node(np);
}
/** FIXME - very bad code, rewrite me **/
bool search(char forename[], char surname[], struct node* table[]){
    bool found = false;
    int user_hash = hash(surname);
    struct node *np = table[user_hash];
    while (np != NULL && found == false){
        if(strcmp(surname, np->surname) == 0 && strcmp(forename, np->forename) == 0){
            printf("\nUser found\n");
            printf("----------\n");
            printf("UID: %d\n", np->uid);
            printf("User name: %s, %s\n", surname, forename);
            found = true;
        }
        np = np->next;
    } 
    
    return found;
}
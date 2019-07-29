#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 100
#define INPUT_DIM 5

typedef struct node_t{
    int data;
    struct node_t *last, *next;
} node;

void delete_list(node **head);

int main(void){
    
    node *head = NULL;
    node *new_node = NULL;
    node *prev_node = NULL;
    int node_ID = 0;
    char input[INPUT_DIM];
   // char flushme;
    
    while(node_ID < MAXNODES){
        printf("Enter data for node %d: ", node_ID);
        fgets(input, INPUT_DIM+1, stdin);
        input[strcspn(input, "\n")] = 0;
        // flushing input buffer
        //while ((flushme = getchar()) != '\n' && flushme != EOF);
        
        if(strcmp(input, "x") == 0){
            break;
        }
        
        new_node = malloc(sizeof(node));
        if(new_node == NULL){
            fprintf(stderr, "ERROR: Could not allocate memory for node\n");
            return 1;
        }
        
        new_node->data = atoi(input);
        
        if(node_ID == 0){
            head = new_node;
            head->last = NULL;
            head->next = NULL;
        } else{
            new_node->last = prev_node;
            prev_node->next = new_node;
        }
        
        prev_node = new_node;
        node_ID++;
    }
    
    if(head != NULL){
        new_node = head;
        node_ID = 0;
            
        while(new_node != NULL){
            printf("Node %d = %d\n", node_ID, new_node->data);
            new_node = new_node->next;
            node_ID++;
        }
        
        printf("\n");
        
        while(new_node != NULL){
            printf("Node %d = %d\n", node_ID, new_node->data);
            new_node = new_node->last;
            node_ID--;
        }
        
        delete_list(&head);
    }
    
    return 0;
}

void delete_list(node **curr_node){
    
    if(*curr_node != NULL){
        delete_list(&((*curr_node)->next));
        free(*curr_node);
    }
    
}
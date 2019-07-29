#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *next;
} node;

void help(void);
//bool search_list(int value, node *np);
void print_list(node *np);
int add_node(int value, node *np);
//void del_node(int value, node *np);
//void sort_list(node *np);
void free_nodes(node *np);

int main(void){
    
  //  bool found = false;
    node *head = NULL;
    int input = 0;
    int value = 0;
//    int list_len = 0;
    help();
    
    while(input != 'x' && input != 'X'){
        printf("$: ");
        input = getchar();    
        // should flush the buffer?
        while ((ch = getchar()) != '\n' && ch != EOF);
        switch(input){
            case 'a':
            case 'A':
                printf("Enter value to add to list: ");
                value = getchar();    
                getchar();
                add_node(value, head);
                break;
            case 'd':
            case 'D':
                printf("Enter node number to delete");
                value = getchar();
                getchar();
                del_node(value, head);
                break;
            case 'p':
            case 'P':
                print_list(head);
                break;
            case 'h':
            case 'H':
                help();
                break;
            case 's':
            case 'S':
                sort_list(head);
                break;
            case 'z':
            case 'Z':
                printf("Enter value to search for: ");
                value = getchar();
                getchar();
                search_list(value, head);
                break;
            default:
                    printf("Sorry, command not recognised\n");
                    break;
        }
    }
    
    if(head != NULL){
        free_nodes(head);
    }
    
    return 0;
}
    



void help(void){
    printf("\nCommands:\n");
    printf("--------\n");
    printf("(a)dd node, (d)elete node, (p)rint list, (h)elp, (s)ort list, (z)earch list.\n");
}


bool search_list(int value, node *np){
    
    return false;
}

void print_list(node *np){
    int counter = 0;
    node *print_ptr = np;
    while(print_ptr != NULL){
        printf("Node %d: %d\n", counter, print_ptr->value);
        print_ptr = print_ptr->next;
        counter++;
    }
}

int add_node(int value, node *head){
    node *newnode;
    if((newnode = malloc(sizeof(node))) == NULL){
        fprintf(stderr, "ERROR: Could not allocate memory for new node.\n");
        return 3;
    }
    
    newnode->value = value;
    
    if(head == NULL){
        head = newnode;
    } else{
        newnode->next = head->next;
        head = newnode;
    }
    
    return 0;
}

void del_node(int value, node *np){
    
}

void sort_list(node *np){
    
}

void free_nodes(node *np){
    while(np->next != NULL){
        free_nodes(np->next);
    }
    free(np);
}
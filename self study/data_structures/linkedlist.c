/** linkedlist.c
 * 
 * Experiment to implement single-linked list, using STRUC, STRUC * and malloc
 * inlcuding a menu-system, and the ability to add/delete nodes, sort/search values
 * currently
 * - linear search
 * - insertion sort
 * 
 * TODO 
 * - add more options to select different search/sort methods?
 * - add in stderr & return values
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *next;
} node;


/** Have used ** rather than * in functions, as planning to return other values so need to be able to directly
 * alter [node *head] in main. This is also to avoid declaring head as a global - but perhaps it may have been 
 * preferable here?
 */
void help(void);
bool search_list(int value, node *np);
void print_list(node *np);
int add_node(int value, node **np);
void del_node(int value, node **np);
void sort_list(node *np);
void free_nodes(node **np);
void insertion_sort(int array[], int list_len);
    
int main(void){
    
    node *head = NULL;
    char input = ' ';
    int value = 0;
    help();
    /** NB:  used scanf for ease although getchar may be preferable to protect against overflow
     * note the space before format specifier (" %c") 
     * this is to ensure that scanf will disregard any whitespace in the input buffer.
     * 
     * with this looping menu system and C's buffered input, getc/getchar would add a CR/LF character alongside
     * the chosen character to the buffer. This would then be the next character fed into getchar, leading to problems.
     * 
     * Apparently the only portable way of effectively clearing the buffer in C is the following:
     * while((c = getchar()) != '\n' && c != EOF)
     *    
    */
    while(input != 'x' && input != 'X'){
        printf("\n$: ");
        scanf(" %c", &input);    
        switch(input){
            case 'a':
            case 'A':
                printf("Enter value to add to list: ");
                scanf(" %d", &value);
                add_node(value, &head);
                break;
            case 'd':
            case 'D':
                printf("Are you sure you want to delete entire list? (Y/N)\n");
                scanf(" %c", &input);
                switch(input){
                    case 'y':
                    case 'Y':
                        free_nodes(&head);
                        printf("\nList Deleted...\n");
                        break;
                    default:
                        printf("List Deletion Cancelled...\n");
                        break;
                }
                break;
            case 'n':
            case 'N':
                printf("Enter node number to delete: ");
                scanf(" %d", &value);
                del_node(value, &head);
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
                scanf(" %d", &value);
                search_list(value, head);
                break;
            case 'x':
            case 'X':
                break;
            default:
                    printf("Sorry, command not recognised\n");
                    break;
        }
    }
    
    if(head != NULL){
        free_nodes(&head);
    }
    
    return 0;
}
    



void help(void){
    printf("\nCommands:\n");
    printf("--------\n");
    printf("(a)dd node, (d)elete list, delete (n)ode, (p)rint list, (h)elp, (s)ort list, (z)earch list, e(x)it.\n");
}

// Linear search, as data may not be sorted and is of small size.
bool search_list(int value, node *np){
    int node_ID = 0;
    while(np){
        if(value == np->value){
            printf("Value %d found at node %d.\n", value, node_ID);
            return true;
        }
        np = np->next;
        node_ID++;
    }
    
    printf("Value %d not found in list.\n", value);
    return false;
}


void print_list(node *np){
    int counter = 0;
    while(np != NULL){
        printf("Node %d: %d\n", counter, np->value);
        np = np->next;
        counter++;
    }
}

// adds new nodes to the front of the list
int add_node(int value, node **np){
    node *newnode;
    if((newnode = malloc(sizeof(node))) == NULL){
        fprintf(stderr, "ERROR: Could not allocate memory for new node.\n");
        return 3;
    }
    
    newnode->value = value;
    // If creating first node, make sure node.next is NULL
    if(*np == NULL){
        newnode->next = NULL;
    } else{
        newnode->next = *np;
    }
    
    *np = newnode;
    return 0;
}

// allows deletion of any node in list
void del_node(int node_ID, node **headptr){
    if(node_ID < 0){
        fprintf(stderr, "Error: Invalid Node ID \"%d\"\n", node_ID);
        return;
    }
    
    int n = 0;
    // only way I could think to allow node deletion was to emulate a doubly-linked list by keeping track of previous node via ptr
    node *curr_node = *headptr;
    node *prev_node = *headptr;
    
    while(curr_node != NULL){
        if(n == node_ID){
            if(node_ID == 0){
                // if deleting the first node, set new head by pointing headptr to .next
                *headptr = curr_node->next;
            } else{
                // otherwise, tell previous node to point to next node (ie; skipping current node)
                prev_node->next = curr_node-> next;
            }

            free(curr_node);
            return;
        }
        
        n++;
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    fprintf(stderr, "ERROR: Node %d not found", node_ID);
    return;
}

// sort by converting list into an array for processing, then sequentially writing sorted values
// back into nodes. Have used a insertion_sort as should be efficient with small data-set, and code is compact.
//
// It would be more efficient to keep a rolling tally of listsize declared in main and passed to each function
// however, for this experiment I was interested in writing the other functions without doing so
void sort_list(node *head_ptr){
    node *curr_node = head_ptr;
    int list_len = 0;
    
    while(curr_node){
        list_len++;
        curr_node = curr_node->next;
    }
    
    int array[list_len];
    curr_node = head_ptr;
    
    for(int i = 0; i < list_len; i++){
        array[i] = curr_node->value;
        curr_node = curr_node->next;
    }
    
    insertion_sort(array, list_len);
    
    curr_node = head_ptr;
    for(int i = 0; i < list_len; i++){
        curr_node->value = array[i];
        curr_node = curr_node->next;
    }
}

void free_nodes(node **np){
    if((*np)->next != NULL){
        free_nodes(&((*np)->next));
    }
    free(*np);
    // Pointers must always be set to NULL after freeing MALLOC() mem, as they will typically still point to previous data
    // In this case, you 
    *np = NULL;
    
}

void insertion_sort(int array[], int list_len){
    
    int swap_val;
    
    for(int i = 1; i < list_len; i++){
        swap_val = array[i];
        int j = i-1;
        while(j >=0 && array[j] > swap_val){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = swap_val;
    }
}
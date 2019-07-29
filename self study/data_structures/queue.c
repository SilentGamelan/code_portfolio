/** queue.c
 * Implements a queue via struct and array
 * http://ideone.com/ugrdSm - code works, CS50 IDE doesnt'... why??
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define CAPACITY 10
#define INPUT_MAX 5

struct _queue{
    int array[CAPACITY];
    int front;
    int size;
};

int check_input(char value[INPUT_MAX]);
int enqueue(struct _queue *q_ptr, int value);
int dequeue(struct _queue *q_ptr);
void print_queue(struct _queue *q_ptr); 
int main(void){
    
    struct _queue myqueue = {{0}, 0, 0};
    char input = ' ';
    char value[INPUT_MAX] = " ";
    char flushme = ' ';
    
    while(input != 'x' && input != 'X'){
        
        printf("Enter command (D)equeue, (E)nqueue, (P)rint queue, e(X)it: ");
        input = getchar();
        //(&input, 2, stdin);
        while((flushme = getchar()) != '\n' && flushme != EOF);
        
        switch(input){
            case 'E':
            case 'e':
                printf("Enter value to Enqueue: ");
                fgets(value, INPUT_MAX, stdin);
  //              while((flushme = getchar()) != '\n' && flushme != EOF);
                if(check_input(value) == 0){
                    enqueue(&myqueue, atoi(value));
                    printf("Enqueued Value: %s\n", value);
                    printf("Value at start of queue: %d\n", myqueue.array[myqueue.front]);
                }
                break;    
            case 'D':
            case 'd':
                printf("Dequeueing Value: %d\n", myqueue.array[myqueue.front]);
                dequeue(&myqueue);
                break;
            case 'P':
            case 'p':
                printf("Current Queue:\n");
                print_queue(&myqueue);
                break;
            case 'X':
            case 'x':
                break;
            default:
                break;
        }
    }
    
    return 0;
}


int check_input(char input[INPUT_MAX]){
    
    int index = 0;
    while(input[index] != '\n' && input[index] != EOF){
        if(!isdigit(input[index])){
            printf("Non-numeric input detected\n");
            return 1;
        }
        index++;
    }
    
    return 0;
}

int enqueue(struct _queue *q_ptr, int value){
    
    printf("Enqueueing.... \n");
    if(q_ptr->size == CAPACITY){
        printf("Queue is full.\n");
        return 1;
    } else{
        printf("Enqueueing value: %d...\n", value);
        q_ptr->array[(q_ptr->front + q_ptr->size) % CAPACITY] = value;
        q_ptr->size++;
    }
    return 0;
}

int dequeue(struct _queue *q_ptr){
    if(q_ptr->front == CAPACITY){
        q_ptr->front = 0;
    } else{
        q_ptr->front++;
    }
    q_ptr->size--;
    return 0;
}   

// **TODO** implement print displaying queue order
void print_queue(struct _queue *q_ptr){
    
    printf("Queue as seen in memory:\n");
    for(int i = 0 ; i < CAPACITY; i++){
        printf("%d ", q_ptr->array[i]);
    }
    printf("\n");
}
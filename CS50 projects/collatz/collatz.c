/* collatz.c
*
* recursive implementation of collatz conjecture - it is always possible to get back to 1 with following method:
* 
*   if n is 1:      stop
*   if is even:     repeat process on n/2
*   if n is odd:    repeat process on 3n+1
*
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void collatz(long *mynum, long *steps);

int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("Error: %s\nUsage: %s n (n = int value)", argv[0], argv[0]);
        return 1;
    }
    
    errno = 0;
    char *errptr = NULL;
    
    long int mynum = strtol(argv[1], &errptr, 10);
    
    if(errno != 0){
        return errno;
    }
    
    long int steps = 0;
    
    collatz(&mynum, &steps);
    
    printf("Steps taken to 1: %li\n", steps);
    
    return 0;
}

void collatz(long *mynum, long *steps){
    
    if(*mynum != 1){
        if(*mynum % 2 == 0){
            *mynum /= 2;
        }
        else {
            *mynum = (*mynum * 3) + 1;
        }

        (*steps)++;
        
        collatz(mynum, steps);
    }
}
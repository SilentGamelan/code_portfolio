/*  bubblesort.c
*   -----------
*   bubble sort iterates over n-1 (where n is the size of the array)
*   for each pair of values x,y if x>y, the values of x and y are swapped
*   so that, on each step, the highest value gets pushed to the right.
* 
*   on reaching n-1, we know the highest value is now at n, so the value of n is decremented, and the bubbling loop is run again
*   and again, each time pushing the next highest value successively into place, until the array is sorted
*
*   NB: have reimplimented without pointers, with alternative method of loop counter logic (ie; both counting up)
*       and swap being expanded in-line, rather than as a separate function
*/

#include <stdio.h>

#define ARRAYSIZE 10

//void swap(int *x, int *y);

void print_array(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {4, 2, 1, 3, 7, 0, 9, 8, 5, 6};
    int temp;
    
    print_array(array);
    
    for(int i = 0; i < ARRAYSIZE-1; i++){
        for(int j = 0; j < (ARRAYSIZE - i - 1); j++){
            if(array[j] > array[j+1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
            print_array(array);
        }
    }

    
    print_array(array);  
    return 0;
}


void print_array(int array[])
{
    for(int i = 0; i < ARRAYSIZE; i++){
    printf("%d\t", array[i]);    
    }
    printf("\n");
 
    
}


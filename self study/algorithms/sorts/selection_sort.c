/* selection_sort.c
*   uses array[], x=0, y=0 as indices.
*   sorts by repeatedly iterating over unsorted array (of size n) with x, and finding the minimum value.
*   on initial pass, it swaps min_val with list[y] and increments y
*   on each successive pass it searches from list[y], until reaching n-1, at which point the array will be ordered.
*
*/

#include <stdio.h>

#define ARRAYSIZE 20

void print_array(int array[]);

int main(void)
{
    
    int array[ARRAYSIZE] = {20, 2, 6, 15, 10, 5, 13, 4, 1, 19, 12, 3, 9, 17, 11, 8, 7, 16, 14, 18};
    // hold both the minimum value found, and the index at which it is located, in order to swap with array[x]
    int minval;
    int minval_pos;
    
    print_array(array);
    printf("\n");
    
    for(int x = 0; x < ARRAYSIZE; x++){
        minval = array[x];
        for(int y = x+1; y < ARRAYSIZE; y++){
            if(array[y] < minval){
                minval = array[y];
                minval_pos = y;
            }
        }
        
        // avoid swapping identical numbers
        if(minval != array[x]){
            array[minval_pos] = array[x];
            array[x] = minval;
        }
        
        print_array(array);
    }
    
    
}

void print_array(int array[])
{
    for(int i = 0; i < ARRAYSIZE; i++){
    printf("%d ", array[i]);    
    }
    printf("\n");
 
    
}
/* insertion_sort.c
*
*   implements insertion sort method:
*   iterates over an array (from left to right) taking an unsorted value and then inserting it into its correct place to the left
*   of the currently selected index, i.
*
*   It does this by working from right to left of currently selected index (array[i-1])) and comparing to size of array[i].
*   
*   When the correct place is found, the elements are shifted to the right in order to make space for the insertion val of array[i]
*
*   This is often described as a card-players sort, where a deck is worked through one after the other and sorted into a
*   a separate sorted pile. However, this implementation sorts "in-place" rather than to a separate array
*/

#include <stdio.h>

#define ARRAYSIZE 20

void swap(int *i, int *y);
void print_array(int array[]);

int main(void)
{
    int array[ARRAYSIZE] = {20, 2, 6, 15, 10, 5, 13, 4, 1, 19, 12, 3, 9, 17, 11, 8, 7, 16, 14, 18};
    
    print_array(array);
    
    int swap_val;
    
    for(int i = 1; i < ARRAYSIZE; i++){
        swap_val = array[i];
        int j = i-1;
        while(j >=0 && array[j] > swap_val){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = swap_val;
        print_array(array);
    }
    
    print_array(array);
    
    return 0;

    
}


void print_array(int array[])
{
    for(int i = 0; i < ARRAYSIZE; i++){
    printf("%d ", array[i]);    
    }
    printf("\n");
 
    
}
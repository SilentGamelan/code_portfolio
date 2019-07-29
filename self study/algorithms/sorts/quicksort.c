/* quicksort.c
*   implements quicksorting of an array
*   selects a value from the array to act as the "pivot" - 
*   Each remaining value is then "partitioned" - grouped to left/right of pivot index depending if less-than or greater-than pivot
*   Each partition is then recursively sorted by quicksorting of the effective 'subarrays'
*
*   Quicksort operates in-place - the 'subarrays' are simulated by recording and passing indices of array[] which describe the
*   relative start and end positions of each subarray 
*/

#include <stdio.h>

#define ARRAYSIZE 20

void print_array(int array[]);
void a_swap(int array[], int a, int b);

void quick_sort(int array[], int start, int end);
int partition(int array[], int start, int end);


int main(void)
{
    int array[ARRAYSIZE] = {20, 2, 6, 15, 18, 5, 13, 4, 1, 19, 12, 3, 9, 17, 11, 8, 7, 16, 14, 10};

    print_array(array);

    // called with array and its start/end indices
    quick_sort(array, 0, ARRAYSIZE-1);
    
    print_array(array);
    
    return 0;
}


void quick_sort(int array[], int start, int end)
{
    // breaks recursion when reaches terminal case (ie; a single-member sub-array is reached via partitioning)
    if(start < end){
        // the position of the pivot, after partition() has ordered current array with pivot in the middle
        // values < pivot to the left, values > pivot to the right
        int pIndex = partition(array, start, end);
        
        // recursively partition and sort the sub arrays to the left, and then the right, of the pivot for the current sub-array
        quick_sort(array, start, pIndex-1);
        quick_sort(array, pIndex+1, end);
    }
    
}

int partition(int array[], int start, int end)
{
    // have chosen to always select the rightmost index of a sub-array to be the pivot
    // this is not ideal, as for ordered arrays can increase complexity to O(n^2), rather than O(n log n)
    // Choosing a random index as a pivot value is probably preferable to avoid this
    int pivot = array[end];
    int pIndex = start;
    
    for(int count = start; count < end; count++){
        // the pivot index effectively points to the next potential place to swap-in a value < pivot
        // if array[count]>pivot, pIndex is NOT incremented, and so on the next iteration of array[count] with a value < pivot
        // array[count] can be safely swapped into array[pIndex], and 
        if(array[count] <= pivot){
            // avoid unnecessary swap where the first iteration of array[count]<= pivot and so would swap itself
            if(pIndex != count){
                a_swap(array, count, pIndex);
            }
            pIndex++;
        }
    }
    
    // for-loop ends at n-1, as nth position contains the pivot, which is then swapped into the position pointed to by pIndex
    // which will be bee the position one-to-the-right of the lower-than-pivot values. Swapping here places x... < pivot > y...
    a_swap(array, pIndex, end);
    
    return pIndex;
}
    
    


void print_array(int array[])
{
    for(int i = 0; i < ARRAYSIZE; i++){
    printf("%d ", array[i]);    
    }
    printf("\n");
 
    
}

void a_swap(int array[], int a, int b)
{
    int c = array[a];
    array[a] = array[b];
    array[b] = c;
}
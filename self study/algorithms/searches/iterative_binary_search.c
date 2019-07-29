/* iterative binary_search.c
*
*   implementation of simple binary search algorithm on an ordered array of length n, to find a value num
*   aka: divide and conquer
*
*   take the minimum value and max value to find the range (to start, this will be min:1 max:n)
*   find the mid-point (mid) of the range by averaging ((min+max)/2)
*   If the mid > num, set max to mid-point+1, if midpoint > num, set min to midpoint-1
*   repeat until mid-point = num or min > max, indicating that the number has not been found.
*   
*   This implementation is iterative
*
*   Complexity should be O(log n) - results seem to bear reasonably close
*/

#include <stdio.h>
#include <cs50.h>

#define ARRAYSIZE 10000

bool binary_search(int mynum, int values[], int min, int max);
bool search(int value, int values[], int n);

int main(void){
    
    int values[ARRAYSIZE];
    int value = 10001;
    
    for(int i = 0;  i < ARRAYSIZE; i++){
        values[i] = i+1;
    }

    if(search(value, values, ARRAYSIZE-1)){
        printf("Value found\n");
    } else {
        printf ("Value not found\n");
    }

    return 0;
    
}


bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(binary_search(value, values, 0, n)){
        return true;
    } else{
        return false;
    }
}

bool binary_search(int mynum, int values[], int min, int max)
{
    int mid;
    bool found = false;
    
    while(min <= max){
        
        mid = (min+max)/2;
        
        if(values[mid] == mynum){
            found = true;
            break;
        }
        
        if(values[mid] > mynum){
            max = mid - 1;
        } 
        else if (values[mid] < mynum){
            min = mid + 1;
        }
    }
   
    return found;
}
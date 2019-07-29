/*  counting_sort.c
*   (aka; ultrasort/mathsort)
*   sorting algorithm usable on a known, finite, reasonably small range of discrete values with complexity O(n)
*
*   uses a counting array of the same size as known possible key values 
*   (eg; sorting values 0-9 requires count_array[10], values 0-20 requires count_array[21])
*
*   increments counting array index for each incidence of mapped value (ie; array[]={1, 1, 1) will inc count_array[0] 3 times
*
*   then uses count values x, y to iterate over array[] and count_array[], mapping occurances of values
*/


#include <stdio.h>

#define ARRAYSIZE 10
#define MAX_NO 9
#define COUNTINGSIZE MAX_NO + 1

int main(void)
{
    int sortme[ARRAYSIZE] = {8, 8, 4, 3, 1, 2, 1, 6, 3, 1};
    int counting[COUNTINGSIZE];
    
    for(int i = 0; i < ARRAYSIZE; i++){
        counting[i] = 0;
    }

    for(int i = 0; i < ARRAYSIZE; i++){
        counting[sortme[i]]++;
    }
   
   int x = 0;
   int y = 0;
   // x steps over each index of sortme[]
   // y increments over each value represented as an index of counting[]
   while(x < ARRAYSIZE){
       // if there are any occurences of the value represented by counting[y]
       while(counting[y] > 0){
           // insert the represented value into sortme[]
           sortme[x] = y;
           // decrement the amount of occurances held in counting[y]
           counting[y]--;
           // increment the index of sortme[] currently pointing at
           x++;
       }
       y++;
   }
   
   for(int i = 0; i < ARRAYSIZE; i++){
        printf("%d\t", sortme[i]);
    }
    
    printf("\n");
    
    return 0;
}
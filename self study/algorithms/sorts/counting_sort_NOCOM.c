/*  counting_sort.c
*   (aka; ultrasort/mathsort)
*   sorting algorithm usable on a known, finite, reasonably small range of discrete values. 
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
    int array[ARRAYSIZE] = {8, 8, 4, 3, 1, 2, 1, 6, 3, 1};
    int counting_array[COUNTINGSIZE];
    
    for(int i = 0; i < ARRAYSIZE; i++){
        counting_array[i] = 0;
    }

    for(int i = 0; i < ARRAYSIZE; i++){
        counting_array[array[i]]++;
    }
   
   int x = 0;
   int y = 0;
   while(x < ARRAYSIZE){
       while(counting_array[y] > 0){
           array[x++] = y;
           counting_array[y]--;
       }
       y++;
   }
   
   for(int i = 0; i < ARRAYSIZE; i++){
        printf("%d\t", array[i]);
    }
    
    printf("\n");
    
    return 0;
}
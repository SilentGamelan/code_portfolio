/* int_division.c
*
*   Important reminder of why mindful selection of variable types is necessary 
*
*/

#include <stdio.h>

int main(void)
{
    int a = 10;
    int b = 3;
    int c = a/b;
    
    printf("%d\n", c);

    printf("%d\n", a/b);
    
    printf("%f\n", (float)(a/b));
    
    printf("%f\n", (float)a/(float)b); // this is the only way to achieve correct result without explict float types.

    return 0;
}
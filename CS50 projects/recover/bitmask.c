/** bitmask.c
 * 
 * Example of using bitmasking to check for bit-flags, or number ranges
 * 
 * 
*/


#include <stdio.h>

int main(void){
    
    
    unsigned char bitmask = 0xE0;
    
    unsigned char value[16];
    value[15] = 0xB0;
    
    unsigned char val = 224;
    for(int i = 0; i < 15; i++){
        value[i] = val++;
    }

    for(int i = 0; i < 16; i++){
        printf("%d bitmasked with %d = %d\n", (int)value[i], (int)bitmask, (int)(bitmask & value[i]));
    }
    
    
    
    return 0;
}
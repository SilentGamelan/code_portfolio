#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define ROWSIZE 10

int main(void){
    
    int source[ROWSIZE] = {2,1,2,1,2,1,2,1,2,1};
    
    int dest[100];
    for(int i = 0; i < 100; i++){
        dest[i] = 0;
    }
    
    float scale = 2.5;
    float temp_size = ROWSIZE * scale;
 
    int scale_counter = (int)scale;
    // remove this and reuse dec_counter?
    int dec_temp = (int) (scale * 10);
    int decimal = dec_temp % 10;
    int dec_counter = decimal;
    
    int new_size;
    new_size = (int)temp_size;
    
    int *pix_ptr = dest;
    
    for(int i = 0; i < ROWSIZE; i++){
        // TODO - keep track of the decimal, and use some form of formula to add the extra 1 on to the for loop count variable
        // ie;  scale of 1.1 means that for every 10 pixels, 1 extra should be added
        //      scale of 1.2 means that for every 5 pixels 1 extra should be added          10px 2 added
        //      scale of 1.3 means that for every ?4 pixels, 1 extra should be added []     10px 3 added
        //      scale of 2.0 means that for every 1 pixel, 1 should be added
        
        if(dec_counter >= 10){
            scale_counter++;
        }
        
        for(int j = 0; j < (int)scale_counter; j++){
            *pix_ptr++ = source[i];
         
        }
        
        if(dec_counter >= 10){
            dec_counter -= 10;
            scale_counter--;
        }
        
        dec_counter += decimal;    
        
    }
        
    for(int i = 0, arraysize = sizeof(dest)/sizeof(dest[0]); i < arraysize; i++){
        printf("Array[%d]: %d\n", i, dest[i]);
    }    
        
    return 0;
}
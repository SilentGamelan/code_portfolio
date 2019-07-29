#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    if(argc != 4){
        fprintf(stderr, "Usage: calc_resize f (floating point no 0.0 - 100.0");
        return 1;
    }
    
    char *end_ptr = NULL;
    
    unsigned long x = strtol(argv[1], &end_ptr, 10);
    unsigned long y = strtol(argv[2], &end_ptr, 10);
    
    
    float scale = strtof(argv[3], &end_ptr);
    
    
    float temp_x, temp_y;
    
    unsigned long new_x, new_y;
    
    temp_x = x * scale;
    temp_y = y * scale;
    
    new_x = (unsigned long)temp_x;
    new_y = (unsigned long)temp_y;
    
    printf("x: %lu\ny: %lu\n\nScale: %f\n\ntemp_x: %f\ntemp_y: %f\n\nnew_x: %lu\nnew_y: %lu\n", x, y, scale, temp_x, temp_y, 
    new_x, new_y);
    
    return 0;
}
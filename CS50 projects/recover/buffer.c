#include <stdio.h>

int main(void){
    
    unsigned char buffer[4] = {0xFF, 0xF8, 0xFF, 0xE0};
    
    //if(buffer[0] == 0xFF && buffer[1] == 0xF8 && buffer[2] == 0xFF && (buffer[3] & 0xE0) == 0xE0){
    if(*buffer == 0xFF && *(buffer+1) == 0xF8 && *(buffer+2) == 0xFF && (*(buffer+3) & 0xE0) == 0xE0){
        printf("yay.\n");
    }
    
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
    char array[5] = "1234";
    int num = 0;
    // atoi obviously runs until hits nul unless it knows it is a char pointer
    // it below gives result of "2345"
    num = atoi(&array[1]);
    printf("num: %d\n", num);
    
    // as per SO:3251401, you can use the fact that digits are guaranteed to be 1 larger than the last
    for(int i = 0; i < strlen(array); i++){
        if(array[i] >= '0' && array[i] <= '9'){
            num = array[i] - '0';
            printf("num %d: %d\n", i, num);
        }
    }
    
    // checking if string is empty
    
 struct mystruct{
    char mystring[5];    
    };
   
    struct mystruct mestruct;
    strcpy(mestruct.mystring, array);
    struct mystruct *sp = &mestruct;
    
    if(!(sp->mystring[0])){
        printf("Suprise I'm not empty at all!!\n");
    }
    
    
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

int foo(void);

int main(void){

    if(foo()){
        printf("baa!\n");
    }    
    
    if(!foo()){
        printf("nobaa!\n");
    }
    
    if(0 && 0){
        printf("logically zero");
    }
    return 0;
}

int foo(){
    
    return 0;
    
}
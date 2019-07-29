#include <stdio.h>
#include <string.h>

int main(void){
    
    char testy[] = "x";
    char testy2[5] = "x";
    int val = 9999;
    
    val = strcmp(testy, testy2);
    //val = strcmp(testy, testy3);
    //val = strcmp(testy, testy4);
    
    char mystring[10] = "yarp";
    printf("length of mystring = %lu", strlen(mystring));
    
    char c = '\'';
    if(c == '\''){
        printf("That's apostrophewang!\n");
    }
    
    return 0;
}
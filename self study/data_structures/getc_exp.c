#include <stdio.h>


int main(void){
    char mystring[6] = {0};
    mystring[0] = '1';
    char flushme;
    printf("%s\n", mystring);
    
    fgets(mystring, 2, stdin);
    while((flushme = getchar()) != '\n' && flushme != EOF);
    printf("%s\n", mystring);
    fgets(mystring, 6, stdin);
    printf("%s\n", mystring);
    
    
    printf("0 modulo 5 = %d\n", 0%5);
    printf("Mystring is now %s\n", mystring);
    printf("\narray indexing using modulo: %c\n", mystring[(0+0)%5]);
    return 0;
}
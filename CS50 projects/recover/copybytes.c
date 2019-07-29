#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


int main(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "%s Usage: %s int n source_file des_file (n = bytes to be copied)\n", argv[0], argv[0]);
        return 1;
    }
    
    FILE *src_fp, *dest_fp;
    char *endptr;
    char c;
    errno = 0;
    
    long long unsigned int bytes = strtoull(argv[1], &endptr, 10);
    
    if(endptr == argv[1] || *endptr != '\0' || ((bytes == LLONG_MAX || bytes == LLONG_MIN) && errno == ERANGE)){
        fprintf(stderr, "ERROR converting %s to long long int.\n", argv[1]);
        return bytes;
    }
    
    src_fp = fopen(argv[2], "r");
    if(src_fp == NULL){
        fprintf(stderr, "ERROR - could not open file %s for reading\n", argv[2]);
        return 2;
    }
    
    dest_fp = fopen(argv[3], "w");
    if(dest_fp == NULL){
        fprintf(stderr, "ERROR - could not open file %s for writing\n", argv[3]);
        return 3;
    }
    
    for(int i = 0; i < bytes; i++){
        fread(&c, 1, 1, src_fp);
        if(feof(src_fp)){
            fprintf(stderr, "Unexpected end of file\n");
            break;
        }
        fwrite(&c, 1, 1, dest_fp);
    }

    fclose(dest_fp);
    fclose(src_fp);
    
    return 0;
}
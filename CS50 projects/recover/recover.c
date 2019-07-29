/**
 *  recover.c - program to read in the contents of a file (representing the contents of a memory card)
 *  discover any deleted jpg files, and write out any recovered images to separate files on disk
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE 512

int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "%s Usage: %s n (n = name of memory card dump file)\n", argv[0], argv[0]);
        return 1;
    }
    
    char *src_filename = argv[1];
    
    FILE *src_fp, *dest_fp;
    
    src_fp = fopen(src_filename, "r");
    if(src_fp == NULL){
        fprintf(stderr, "ERROR: unable to open source file %s", src_filename);
        return 2;
    }
    
    char dest_filename [6];
    unsigned int file_no = 0;
    unsigned char buffer[BLOCKSIZE];
    unsigned char header1 = (unsigned char)0xFF;
    unsigned char header2 = (unsigned char)0xD8;
    // the final byte in the header is from E0 to EF
    // another way of looking at it is that the first three bits of the final byte are 111n
    // so we can check if these bits are set by applying a bitmask of 1110 (0xE0) (apply logical &)
    // if the result is the same as the bitmask, we know this is true
    unsigned char header3 = (unsigned char)0xE0;
    long long blockcounter = 0;
    
    while(fread(buffer, BLOCKSIZE, 1, src_fp) == 1){

        if(*buffer == header1 && *(buffer + 1) == header2 && *(buffer + 2) == header1 && (header3 & *(buffer + 3)) == header3){
            
            sprintf(dest_filename, "%03d.jpg", file_no++);
            
            dest_fp = fopen(dest_filename, "w");
            if(dest_fp == NULL){
                fprintf(stderr, "ERROR: unable to open file %s for writing", dest_filename);
                return 3;
            }
        
            while(!feof(src_fp)){
                fwrite(buffer, BLOCKSIZE, 1, dest_fp);
                 fread(buffer, BLOCKSIZE, 1, src_fp);
                //if we find the start of another jpg, wind back 1 block and break, to skip writing this to current file, and close it
                if(*buffer == header1 && *(buffer + 1) == header2 && *(buffer + 2) == header1 && (header3 & *(buffer + 3)) == header3){
                    fseek(src_fp, -BLOCKSIZE, SEEK_CUR);
                    break;
                }
            }
            
            fclose(dest_fp);
            blockcounter = 0;
        }
        
    }
    
    fclose(src_fp);
    return 0;
}
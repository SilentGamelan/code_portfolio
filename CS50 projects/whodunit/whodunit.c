/** whodunit.c
 * program to read in a bitmap image, within which is hidden a picture of the culprit of a murder using red masking.
 * 
 * Have rewritten my initial code which was a simple modification of copy.c to make it
 * - Modular
 * - To read the source file entirely into memory (within a custom structure)
 * - To alter the file while in memory
 * - To write the altered bitmap to file via the structure, rather than byte-per-byte
 * - To have reasonably robust error-checking and reporting
 * 
 * This gave me the opportunity to practice with
 * - File pointers
 * - Structure pointers
 * - Pointer-to-pointers
 * - '.' and '->' structure operators
 */
 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "bmp.h"

typedef struct BMPFILE{
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
   unsigned char *pixel_array;
} BMPFILE;

// using FILE pointer-to-pointer, as want open_file()+read_file() to return any error messages. If just send a file pointer,
// then it will be lost on return?
int open_file(char *srcfile, char *destfile, FILE **src_ptr, FILE **dest_ptr);
int read_file(BMPFILE *img_ptr, FILE **src_ptr);
int write_file(BMPFILE *img_ptr, FILE **dest_ptr);
void alter_colour(BMPFILE *img_ptr);

int main(int argc, char *argv[])
{

    if(argc != 3){
        fprintf(stderr, "Usage: whodunit input_file output_file\n\n");
        return 1;
    }

    char *srcfile = argv[1];
    char *destfile = argv[2];
    FILE *src_ptr;
    FILE *dest_ptr;
   
    int err_num = 0;
    
    err_num = open_file(srcfile, destfile, &src_ptr, &dest_ptr);
    if(err_num !=0){
        return err_num;
    }
    
    BMPFILE image;
    
    err_num = read_file(&image, &src_ptr);
    if(err_num != 0){
        return err_num;
    }
    
    alter_colour(&image);
    
    err_num = write_file(&image, &dest_ptr);
    if(err_num != 0){
        return err_num;
    }
    
    free(image.pixel_array);
    
    return 0;
}



int open_file(char *srcfile, char *destfile, FILE **src_ptr, FILE **dest_ptr){
    
    *src_ptr = fopen(srcfile, "r");
    
    if(*src_ptr == NULL){
        fprintf(stderr, "ERROR: could not open input file \"%s\"\n", srcfile);
        return 2;
    }
    
    *dest_ptr = fopen(destfile, "w");
    
    if(*dest_ptr == NULL){
        fprintf(stderr, "ERROR: could not open output file \"%s\"\n", destfile);
        return 3;
    }
    
    return 0;
}




int read_file(BMPFILE *img_ptr, FILE **src_ptr)
{
    // read soure file's BITMAPFILEHEADER
    fread(&(img_ptr->bmfh), sizeof(BITMAPFILEHEADER), 1, *src_ptr);
    
    // read source file's BITMAPINFOHEADER
    fread(&(img_ptr->bmih), sizeof(BITMAPINFOHEADER), 1, *src_ptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (img_ptr->bmfh.bfType != 0x4d42 || img_ptr->bmfh.bfOffBits != 54 || img_ptr->bmih.biSize != 40 || 
        img_ptr->bmih.biBitCount != 24 || img_ptr->bmih.biCompression != 0)
    {
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    
    // Dynamically allocate enough memory to fit the entire image portion into pixel_array
    img_ptr->pixel_array =  (unsigned char *)malloc(img_ptr->bmih.biSizeImage);

    if(!img_ptr->pixel_array){
        fprintf(stderr, "Could not allocate memory for char *pixel_array.\n");
        return 5;
    }
    
    fread(img_ptr->pixel_array, img_ptr->bmih.biSizeImage, 1, *src_ptr);
    
    
    if(fclose(*src_ptr) != 0){
        fprintf(stderr, "Error closing .bmp source file.\n");
        return 6;
    }    
  
    // success
    return 0;

}


int write_file(BMPFILE *img_ptr, FILE **dest_ptr)
{
    int err_num = 0;
    
   // Error checking on fwrite(), which returns BLOCKS if successful
    if(fwrite(&img_ptr->bmfh, sizeof(char), sizeof(BITMAPFILEHEADER), *dest_ptr) != sizeof(BITMAPFILEHEADER)){
        err_num = 7;
    } else if(fwrite(&img_ptr->bmih, sizeof(char), sizeof(BITMAPINFOHEADER), *dest_ptr) != sizeof(BITMAPINFOHEADER)){
        err_num = 8;
    } else if(fwrite(img_ptr->pixel_array, sizeof(char), img_ptr->bmih.biSizeImage, *dest_ptr) != img_ptr->bmih.biSizeImage){
        err_num = 9;
    } else if(fclose(*dest_ptr) != 0){
        err_num = 10;   
    }
    
    
    if(err_num != 0){
        fprintf(stderr, "ERROR: Problem writing to file.\n");
        return err_num;
    }
    
    return 0;
}

    

void alter_colour(BMPFILE *img_ptr)
{
    // determine padding for scanlines
    int padding =  (4 - (img_ptr->bmih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // *pixel_ptr used to step over the byte values contained in pixel_array, in order to read and modify RGB values
    unsigned char *pixel_ptr = img_ptr->pixel_array;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(img_ptr->bmih.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for(int j = 0; j < img_ptr->bmih.biWidth; j++){
            // Colour altering code for finding hidden messages
            // REMEMBER THAT THE ORDER IN BMP HEADER IS BLUE GREEN RED!!!!
            // if pixel is bright red, then make pixel white, otherwise, turn it black
            if(*(pixel_ptr+2) == 255){
                *pixel_ptr++ = 255;
                *pixel_ptr++ = 255;
                pixel_ptr++;
            }
            else{
                *pixel_ptr++ = 0;
                *pixel_ptr++ = 0;
                *pixel_ptr++ = 0;
            }
        
        }
        // add padding at the end of scanline, if required
        for (int k = 0; k < padding; k++){
                *pixel_ptr++ = 0;
            }
    }
    
}

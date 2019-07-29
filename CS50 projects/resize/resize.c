/** resize.c
 * program to read in a bitmap image, and resize it as per command-line argument
 * 
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bmp.h"

// for error checking, must also #include <errno.h> as above
extern int errno;

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
void resize_image(BMPFILE *img_ptr, BMPFILE *resized_ptr, float scale);

int main(int argc, char *argv[]){
   
    if(argc != 4){
        fprintf(stderr, "Usage: resize scaling_value(0.0-100.0), input_file, output_file\n");
        return 1;
    }

    // required for strtof()
    char *endptr = NULL;
    float scale = strtof(argv[1], &endptr);
    // error checking: if no conversion is performed, strof() will return a 0, and place the value of endptr into 
    // address of nptr (here, argv[1]). So the following will detect an input error
    if(scale == 0 && argv[1] == endptr){
        fprintf(stderr, "ERROR: Scale input error\n");
        return 2;
    }
    
    if(scale < 0 || scale > 100.0){
        fprintf(stderr, "ERROR: scaling factor must be between 0.0 and 100.0\n");
        return 2;
    }

    char *srcfile = argv[2];
    char *destfile = argv[3];
    FILE *src_ptr;
    FILE *dest_ptr;
   
    
    errno = open_file(srcfile, destfile, &src_ptr, &dest_ptr);
    if(errno !=0){
        return errno;
    }
    
    BMPFILE image;
    
    errno = read_file(&image, &src_ptr);
    if(errno != 0){
        return errno;
    }
    
    BMPFILE resized_image;
    
    resize_image(&image, &resized_image, scale);
    
    errno = write_file(&resized_image, &dest_ptr);
    if(errno != 0){
        return errno;
    }
    
    free(image.pixel_array);
    free(resized_image.pixel_array);
    
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




int read_file(BMPFILE *img_ptr, FILE **src_ptr){
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

// **TODO update this to avoid confusion with img_ptr and resized_ptr: image. resized. structures
int write_file(BMPFILE *img_ptr, FILE **dest_ptr){
    
   // Error checking on fwrite(), which returns BLOCKS if successful
    if(fwrite(&img_ptr->bmfh, sizeof(char), sizeof(BITMAPFILEHEADER), *dest_ptr) != sizeof(BITMAPFILEHEADER)){
        errno = 7;
    } else if(fwrite(&img_ptr->bmih, sizeof(char), sizeof(BITMAPINFOHEADER), *dest_ptr) != sizeof(BITMAPINFOHEADER)){
        errno = 8;
    } else if(fwrite(img_ptr->pixel_array, sizeof(char), img_ptr->bmih.biSizeImage, *dest_ptr) != img_ptr->bmih.biSizeImage){
        errno = 9;
    } else if(fclose(*dest_ptr) != 0){
        errno = 10;   
    }
    
    
    if(errno != 0){
        fprintf(stderr, "ERROR: Problem writing to file.\n");
        return errno;
    }
    
    return 0;
}

    

void resize_image(BMPFILE *img_ptr, BMPFILE *resized_ptr, float scale){
    
    
    // copy the header of source file
    resized_ptr->bmfh = img_ptr->bmfh;
    resized_ptr->bmih = img_ptr->bmih;
    
    float temp_x, temp_y;
    LONG new_x, new_y;
    
    // apply scaling factor
    temp_x = img_ptr->bmih.biWidth * scale;
    temp_y = img_ptr->bmih.biHeight * scale;
    
    // round and truncate scaled x,y values back into int values
    new_x = (long)temp_x;
    new_y = (long)temp_y;
    
    // update resized image header 
    resized_ptr->bmih.biWidth = new_x;
    resized_ptr->bmih.biHeight = new_y;
    
    // determine padding for scanlines
    int orig_padding =  (4 - (img_ptr->bmih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (resized_ptr->bmih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // continue updating header files
    resized_ptr->bmih.biSizeImage = ((new_x * sizeof(RGBTRIPLE))+ new_padding) * abs(new_y);
    resized_ptr->bmfh.bfSize = sizeof(resized_ptr->bmfh) + sizeof(resized_ptr->bmih) + resized_ptr->bmih.biSizeImage;
    
    // malloc pixel buffer for resized imaged
    resized_ptr->pixel_array =  (unsigned char *)malloc(resized_ptr->bmih.biSizeImage);
    

    // ptrs used to step over the byte values contained in pixel_array, in order to read and modify RGB values
    unsigned char *pix_ptr = img_ptr->pixel_array;
    unsigned char *newpix_ptr = resized_ptr->pixel_array;
    
    /**
     * find and store the decimal part of scale as an INT (to keep track of fractions
     *  for columns:
    *      scale 1.5 can be interpreted as print 1 extra pixel every 2 pixels in old line
    *      scale 0.5 means to print 1 pixel in new line, for every 2 pixels in old line
    *  
    * for rows:
    *      scale 0.5 means to only copy every *other* line
    *      scale 2 means to copy each line twice
    *      scale 1.5 means to copy an EXTRA line for every 2 lines from old image
    *
    * using xdecimal and ydecimal allows me to turn off the line-duping code when not enlarging
    * it should also allow me to modify the code to allow for independent x and y axis resizing?
    */
    
    int xscale_counter = (int)scale;
    int xdec_counter = (int) (scale * 10);
    int xdecimal = xdec_counter % 10;
    xdec_counter = xdecimal;
    
    int yscale_counter = xscale_counter;
    int ydec_counter = xdec_counter;
    int ydecimal = xdecimal;

  
    // keep track of start of current line where required to print extra copies when upsizing [use memcpy()]
    // should be unsigned char * const buffer?
    // should I be casting malloc or not? Conflicting opinions
    //unsigned char *line_start, *line_end,
    unsigned char *bp;
    unsigned char *buffer = malloc((new_x * sizeof(RGBTRIPLE))+ new_padding);
    bp = buffer;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(img_ptr->bmih.biHeight); i < biHeight; i++)
    {
        if(ydec_counter >= 10){
            yscale_counter++;
        }
        
       // line_start = newpix_ptr;
        bp = buffer;
        // iterate over pixels in scanline
        for(int k = 0; k < img_ptr->bmih.biWidth; k++){
            
            if(xdec_counter >= 10){
                xscale_counter++;
            }
            
            for(int l = 0; l < xscale_counter; l++){
                *bp++ = *(pix_ptr);
                *bp++ = *(pix_ptr+1);
                *bp++ = *(pix_ptr+2);
            }
           
            
            if(xdec_counter >= 10){
                xdec_counter -= 10;
                xscale_counter--;
            }
            
            xdec_counter += xdecimal;
           
            pix_ptr = pix_ptr + 3;
        }
        
        // move past padding at the end of src image scanline, if necessary
        for (int m = 0; m < orig_padding; m++){
            pix_ptr++;
        }
            
        // add in new padding to new image
        for(int m = 0; m < new_padding; m++){
            *bp++ = 0;
        }
            
        //line_end = newpix_ptr - 1;
            
        // copy current line according to yscale_counter to apply vertical resize    
        for(int n = 0; n < yscale_counter; n++){
            memcpy(newpix_ptr, buffer, (bp - buffer));
            newpix_ptr = newpix_ptr + (bp - buffer);
        }
        
        // prevents fractional values being carried over to next line
        xdec_counter = xdecimal;
        
        if(ydec_counter >= 10){
                ydec_counter -= 10;
                yscale_counter--;
        }
        ydec_counter += ydecimal;    
        
    }
    free(buffer);
}

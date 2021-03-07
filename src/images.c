/*
Bina BADIANE
11928259
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "lodepng.h"
#include "images.h"

#define ALPHA 255

Im readImage(char *filename){
    unsigned error;
    uint32_t width, height, i, j, z;
    uint8_t *image;
    Im img;
    error = lodepng_decode32_file(&image, &width, &height, filename);
    if(error){
        fprintf(stderr, "Error : could not read %s\n", filename);
	    assert(0);
    }
    img.tab = (uint8_t**) malloc(height*sizeof(uint8_t*));
    if(img.tab == NULL){
        fprintf(stderr, "Memory allocation error (1)\n");
	    assert(0);
    }
    for(i = 0; i < height; i ++){
        img.tab[i] = (uint8_t*) malloc(width*sizeof(uint8_t));
        if(img.tab[i] == NULL){
            fprintf(stderr, "Memory allocation error (2)\n");
    	    assert(0);
        }
    }
    img.width = width;
    img.height = height;
    z  = 0;
    for(i = 0; i < height; i ++){
        for(j = 0; j < width; j ++){
            img.tab[i][j] = image[z];
            z += 4;
        }
    }
    free(image);
    return img;
}

void writeImage(Im img, char *filename){
    uint32_t n, i, j, z;
    uint8_t *image;
    unsigned error;
    n = 4 * img.width * img.height;
    image = (uint8_t*) malloc(n*sizeof(uint8_t));
    if(image == NULL){
        fprintf(stderr, "Memory allocation error (3)\n");
	    assert(0);
    }
    z = 0;
    for(i = 0; i < img.height; i ++){
        for(j = 0; j < img.width; j ++){
            image[z++] = img.tab[i][j];
            image[z++] = img.tab[i][j];
            image[z++] = img.tab[i][j];
            image[z++] = ALPHA;
        }
    }
    error = lodepng_encode32_file(filename, image, img.width, img.height);
    if(error){
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        assert(0);
    }
    free(image);
}

void writeImageColor(Im img, char *filename){
    srand(time(NULL));
    uint32_t n, i, j, z;
    uint8_t *image;
    uint8_t red1, red2, green1, green2, blue1, blue2;
    unsigned error;
    n = 4 * img.width * img.height;
    image = (uint8_t*) malloc(n*sizeof(uint8_t));
    if(image == NULL){
        fprintf(stderr, "Memory allocation error (4)\n");
	    assert(0);
    }
    z = 0;
    red1 = (rand() % 256);
    red2 = red1;
    while(red2 == red1)
        red2 = (rand() % 256);
    green1 = (rand() % 256);
    green2 = green1;
    while(green2 == green1)
        green2 = (rand() % 256);
    blue1 = (rand() % 256);
    blue2 = blue1;
    while(blue2 == blue1)
        blue2 = (rand() % 256);
    for(i = 0; i < img.height; i ++){
        for(j = 0; j < img.width; j ++){
            if(img.tab[i][j] == 100){
                image[z++] = red1;
                image[z++] = green1;
                image[z++] = blue1;
                image[z++] = ALPHA;
            }
            else{
                image[z++] = red2;
                image[z++] = green2;
                image[z++] = blue2;
                image[z++] = ALPHA;
            }
        }
    }
    error = lodepng_encode32_file(filename, image, img.width, img.height);
    if(error){
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        assert(0);
    }
    free(image);
}

void writeImageContour(Im img, Im img_watershed, char *filename){
    uint32_t n, i, j, z;
    uint8_t *image;
    unsigned error;
    n = 4 * img.width * img.height;
    image = (uint8_t*) malloc(n*sizeof(uint8_t));
    if(image == NULL){
        fprintf(stderr, "Memory allocation error (5)\n");
	    assert(0);
    }
    z = 0;
    for(i = 0; i < img.height; i ++){
        for(j = 0; j < img.width; j ++){
            if(0 < i && i < img.height-1 && 0 < j && j < img.width-1){
                if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i+1][j+1] == 200 && img_watershed.tab[i+1][j] == 200 && img_watershed.tab[i+1][j-1] == 200 && img_watershed.tab[i][j-1] == 200 && img_watershed.tab[i-1][j-1] == 200 && img_watershed.tab[i-1][j] == 200 && img_watershed.tab[i-1][j+1] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i+1][j+1] == 100 && img_watershed.tab[i+1][j] == 100 && img_watershed.tab[i+1][j-1] == 100 && img_watershed.tab[i][j-1] == 100 && img_watershed.tab[i-1][j-1] == 100 && img_watershed.tab[i-1][j] == 100 && img_watershed.tab[i-1][j+1] == 100) ){
                    image[z++] = img.tab[i][j];
                    image[z++] = img.tab[i][j];
                    image[z++] = img.tab[i][j];
                    image[z++] = ALPHA;
                }
                else{

                    image[z++] = 0;
                    image[z++] = 0;
                    image[z++] = 255;
                    image[z++] = ALPHA;
                }
            }
            else{
                if(i == 0 && j == 0){
                    if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i+1][j+1] == 200 && img_watershed.tab[i+1][j] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i+1][j+1] == 100 && img_watershed.tab[i+1][j] == 100) ){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(i == 0 && j == img.width-1){
                    if((img_watershed.tab[i+1][j] == 200 && img_watershed.tab[i+1][j-1] == 200 && img_watershed.tab[i][j-1] == 200) || (img_watershed.tab[i+1][j] == 100 && img_watershed.tab[i+1][j-1] == 100 && img_watershed.tab[i][j-1] == 100) ){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(i == 0 && 0 < j && j < img.width-1){
                    if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i+1][j+1] == 200 && img_watershed.tab[i+1][j] == 200 && img_watershed.tab[i+1][j-1] == 200 && img_watershed.tab[i][j-1] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i+1][j+1] == 100 && img_watershed.tab[i+1][j] == 100 && img_watershed.tab[i+1][j-1] == 100 && img_watershed.tab[i][j-1] == 100)){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(0 < i && i < img.height-1 && j == 0){
                    if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i+1][j+1] == 200 && img_watershed.tab[i+1][j] == 200 && img_watershed.tab[i-1][j] == 200 && img_watershed.tab[i-1][j+1] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i+1][j+1] == 100 && img_watershed.tab[i+1][j] == 100 && img_watershed.tab[i-1][j] == 100 && img_watershed.tab[i-1][j+1] == 100)){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(i == img.height-1 && j == 0){
                    if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i-1][j] == 200 && img_watershed.tab[i-1][j+1] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i-1][j] == 100 && img_watershed.tab[i-1][j+1] == 100)){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(i == img.height-1 && 0 < j && j < img.width-1){
                    if((img_watershed.tab[i][j+1] == 200 && img_watershed.tab[i][j-1] == 200 && img_watershed.tab[i-1][j-1] == 200 && img_watershed.tab[i-1][j] == 200 && img_watershed.tab[i-1][j+1] == 200) || (img_watershed.tab[i][j+1] == 100 && img_watershed.tab[i][j-1] == 100 && img_watershed.tab[i-1][j-1] == 100 && img_watershed.tab[i-1][j] == 100 && img_watershed.tab[i-1][j+1] == 100) ){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else if(i == img.height-1 && j == img.width-1){
                    if((img_watershed.tab[i][j-1] == 200 && img_watershed.tab[i-1][j-1] == 200 && img_watershed.tab[i-1][j] == 200) || (img_watershed.tab[i][j-1] == 100 && img_watershed.tab[i-1][j-1] == 100 && img_watershed.tab[i-1][j] == 100) ){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
                else{
                    if((img_watershed.tab[i+1][j] == 200 && img_watershed.tab[i+1][j-1] == 200 && img_watershed.tab[i][j-1] == 200 && img_watershed.tab[i-1][j-1] == 200 && img_watershed.tab[i-1][j] == 200) || (img_watershed.tab[i+1][j] == 100 && img_watershed.tab[i+1][j-1] == 100 && img_watershed.tab[i][j-1] == 100 && img_watershed.tab[i-1][j-1] == 100 && img_watershed.tab[i-1][j] == 100) ){
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = img.tab[i][j];
                        image[z++] = ALPHA;
                    }
                    else{
                        image[z++] = 0;
                        image[z++] = 0;
                        image[z++] = 255;
                        image[z++] = ALPHA;
                    }
                }
            }
        }
    }
    error = lodepng_encode32_file(filename, image, img.width, img.height);
    if(error){
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        assert(0);
    }
    free(image);
}

Im *allocateImage(uint32_t width, uint32_t height){
    uint32_t i;
    Im *img;
    uint8_t **image;
    img = (Im*) calloc(1, sizeof(Im));
    image = (uint8_t**) calloc(height, sizeof(uint8_t*));
    for(i = 0; i < height; i ++)
        image[i] = (uint8_t*) calloc(width, sizeof(uint8_t));
    img->width = width;
    img->height = height;
    img->tab = image;
    return img;
}

void freeImage(Im *img){
    uint32_t i;
    for(i = 0; i < img->height; i ++)
        free(img->tab[i]);
    free(img->tab);
    free(img);
}

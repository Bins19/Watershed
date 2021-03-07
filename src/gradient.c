/*
Bina BADIANE
11928259
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "lodepng.h"
#include "gradient.h"

uint8_t *bounds(Im img, int32_t borne_inf1, int32_t borne_sup1, int32_t borne_inf2, int32_t borne_sup2){
    uint8_t *b;
    int32_t i, j;
    b = (uint8_t*) malloc(2 * sizeof(uint8_t));
    if(b == NULL){
        fprintf(stderr, "Memory allocation error (6)\n");
        assert(0);
    }
    while(borne_inf1 < 0)
        borne_inf1 ++;
    while(borne_inf2 < 0)
        borne_inf2 ++;
    b[0] = img.tab[borne_inf1][borne_inf2];
    b[1] = img.tab[borne_inf1][borne_inf2];
    for(i = borne_inf1; i <= borne_sup1; i ++){
        for(j = borne_inf2; j <= borne_sup2; j ++){
            if(i < img.height && j < img.width){
                if(img.tab[i][j] > b[0])
                    b[0] = img.tab[i][j];
                if(img.tab[i][j] < b[1])
                    b[1] = img.tab[i][j];
            }
        }
    }
    return b;
}

Im *calculateGradient(Im img, int32_t r){
    Im *gradient;
    uint32_t height, width;
    uint8_t *b;
    int32_t i, j;
    height = img.height;
    width = img.width;
    gradient = allocateImage(width, height);
    for(i = 0; i < height; i ++){
        for(j = 0; j < width; j ++){
            b = bounds(img, i-r, i+r, j-r, j+r);
            gradient->tab[i][j] = b[0] - b[1];
            free(b);
        }
    }
    return gradient;
}

/*
Bina BADIANE
11928259
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "lodepng.c"
#include "images.c"
#include "gradient.c"
#include "watershed.c"

int main(int argc, char **argv){
    srand(time(NULL));
    clock_t begin, end;
    double time_spent;
    uint32_t i;
    Im img, img_markers;
    Im *grad;
    size_t size;
    char *path1;
    char *path2;
    char *path3;
    char *name_img;
    char *name_img_markers;
    char *name_img_processed;

    begin = clock();

    size = strlen("../img/") + strlen(argv[2]) + 1;
    path1 = (char *) malloc(size);
    strcpy(path1, "../img/");
    strcat(path1, argv[2]);

    size = strlen(path1) + 2;
    path2 = (char *)malloc(size);
    strcpy(path2, path1);
    strcat(path2, "/");
    size = strlen(path2) + strlen(argv[2]) + 1;
    path3 = (char *)malloc(size);
    strcpy(path3, path2);
    strcat(path3, argv[2]);

    size = strlen(path3) + 5;
    name_img = (char *)malloc(size);
    strcpy(name_img, path3);
    strcat(name_img, ".png");

    size = strlen(path3) + 15;
    name_img_markers = (char *)malloc(size);
    strcpy(name_img_markers, path3);
    strcat(name_img_markers, "_marqueurs.png");

    img = readImage(name_img);
    img_markers = readImage(name_img_markers);
    grad = calculateGradient(img, 1);
    calculateWatershed(*grad, img_markers);

    if(!(strcmp(argv[1], "-grey"))) {
        size = strlen(path3) + 14;
        name_img_processed = (char *)malloc(size);
        strcpy(name_img_processed, path3);
        strcat(name_img_processed, "_lpe_gris.png");

        writeImage(img_markers, name_img_processed);
    } else if(!(strcmp(argv[1], "-color"))) {
        size = strlen(path3) + 18;
        name_img_processed = (char *)malloc(size);
        strcpy(name_img_processed, path3);
        strcat(name_img_processed, "_lpe_couleurs.png");

        writeImageColor(img_markers, name_img_processed);
    } else if(!(strcmp(argv[1], "-contour"))){
        size = strlen(path3) + 17;
        name_img_processed = (char *)malloc(size);
        strcpy(name_img_processed, path3);
        strcat(name_img_processed, "_lpe_contour.png");

        writeImageContour(img, img_markers, name_img_processed);
    } else {
        printf("Wrong option. Choose -grey, -color or -contour\n");
        return EXIT_FAILURE;
    }
    freeImage(grad);

    for(i = 0; i < img.height; i ++)
        free(img.tab[i]);
    free(img.tab);

    for(i = 0; i < img_markers.height; i ++)
        free(img_markers.tab[i]);
    free(img_markers.tab);

    free(path1);
    free(path2);
    free(path3);
    free(name_img);
    free(name_img_markers);
    free(name_img_processed);

    end = clock();
    time_spent = (double) (end - begin)/CLOCKS_PER_SEC;
    printf("Temps du programme : %lf s\n", time_spent);
    return EXIT_SUCCESS;
}

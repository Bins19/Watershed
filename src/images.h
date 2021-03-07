/*
Bina BADIANE
11928259
*/

/* data structure representing an image: a width, a height and a
dot matrix */
typedef struct{
    uint32_t width;
    uint32_t height;
    uint8_t **tab;
}Im;

// function reading a PNG image and storing it in a variable of type Im
Im readImage(char *filename);
// function writing the image stored in img to a file named filename
void writeImage(Im img, char *filename);
/* function that writes a segmented image with two colors randomly chosen to a
file named filename */
void writeImageColor(Im img, char *filename);
// function that writes a segemented image with the contour colored
void writeImageContour(Im img, Im img_watershed, char *filename);
// function allocating memory for an image
Im *allocateImage(uint32_t width, uint32_t height);
// function freeing the img data structure from memory
void freeImage(Im *img);

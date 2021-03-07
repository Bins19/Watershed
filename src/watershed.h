/*
Bina BADIANE
11928259
*/

// data strcture which represents a pixel
typedef struct{
    uint32_t i;
    uint32_t j;
}Pixel;

typedef struct maillon{
    Pixel p;
    struct maillon *next;
}Maillon;

typedef struct{
    Maillon *head;
    Maillon *tail;
}Liste;

typedef struct{
    Liste **tab;
}Tab_hachage;

// function that intializes a link
Maillon *initMaillon(uint32_t i, uint32_t j);
// funciton that initializes a list
Liste *iniList();
// function that initializes a hash table
Tab_hachage *initTabHash();
// function which is true when th is empty and false otherwise
_Bool isEmpty(Tab_hachage *th);
// function that removes the head of the first list which his head is not empty
Pixel remMinTabHash(Tab_hachage *th);
// function that adds a pixel at the head of a list
void addHeadList(Liste *L, uint32_t i, uint32_t j);
// function that adds a pixel in a hash table
void addTabHash(Tab_hachage *th, uint32_t i, uint32_t j, Im img);
/* function that calculates and returns the waterhed segementation calculated
on the gradient image and the markers image and puts it in M */
void calculateWatershed(Im gradient, Im M);

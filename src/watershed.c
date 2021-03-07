/*
Bina BADIANE
11928259
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "lodepng.h"
#include "watershed.h"

#define SIZE 256

Maillon *initMaillon(uint32_t i, uint32_t j){
    Maillon *m;
    m = (Maillon*) malloc(sizeof(Maillon));
    if(m == NULL){
        fprintf(stderr, "Memory allocation error (6)\n");
        assert(0);
    }
    m->p.i = i;
    m->p.j = j;
    m->next = NULL;
    return m;
}

Liste *initList(){
    Liste *L;
    L = (Liste*) malloc(sizeof(Liste));
    if(L == NULL){
        fprintf(stderr, "Memory allocation error (7)\n");
        assert(0);
    }
    L->head = NULL;
    L->tail = NULL;
    return L;
}

Tab_hachage *initTabHash(){
    Tab_hachage *th;
    uint32_t i;
    th = (Tab_hachage *) malloc(sizeof(Tab_hachage));
    if(th == NULL){
        fprintf(stderr, "Memory allocation error (8)\n");
        assert(0);
    }
    th->tab = (Liste **) malloc(SIZE*sizeof(Liste*));
    if(th->tab == NULL){
        fprintf(stderr, "Memory allocation error (9)\n");
        assert(0);
    }
    for(i = 0; i < SIZE; i++)
        th->tab[i] = initList();
    return th;
}

_Bool isEmpty(Tab_hachage *th){
    _Bool empty;
    uint32_t i;
    i = 0;
    while(i < SIZE && th->tab[i]->head == NULL)
        i ++;
    empty = (i == SIZE) ? 1 : 0;
    return empty;
}

Pixel remMinTabHash(Tab_hachage *th){
    uint8_t i;
    Maillon *m;
    Pixel p;
    i = 0;
    while(th->tab[i]->head == NULL)
        i ++;
    m = th->tab[i]->head;
    p = m->p;
    th->tab[i]->head = m->next;
    free(m);
    if(th->tab[i]->head == NULL)
        th->tab[i]->tail = NULL;
    return p;
}

void addHeadList(Liste *L, uint32_t i, uint32_t j){
    Maillon *m;
    m = initMaillon(i, j);
    m->next = L->head;
    L->head = m;
    if(L->tail == NULL)
        L->tail = m;
}

void addTabHash(Tab_hachage *th, uint32_t i, uint32_t j, Im img){
    uint8_t position;
    position = img.tab[i][j];
    addHeadList(th->tab[position], i, j);
}

void calculateWatershed(Im gradient, Im M){
    Tab_hachage *th;
    uint32_t height, width, i, j, k, l;
    Pixel p;
    th = initTabHash(M.height);
    height = M.height;
    width = M.width;
    for(i = 0; i < height; i ++){
        for(j = 0; j < width; j ++){
                if(M.tab[i][j] != 0)
                    addTabHash(th, i, j, gradient);
        }
    }
    while(!(isEmpty(th))){
        p = remMinTabHash(th);
        i = p.i;
        j = p.j;
        for(k = i-1; k < i+2; k ++){
            for(l = j-1; l < j+2; l ++){
                if(0 <= k && k < height && 0 <= l && l < width){
                    if(M.tab[k][l] == 0){
                        M.tab[k][l] = M.tab[i][j];
                        addTabHash(th, k, l, gradient);
                    }
                }
            }
        }
    }
    for(i = 0; i < SIZE; i ++)
        free(th->tab[i]);
    free(th->tab);
    free(th);
}

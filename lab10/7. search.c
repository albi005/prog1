#include "stdio.h"
#include <stdlib.h>
#include "debugmalloc.h"
 
typedef struct ListaElem {
    int adat;
    struct ListaElem *kov;
} ListaElem;
 
 
/* létrehoz egy listát, benne egy csomó számmal */
ListaElem *lista_letrehoz(void) {
    int szamok[] = { 8, 14, 13, 17, 1, 19, 16, 5, 3, 11, 2,
                     15, 9, 10, 6, 22, 4, 7, 18, 27, -1 };
    ListaElem *lis = NULL;
 
    for (int i = 0; szamok[i] != -1; ++i) {
        ListaElem *u;
        u = (ListaElem*) malloc(sizeof(ListaElem));
        u->kov = lis;
        u->adat = szamok[i];
        lis = u;
    }
    return lis;
}

void free_list(ListaElem *p) {
    while (p != NULL) {
        ListaElem *next = p->kov;
        free(p);
        p = next;
    }
}

ListaElem *search(ListaElem *p, int val) {
    while (p != NULL) {
        ListaElem *next = p->kov;
        if (p->adat == val) return p;
        p = next;
    }
    return NULL;
}

int main(void) {
    ListaElem *eleje;
    
    eleje = lista_letrehoz();

    ListaElem *res = search(eleje, 5);
    printf("%d\n", res->adat);
    
    free_list(eleje);
    
    return 0;
}

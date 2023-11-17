#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
 
typedef struct BiFa {
    int ertek;
    struct BiFa *bal, *jobb;
} BiFa;
 
BiFa *beszur(BiFa *gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa *uj = (BiFa*) malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */ gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}
 
void print(BiFa* root) {
    if (root == NULL) return;
    print(root->bal);
    printf("%d ", root->ertek);
    print(root->jobb);
}

int count(BiFa* root) {
    if (root == NULL) return 0;
    return count(root->bal) + count(root->jobb) + 1;
}

int sum(BiFa* root) {
    if (root == NULL) return 0;
    return sum(root->bal) + sum(root->jobb) + root->ertek;
}

BiFa* search(BiFa* root, int target) {
    if (root == NULL) return NULL;
    if (root->ertek == target) return root;
    if (target < root->ertek)
        return search(root->bal, target);
    else return search(root->jobb, target);
}

void negate(BiFa* root) {
    if (root == NULL) return;
    root->ertek *= -1;
    negate(root->jobb);
    negate(root->bal);
}

BiFa* negated_search(BiFa* root, int target) {
    if (root == NULL) return NULL;
    if (root->ertek == target) return root;
    if (target > root->ertek)
        return negated_search(root->bal, target);
    else return negated_search(root->jobb, target);
}

void invert(BiFa* root) {
    if (root == NULL) return;
    BiFa* tmp = root->bal;
    root->bal = root->jobb;
    root->jobb = tmp;
    invert(root->bal);
    invert(root->jobb);
}

void free_bifa(BiFa* root) {
    if (root == NULL) return;
    free_bifa(root->bal);
    free_bifa(root->jobb);
    free(root);
}
 
int main(void) {
    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0};
    BiFa *gyoker = NULL;
    for (int i = 0; minta[i] > 0; i++)
        gyoker = beszur(gyoker, minta[i]);
 
    /* Ide tedd be a kipróbálandó függvények hívásait! */
    print(gyoker);
    printf("\n%d darab\n", count(gyoker));
    printf("Osszeg: %d\n", sum(gyoker));
    printf("1. talalat: %p\n", search(gyoker, 15));
    printf("2. talalat: %p\n", search(gyoker, 0));
    printf("3. talalat: %p\n", search(gyoker, 56));
    printf("4. talalat: %p\n", search(gyoker, 69));
    printf("5. talalat: %p\n", search(gyoker, -1));

    negate(gyoker);
    print(gyoker);
    printf("\n1. negalt talalat: %p\n", search(gyoker, -15));
    printf("2. negalt talalat: %p\n", search(gyoker, -0));
    printf("3. negalt talalat: %p\n", search(gyoker, -56));
    printf("4. negalt talalat: %p\n", search(gyoker, -69));
    printf("5. negalt talalat: %p\n", search(gyoker, 1));
    printf("1. negalt negalt talalat: %p\n", negated_search(gyoker, -15));
    printf("2. negalt negalt talalat: %p\n", negated_search(gyoker, 0));
    printf("3. negalt negalt talalat: %p\n", negated_search(gyoker, -56));
    printf("4. negalt negalt talalat: %p\n", negated_search(gyoker, -69));
    printf("5. negalt negalt talalat: %p\n", negated_search(gyoker, 1));

    invert(gyoker);
    print(gyoker);
    printf("\n1. negalt talalat: %p\n", search(gyoker, -15));
    printf("2. negalt talalat: %p\n", search(gyoker, -0));
    printf("3. negalt talalat: %p\n", search(gyoker, -56));
    printf("4. negalt talalat: %p\n", search(gyoker, -69));
    printf("5. negalt talalat: %p\n", search(gyoker, 1));
    printf("1. negalt negalt talalat: %p\n", negated_search(gyoker, -15));
    printf("2. negalt negalt talalat: %p\n", negated_search(gyoker, 0));
    printf("3. negalt negalt talalat: %p\n", negated_search(gyoker, -56));
    printf("4. negalt negalt talalat: %p\n", negated_search(gyoker, -69));
    printf("5. negalt negalt talalat: %p\n", negated_search(gyoker, 1));

    free_bifa(gyoker);
 
    return 0;
}

#include <stdio.h>

int main() {
    // Kiírom a kérdést
    printf("Mekkora legyen a szakasz? ");
    // Felveszek egy változót
    int l;
    // Beolvasok a parancssorból a változóba
    scanf("%d", &l);

    // Kiírom az első +-t
    printf("+");
    // Felveszek egy i változót és addig növelem egyesével amíg kisebb l-nél.
    // Minden növelés után kiírok egy --t és egy új sort.
    for (int i = 0; i < l; i++) printf("-");
    // Kiírom az második +-t
    printf("+");
    
}
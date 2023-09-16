#include <stdio.h>
#include <stdbool.h>
 
int main(void) {
    int tomb[10];
 
    for (int i = 0; i < 10; i += 1)
        tomb[i] = i * 10;
 
    int i = 0;
    while (true) {
        printf("%d. elem: %d\n", i, tomb[i]);
        i += 1;
    }
 
    return 0;
}

// 1. Egy 10 int hosszú tömböt feltölt 0-tól 90-ig a 10-zel osztható számokkal,
//    majd kiírja a tömböt értékeit és az utána következő memóriából is kiír 10 int-et.
//    Olyan memóriát olvas be és ír ki ami másra vanhasználva ezért az értéke véletlenszerű.
// 2. A while(true) végtelen ciklus eredményez. A tömb értékein nem változtat.

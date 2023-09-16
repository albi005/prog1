#include <stdio.h>
 
int main(void) {
    char betu;
    while (scanf("%c", &betu) == 1)
        printf("betu='%c', betu=%d\n", betu, betu);
 
    return 0;
}

// 1. Kiírja a bevitt karakterekhez tartozó ASCII kódot
// 2. A ctrl+d megnyomásával lehet kilépni. Ilyenkor end of file-t olvas be a scanf és az értéke 1 lesz.
// 3. Mert a karakter és az ASCII kódot is kiírja.
// 4. Beolvas a betu változóba és igazzá válik ha end of file-t kap.


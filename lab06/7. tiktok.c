#include <stdio.h>

void print(unsigned long x) {
    for (int i = 31; i >= 0; i--)
        printf("%c", 0 != (x & (1 << i)) ? '#' : ' ');
    printf("\n");
}

int main(void) {
    unsigned long szamok[8] = { 0U, 1931988508U, 581177634U, 581374240U,
                            581177632U, 581177634U, 1919159836U, 0U };
    // 65535d==0000FFFFh: a 32 bit alsó 16 bitje igaz

    for (int i = 0; i < 8; i++)
        print(szamok[i]);

    // csak az alsó 16 bitet tartja meg
    for (int i = 0; i < 8; i++)
        print(szamok[i] & 65535);

    // csak az felső 16 bitet tartja meg
    for (int i = 0; i < 8; i++)
        print(szamok[i] & ~65535);

    // igazzá teszi az alsó 16 bitet
    for (int i = 0; i < 8; i++)
        print(szamok[i] | 65535);

    // igazzá teszi a felső 16 bitet
    for (int i = 0; i < 8; i++)
        print(szamok[i] | ~65535);

    // megfordítja az alsó 16 bitet
    for (int i = 0; i < 8; i++)
        print(szamok[i] ^ 65535);

    // megfordítja a felső 16 bitet
    for (int i = 0; i < 8; i++)
        print(szamok[i] ^ ~65535);

    return 0;
}

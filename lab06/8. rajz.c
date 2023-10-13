#include <stdio.h>

unsigned long szamok[24];

void println(unsigned long x) {
    for (int i = 31; i >= 0; i--)
        printf("%c", 0 != (x & (1 << i)) ? '#' : ' ');
    printf("\n");
}

void print() {
    for (int i = 0; i < 24; i++)
        println(szamok[i]);
}

void draw(int x, int y) {
    szamok[y] |= 1 << (31 - x);
}

int main(void) {
    for (int i = 0; i < 24; i++)
        szamok[i] = 0;
    print();

    draw(1, 5);
    draw(1, 4);
    draw(1, 3);
    draw(1, 2);
    draw(1, 5);
    draw(2, 1);
    draw(2, 3);
    draw(3, 1);
    draw(3, 3);
    draw(4, 5);
    draw(4, 4);
    draw(4, 3);
    draw(4, 2);
    draw(4, 5);

    draw(6, 5);
    draw(6, 4);
    draw(6, 3);
    draw(6, 2);
    draw(6, 1);
    draw(7, 5);
    draw(8, 5);
    draw(9, 5);

    draw(11, 5);
    draw(11, 4);
    draw(11, 3);
    draw(11, 2);
    draw(11, 1);
    draw(12, 1);
    draw(12, 3);
    draw(12, 5);
    draw(13, 1);
    draw(13, 3);
    draw(13, 5);
    draw(14, 2);
    draw(14, 4);

    draw(16, 5);
    draw(16, 4);
    draw(16, 3);
    draw(16, 2);
    draw(16, 1);
    print();


    return 0;
}

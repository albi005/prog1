#include <stdio.h>

int main() {
    unsigned long int x = 1;
    for (int i = 0; i < 40; i++)
        printf("%lu\n", x << i);

    unsigned char x1 = 1;
    unsigned short int x2 = 1;
    unsigned int x3 = 1;
    unsigned long int x4 = 1;
    unsigned long long int x5 = 1;

    int i = 0;
    while (x1 <<= 1 > 0) i++;
    printf("unsigned char: %d\n", i+1);

    i = 0;
    while (x2 <<= 1 > 0) i++;
    printf("unsigned short int: %d\n", i+1);

    i = 0;
    while (x3 <<= 1 > 0) i++;
    printf("unsigned int: %d\n", i+1);

    i = 0;
    while (x4 <<= 1 > 0) i++;
    printf("unsigned long int: %d\n", i+1);

    i = 0;
    while (x5 <<= 1 > 0) i++;
    printf("unsigned long long int: %d\n", i+1);
}


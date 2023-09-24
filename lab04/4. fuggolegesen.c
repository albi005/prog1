#include <stdio.h>

int main() {
    char nev[100];
    printf("Kerem a nevet: ");
    scanf("%s", nev);
    char* p = nev;
    while (*p != '\0') {
        printf("%c\n", *p);
        ++p;
    }
}

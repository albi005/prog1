#include <stdio.h>

void trim(char src[], char dest[]) {
    char* last = src;
    for (char* p = src; *p != '\0'; p++)
        if (*p != ' ')
            last = p;

    char* start = src;
    while (*(++start) == ' ');

    for (char* p = start; p <= last; p++)
        dest[p - start] = *p;
    dest[last - start + 1] = '\0';
}

int main() {
    char src[] = "  helló, mizu?   ";
    char dest[30];
    trim(src, dest);
    printf("%s\n", dest);
}


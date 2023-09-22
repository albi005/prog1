#include <stdio.h>
#include <math.h>

int main() {
    int szam;
    printf("Adj meg egy szamot: ");
    scanf("%d", &szam);

    int max_width = floor(log10(szam));
    
    int oszto = 2;
    while (szam > 1) {
        if (szam%oszto==0) {
            int width = floor(log10(szam));
            for (int i = 0; i < max_width - width; i++)
                printf(" ");
            printf("%d|%d\n", szam, oszto);
            szam /= oszto;
        }
        else
            oszto++;
    };

    for (int i = 0; i < max_width - 1; i++)
        printf(" ");
    printf("1|\n");
}

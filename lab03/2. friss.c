#include <stdio.h>

int main() {
    double arr[] = { 2.5, -69, 5.4, -8, -7.7, 6, 2.9, -10, -3, 9.8 };

    printf("Összesen 10 szám van.\n");
    for (int i = 0; i < 10; i++)
        printf("[%d]=%g ", i, arr[i]);

    int negLen = 0;
    double negIndeces[10];
    for (int i = 0; i < 10; i++) {
        double curr = arr[i];
        if (curr >= 0)
            continue;
        negIndeces[negLen] = i;
        negLen++;
    }

    printf("\n\nEbből %d szám negatív.\n", negLen);
    for (int i = 0; i < negLen; i++) {
        int index = negIndeces[i];

        printf("[%d]=%g ", index, arr[index]);
    }
};


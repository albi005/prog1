#include <stdio.h>

int main() {
    int arr[] = { 25, 69, 54, 8, 77, 6, 29, 10, 3, 98 };
    printf("A tömb:");

    int min = arr[0];
    int minhely = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minhely = i;
        }
        printf(" [%d]=%d", i, arr[i]);
    }
    printf("\nA legkisebb szám: %d\n", min);
    printf("A legkisebb indexe: %d\n", minhely);

    printf("Jelölve:");
    for (int i = 0; i < 10; i++) {
        printf(" %d", arr[i]);
        if (arr[i] == min)
            printf("[MIN]");
    }
}

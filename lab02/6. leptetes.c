#include <stdio.h>

int main() {
    char pitagorasz[10] = { 'P', 'i', 't', 'a', 'g', 'o', 'r', 'a', 's', 'z' };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) printf(" %c", pitagorasz[j]);
        printf("\n");

        char last = pitagorasz[0];
        for (int j = 0; j < 9; j++)
            pitagorasz[j] = pitagorasz[j + 1];
        pitagorasz[9] = last;
    }
}

#include <stdio.h>

int* search(int len, int[] arr, int target) {
    for (int i = 0; i < len; ++i) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return NULL;
}


int main() {
    double tomb[5] = { 1, 2, 3, 4, 5 };
    int* found = search(5, tomb, 3);
    int index = found - tomb;
    int* not_found = search(5, tomb, 6);
}

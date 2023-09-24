#include <stdio.h>

int* search(int len, int arr[], int target) {
    for (int* i = arr; i < arr+len; ++i) {
        if (*i == target) {
            return i;
        }
    }
    return NULL;
}


int main() {
    int tomb[5] = { 1, 2, 3, 4, 5 };
    int* found = search(5, tomb, 3);
    printf("found points to %d\n", *found);
    int index = found - tomb;
    int* not_found = search(5, tomb, 6);
}

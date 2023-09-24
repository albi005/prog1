#include <stdio.h>

int search(int len, int arr[], int target) {
    for (int i = 0; i < len; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


int main() {
    int tomb[5] = { 1, 2, 3, 4, 5 };

    int found = search(5, tomb, 3);
    printf("found: %d\n", found);
    
    int not_found = search(5, tomb, 6);
    printf("not_found: %d\n", not_found);
}

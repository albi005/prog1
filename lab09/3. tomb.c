#include <stdio.h>

void iter_fw(int t[], int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", t[i]);
    printf("\n");
}
void rec_fw(int t[], int len) {
    if (len < 1) {
        printf("\n");
        return;
    }
    printf("%d ", *t);
    rec_fw(t + 1, len - 1);
}
void iter_bw(int t[], int len) {
    for (int i = len - 1; i >= 0; i--)
        printf("%d ", t[i]);
    printf("\n");
}
void rec_bw(int t[], int len) {
    if (len < 1) {
        printf("\n");
        return;
    }
    printf("%d ", t[len - 1]);
    rec_bw(t, len - 1);
}

int main() {
    int t1[] = {1,2,3,4,5};
    int t2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    iter_fw(t1, 5);
    iter_bw(t1, 5);
    rec_fw(t1, 5);
    rec_bw(t1, 5);
    iter_fw(t2, 10);
    iter_bw(t2, 10);
    rec_fw(t2, 10);
    rec_bw(t2, 10);
}

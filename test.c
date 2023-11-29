#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    FILE *f = fopen("owners", "r");

    uint64_t ize;
    fscanf(f, "%" SCNu64, &ize);
    fscanf(f, "%" SCNu64, &ize);
}


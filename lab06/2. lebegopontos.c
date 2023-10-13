#include <stdio.h>
#include <math.h>
 
int main(void) {
    printf("1. %f\n", 1.23456789123456789123456789e40);
    printf("2. %g\n", 1e40);
    printf("3. %s\n", 1e3+1 == 1e3 ? "igaz" : "hamis");
    printf("4. %s\n", 1e30+1 == 1e30 ? "igaz" : "hamis"); // 10^30=inf. inf+1=inf
    printf("5. %g\n", pow(10, 40) / pow(10, -40));
    printf("6. %g\n", powf(10, 40) / powf(10, -40)); // 10^40-t nem fér el float-ban, ezért inf-ként tárolja.  inf*valami=inf
 
    return 0;
}

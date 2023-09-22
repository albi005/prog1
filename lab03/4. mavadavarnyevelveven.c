#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isMgh(char c) {
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}
 
int main(void) {
    char c;
    while (scanf("%c", &c) != EOF) {
        char lower = tolower(c);
        if (isMgh(lower))
            printf("%cv%c", c, lower);
        else
            printf("%c", c);
    }
 
    return 0;
}


#include <stdio.h>

int main() {
    char str[] = "Hello";
    str[5] = '!';
    str[6] = 'a';
    
    printf("%s\n", str);
}

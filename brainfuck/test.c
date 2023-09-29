#include <stdio.h>

int main() {
    char ch;

    printf("%d", EOF);

    printf("Enter characters (Ctrl+D or Ctrl+Z to indicate end of input):\n");

    scanf("%c", &ch);
        // Process the character
        printf("Read character: %c (%d)\n", ch, ch);

    printf("End of file reached.\n");

    return 0;
}


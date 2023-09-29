#include <stdio.h>

int main() {
    char code[] = ",+[-.,+]";

    char mem[32768];
    char *p = mem;
    char *end = mem + 32768;

    while (++p < end)
        *p = 0;

    p = mem;
    for (int i = 0; code[i] != '\0'; i++) {
        if (p < mem || p >= end) {
            printf("[ERROR] went out of bounds\n");
            return 0;
        }
        char cmd = code[i];
        switch (cmd) {
            case '+':
                ++*p;
                break;
            case '-':
                --*p;
                break;
            case '[':
                break;
            case ']':
                if (*p == 0)
                    break;

                int stack = 1;
                while (stack) {
                    i--;
                    if (code[i] == '[')
                        stack--;
                    if (i < 0) {
                        printf("[ERROR] unmatched '['\n");
                        return 0;
                    }
                }
                break;
            case '.':
                printf("%c", *p);
                break;
            case ',':
                if (!scanf("%c", p))
                    *p = -1;
                break;
            case '>':
                p++;
                break;
            case '<':
                p--;
                break;
        }
    }
}

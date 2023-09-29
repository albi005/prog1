#include <stdio.h>

int main() {
    // brainfuck code created using https://copy.sh/brainfuck/text.html
    char programkod[] = "--[----->+<]>-----.+++++++++++.----------.[-->+<]>.---.+[--->+<]>+++.[--->+<]>---.";

    char mem[32768];
    char *p = mem;
    char *end = mem + 32768;
    int stack;

    while (++p < end)
        *p = 0;

    p = mem;
    for (int i = 0; programkod[i] != '\0'; i++) {
        if (p < mem || p >= end) {
            printf("[ERROR] went out of bounds\n");
            return 0;
        }
        char cmd = programkod[i];
        switch (cmd) {
            case '+':
                ++*p;
                break;
            case '-':
                --*p;
                break;
            case '[':
                if (*p) break;

                stack = 1;
                while (stack) {
                    i++;
                    if (i == '\0') {
                        printf("[ERROR] unmatched '['\n");
                        return 0;
                    }

                    if (programkod[i] == '[')
                        stack++;
                    else if (programkod[i] == ']')
                        stack--;
                }
                break;
            case ']':
                stack = 1;
                while (stack) {
                    i--;
                    if (i < 0) {
                        printf("[ERROR] unmatched ']'\n");
                        return 0;
                    }

                    if (programkod[i] == '[')
                        stack--;
                    else if (programkod[i] == ']')
                        stack++;
                }
                i--;
                break;
            case '.':
                printf("%c", *p);
                break;
            case ',':
                if (scanf("%c", p) < 0)
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

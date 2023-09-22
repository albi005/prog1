#include <stdio.h>
#include <stdbool.h>

int cmd0(int a) { return 1; }
int cmd1(int a) { return a + 1; }
int cmd2(int a) { return -a; }
int cmd3(int a) { return a * 2; }

int main() {
    int a = 1;

    int cmd;
    bool stop = false;
    do {
        printf("a = %d\n", a);
        printf(
            "0. Alapertek visszaallitasa (a = 1)\n"
            "1. Hozzaad 1-et\n"
            "2. Megforditja az elojelet\n"
            "3. Szorozza 2-vel\n"
            "9. Kilepes\n");
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                a = cmd0(a);
                break;
            case 1:
                a = cmd1(a);
                break;
            case 2:
                a = cmd2(a);
                break;
            case 3:
                a = cmd3(a);
                break;
            case 9:
                stop = true;
                printf("Goodbye!\n");
                break;
            default:
                printf("Ismeretlen parancs.\n");
                break;
        }
    } while (!stop);
}


#include <stdlib.h>
#include <stdio.h>

static char* sort_beolvas_de_tenyleg(int index) {
    char c;
    if (scanf("%c", &c) < 1 || c == '\n') {
        int meret = index + 1;
        char *s = (char*)malloc(meret * sizeof(char));
        s[index] = '\0';
        return s;
    }

    char *s = sort_beolvas_de_tenyleg(index + 1);
    s[index] = c;
    return s;
}

/* A függvény beolvas egy teljes sort (enterig vagy fájl vége jelig) a
 * szabványos bemenetről, és visszaadja egy dinamikusan foglalt sztringben.
 * A sztring nullával van lezárva, az entert nem tartalmazza. A hívó
 * felelőssége a free()-t meghívni a kapott pointerre. */
char* sort_beolvas(void) {
    return sort_beolvas_de_tenyleg(0);
}

int main() {
    char *s = sort_beolvas();
    printf("%s", s);
    free(s);
}

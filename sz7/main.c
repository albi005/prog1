#include <stdio.h>
#include <stdlib.h>

typedef struct Palacsinta {
    int meret;
    struct Palacsinta* alatta;
    struct Palacsinta* felette;
} Palacsinta;

// strazsas, duplan lancolt lista
typedef struct Torony {
    Palacsinta also;
    Palacsinta felso;
} Torony;

void tetejere(Torony* torony, int meret) {
    Palacsinta* uj = malloc(sizeof(Palacsinta));
    uj->meret = meret;
    uj->alatta = torony->felso.alatta;
    uj->felette = &torony->felso;
    torony->felso.alatta->felette = uj;
    torony->felso.alatta = uj;
}

void megfordit(Palacsinta* also, Torony* torony) {
    Palacsinta* eredeti = also;
    Palacsinta* alatta = also->alatta;
    Palacsinta* megforditott = &torony->felso;

    while (eredeti != &torony->felso) {
        Palacsinta* atrakott = eredeti;
        Palacsinta* kovetkezo = eredeti->felette;
        megforditott->alatta = atrakott;
        atrakott->felette = megforditott;
        megforditott = atrakott;
        eredeti = kovetkezo;
    }

    megforditott->alatta = alatta;
    alatta->felette = megforditott;
}

Palacsinta* legnagyobb(Palacsinta* also, Palacsinta* felso) {
    if (also == felso) return NULL;

    Palacsinta* felette = legnagyobb(also->felette, felso);
    if (felette != NULL && felette->meret > also->meret)
        return felette;
    else
        return also;
}

void kiirdb(char c, int db) {
    for (int i = 0; i < db; i++)
        putchar(c);
}

// https://en.wikipedia.org/wiki/ANSI_escape_code
void kirajzol(Torony* torony) {
    int r = legnagyobb(&torony->also, &torony->felso)->meret + 1;

    printf("\x1b[33m"); // sarga

    Palacsinta* felso = torony->felso.alatta;
    while (felso != &torony->also) {
        kiirdb(' ', r - felso->meret);
        kiirdb('_', felso->meret * 2);
        kiirdb(' ', r - felso->meret);
        putchar('\n');
        felso = felso->alatta;
    }

    printf("\x1b[0m"); // visszaallit
    putchar('-');
    kiirdb('_', r * 2 - 2);
    putchar('-');
    printf("\n\nEnter a folytatashoz...");
    while (getchar() != '\n') {}
    printf("\x1b[13F"); // kurzor 13 sorral fel
}

void rendez(Torony* torony) {
    Palacsinta* legfelso_rendezett = &torony->also;
    while (legfelso_rendezett != torony->felso.alatta) {
        Palacsinta* legnagyobb_rendezetlen = legnagyobb(legfelso_rendezett->felette, &torony->felso);
        megfordit(legnagyobb_rendezetlen, torony);
        kirajzol(torony);
        megfordit(legfelso_rendezett->felette, torony);
        kirajzol(torony);
        legfelso_rendezett = legnagyobb_rendezetlen;
    }
}

int main() {
    Torony torony;
    torony.also.felette = &torony.felso;
    torony.felso.alatta = &torony.also;

    int meretek[] = { 1,  7,  9,  6,  5,  8, 10,  3,  4,  2 };
    for (int i = 0; i < 10; i++)
        tetejere(&torony, meretek[i]);
    kirajzol(&torony);

    rendez(&torony);

    printf("\x1b[13E"); // kurzor 13 sorral le
}

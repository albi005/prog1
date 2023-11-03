#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "animal.h"
#include "utils.h"

static void add_animal(Animals *animals, Animal animal) {
    animals->length++;
    if (animals->length > animals->capacity) {
        if (animals->capacity < 10)
            animals->capacity = 10;
        else 
            animals->capacity *= 2;
        animals->data = (Animal*)realloc(animals->data, animals->capacity * sizeof(Animal));
    }
    animals->data[animals->length - 1] = animal;
}

Animals *open_animals(Owners *owners) {
    FILE *f = fopen("animals", "r");

    Animals *animals = malloc(sizeof(Animals));
    animals->file = f;
    animals->length = 0;
    animals->capacity = 0;
    animals->data = NULL;

    if (f == NULL)
        return animals;

    while (1) {
        Animal animal;

        size_t owner_id;

        if (fscanf(f, "%zd ", &animal.id) < 1)
            break;
        fscanf(f, "%zd ", &owner_id);
        animal.name = read_line(f);
        animal.species = read_line(f);

        // https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
        size_t l = 0;
        size_t r = owners->length - 1;
        while (l <= r) {
            size_t m = (l + r) / 2;
            if (owners->data[m].id < owner_id)
                l = m + 1;
            else if (owners->data[m].id > owner_id)
                r = m - 1;
            else {
                animal.owner = &owners->data[m];
                break;
            }
        }
        
        if (animal.owner == NULL) {
            printf("Error: owner with id %zd not found!\n", owner_id);
            exit(1);
        }

        add_animal(animals, animal);
    }

    return animals;
}

void close_animals(Animals *animals) {
    for (int i = 0; i < animals->length; i++) {
        free(animals->data[i].name);
        free(animals->data[i].species);
    }
    free(animals->data);
    free(animals);
}

Animal *create_animal(Animals *animals, Owner *owner, char *name, char *species);
void remove_animal(Animals *animals, Animal *animal);

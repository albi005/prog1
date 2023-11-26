#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "animal.h"
#include "owner.h"
#include "treatment.h"
#include "utils.h"

Animals* new_animals() {
    Animals *animals = malloc(sizeof(Animals));
    animals->file = NULL;
    animals->count = 0;
    animals->capacity = 0;
    animals->data = NULL;
    return animals;
}

void add_animal(Animals* animals, Animal* animal) {
    animals->count++;
    if (animals->count > animals->capacity) {
        if (animals->capacity < 10)
            animals->capacity = 10;
        else 
            animals->capacity *= 2;
        animals->data = (Animal**)realloc(animals->data, animals->capacity * sizeof(Animal*));
    }
    animals->data[animals->count - 1] = animal;
}

void remove_animal(Animals *animals, Animal *animal) {
    size_t index = animals->count;
    if (animals->file != NULL) index = animal->index;
    else {
        for (size_t i = 0; i < animals->count; i++) {
            if (animals->data[i] == animal)
            {
                index = i;
                break;
            }
        }
    }

    if (index == animals->count) {
        printf("Error: animal not found!\n");
        exit(1);
    }

    animals->count--;
    for (size_t i = index; i < animals->count; i++) {
        animals->data[i] = animals->data[i + 1];

        if (animals->file != NULL)
            animals->data[i]->index = i;
    }
}

Animals* open_animals(Owners *owners) {
    FILE *f = fopen("animals", "r");

    if (f == NULL) {
        printf("Error opening animals file!\n");
        exit(1);
    }

    Animals *animals = new_animals();
    animals->file = f;

    if (f == NULL)
        return NULL;

    while (1) {
        size_t id;

        if (fscanf(f, "%zd ", &id) < 1)
            break;
        size_t owner_id;
        fscanf(f, "%zd ", &owner_id);
        char* name = read_line(f);
        char* species = read_line(f);

        // https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
        Owner* owner = NULL;
        size_t l = 0;
        size_t r = owners->count - 1;
        while (l <= r) {
            size_t m = (l + r) / 2;
            if (owners->data[m]->id < owner_id)
                l = m + 1;
            else if (owners->data[m]->id > owner_id)
                r = m - 1;
            else {
                owner = owners->data[m];
                break;
            }
        }
        if (owner == NULL) {
            printf("Error: owner with id %zd not found!\n", owner_id);
            exit(1);
        }

        Animal* animal = create_animal(animals, owner, name, species);
        animal->id = id;
    }

    return animals;
}

// must be called with only the main animals list loaded from a file
Animal* create_animal(Animals *animals, Owner *owner, char *name, char *species) {
    Animal *animal = malloc(sizeof(Animal));

    if (animals->count == 0)
        animal->id = 1;
    else
        animal->id = animals->data[animals->count - 1]->id + 1;

    animal->owner = owner;
    animal->treatments = new_treatments();
    animal->name = name;
    animal->species = species;
    add_animal(animals, animal);
    animal->index = animals->count - 1;
    add_animal(owner->animals, animal);
    return animal;
}

void free_animal(Animal *animal) {
    free(animal->treatments->data);
    free(animal->treatments);
    free(animal->name);
    free(animal->species);
    free(animal);
}

void delete_animal(Animal *animal, Animals *animals, Treatments *treatments) {
    remove_animal(animals, animal);
    remove_animal(animal->owner->animals, animal);

    for (int i = animal->treatments->count - 1; i >= 0; i--) {
        Treatment *treatment = animal->treatments->data[i];
        delete_treatment(treatment, treatments);
    }

    free_animal(animal);
}

void close_animals(Animals *animals) {
    for (int i = 0; i < animals->count; i++)
        free_animal(animals->data[i]);
    free(animals->data);
    free(animals);
}

#ifndef ANIMAL_H
#define ANIMAL_H

#include "owner.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t id;
    Owner *owner;
    char *name;
    char *species;
} Animal;

typedef struct {
    size_t length;
    size_t capacity;
    Animal *data;
    FILE *file;
} Animals;

Animals *open_animals(Owners *owners);
void close_animals(Animals *animals);

Animal *create_animal(Animals *animals, Owner *owner, char *name, char *species);
void remove_animal(Animals *animals, Animal *animal);

#endif

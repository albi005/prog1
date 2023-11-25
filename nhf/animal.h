#ifndef ANIMAL_H
#define ANIMAL_H

#include <stddef.h>
#include <stdio.h>

typedef struct Owners Owners;
typedef struct Owner Owner;
typedef struct Treatments Treatments;

typedef struct Animal {
    size_t id;
    size_t index;
    Owner *owner;
    Treatments* treatments;
    char *name;
    char *species;
} Animal;
#define ANIMAL_PROPERTY_COUNT 2

typedef struct Animals {
    size_t count;
    size_t capacity;
    Animal** data;
    FILE *file;
} Animals;

Animals* new_animals();
void add_animal(Animals *animals, Animal *animal);
void remove_animal(Animals *animals, Animal *animal);

Animals *open_animals(Owners *owners);
void close_animals(Animals *animals);

Animal *create_animal(Animals *animals, Owner *owner, char *name, char *species);
void delete_animal(Animal *animal, Animals *animals, Treatments *treatments);

#endif

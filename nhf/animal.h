#ifndef ANIMAL_H
#define ANIMAL_H

#include <stddef.h>
#include <stdio.h>

typedef struct Owners Owners;
typedef struct Owner Owner;
typedef struct Treatments Treatments;

typedef struct Animal {
    size_t id;
    size_t index; // Index in the main Animals array
    Owner *owner;
    Treatments* treatments;
    char *name;
    char *species;
} Animal;
#define ANIMAL_PROPERTY_COUNT 2

// Dynamic array of Animals
typedef struct Animals {
    size_t count;
    size_t capacity;
    Animal** data;
    FILE *file;
} Animals;

// Allocate and initialize a new empty Animals array
Animals* new_animals();

// Add an Animal to an Animals array
void add_animal(Animals *animals, Animal *animal);

// Remove an Animal from an Animals array
void remove_animal(Animals *animals, Animal *animal);

// Open the `animals` file and read all Animals from it.
Animals *open_animals(Owners *owners);

// Save animals to the `animals` file and free up animals and everything in it.
void close_animals(Animals *animals);

// Create an Animal and add it to the main Animals array
Animal *create_animal(Animals *animals, Owner *owner, char *name, char *species);

// Delete an Animal from the main Animals array
void delete_animal(Animal *animal, Animals *animals, Treatments *treatments);

#endif

#ifndef TREATMENT_H
#define TREATMENT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

typedef struct Animal Animal;
typedef struct Animals Animals;
typedef struct Owner Owner;

typedef struct Treatment {
    size_t id;
    size_t index; // Index in the main Treatments array
    Animal *animal;
    time_t date;
    bool was_rabies_vaccinated;
    char *description;
} Treatment;

// Dynamic array of Treatments
typedef struct Treatments {
    size_t count;
    size_t capacity;
    Treatment** data;
    FILE *file;
} Treatments;

// Allocate and initialize a new empty Treatments array
Treatments* new_treatments();

// Add a Treatment to an Treatments array
void add_treatment(Treatments* treatments, Treatment* treatment);

// Remove a Treatment from an Treatments array
void remove_treatment(Treatments *treatments, Treatment *treatment);

// Create a Treatment and add it to the main Treatments array and to the Animal's Treatments array
Treatment* create_treatment(Treatments *treatments, Animal *animal, time_t date, bool was_rabies_vaccinated, char* description);

// Delete a Treatment, removing it from the main Treatments array and from the Animal's Treatments array
void delete_treatment(Treatment *treatment, Treatments *treatments);

// Open the `treatments` file and read all Treatments from it.
Treatments *open_treatments(Animals *animals);

// Save treatments to the `treatments` file and free up treatments and everything in it.
void close_treatments(Treatments *treatments);

#endif

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
    size_t index;
    Animal *animal;
    time_t date;
    bool was_rabies_vaccinated;
    char *description;
} Treatment;

typedef struct Treatments {
    size_t count;
    size_t capacity;
    Treatment** data;
    FILE *file;
} Treatments;

Treatments* new_treatments();
void add_treatment(Treatments* treatments, Treatment* treatment);
void remove_treatment(Treatments *treatments, Treatment *treatment);

// called with only the main treatments list loaded from a file
Treatment* create_treatment(Treatments *treatments, Animal *animal, time_t date, bool was_rabies_vaccinated, char* description);
void delete_treatment(Treatment *treatment, Treatments *treatments);

Treatments *open_treatments(Animals *animals);
void close_treatments(Treatments *treatments);

#endif

#ifndef TREATMENT_H
#define TREATMENT_H

#include "animal.h"
#include "owner.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    size_t id;
    Animal *animal;
    time_t date;
    bool was_rabies_vaccinated;
    char *description;
} Treatment;

typedef struct {
    size_t length;
    size_t capacity;
    Treatment *data;
    FILE *file;
} Treatments;

Treatments *open_treatments(Animals *animals);
void close_treatments(Treatments *treatments);

Treatment *create_treatment(Treatments *treatments, Owner *owner, char *name, char *species);
void remove_treatment(Treatments *treatments, Treatment *treatment);

#endif

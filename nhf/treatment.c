#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "animal.h"
#include "utils.h"
#include "treatment.h"

static void add_treatment(Treatments *treatments, Treatment treatment) {
    treatments->length++;
    if (treatments->length > treatments->capacity) {
        if (treatments->capacity < 10)
            treatments->capacity = 10;
        else 
            treatments->capacity *= 2;
        treatments->data = (Treatment*)realloc(treatments->data, treatments->capacity * sizeof(Treatment));
    }
    treatments->data[treatments->length - 1] = treatment;
}

Treatments *open_treatments(Animals *animals) {
    FILE *f = fopen("treatments", "r");

    Treatments *treatments = malloc(sizeof(Treatments));
    treatments->file = f;
    treatments->length = 0;
    treatments->capacity = 0;
    treatments->data = NULL;

    if (f == NULL) return treatments;

    while (1) {
        Treatment treatment;

        size_t animal_id;

        if (fscanf(f, "%zd ", &treatment.id) < 1)
            break;
        fscanf(f, "%zd ", &animal_id);
        fscanf(f, "%ld ", &treatment.date);

        int was_rabies_vaccinated;
        fscanf(f, "%d ", &was_rabies_vaccinated);
        treatment.was_rabies_vaccinated = was_rabies_vaccinated;

        treatment.description = read_line(f);

        // https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
        size_t l = 0;
        size_t r = animals->length - 1;
        while (l <= r) {
            size_t m = (l + r) / 2;
            if (animals->data[m]->id < animal_id)
                l = m + 1;
            else if (animals->data[m]->id > animal_id)
                r = m - 1;
            else {
                treatment.animal = animals->data[m];
                break;
            }
        }
        
        if (treatment.animal == NULL) {
            printf("Error: animal with id %zd not found!\n", animal_id);
            exit(1);
        }

        add_treatment(treatments, treatment);
    }

    return treatments;
}
void close_treatments(Treatments *treatments) {
    for (int i = 0; i < treatments->length; i++) {
        free(treatments->data[i].description);
    }
    free(treatments->data);
    free(treatments);
}

Treatment *create_treatment(Treatments *treatments, Animal *animal, char *name, char *species);
void remove_treatment(Treatments *treatments, Treatment *treatment);

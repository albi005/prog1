#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debugmalloc.h"
#include "animal.h"
#include "utils.h"
#include "treatment.h"

Treatments* new_treatments() {
    Treatments *treatments = malloc(sizeof(Treatments));
    treatments->file = NULL;
    treatments->count = 0;
    treatments->capacity = 0;
    treatments->data = NULL;
    return treatments;
}

void add_treatment(Treatments* treatments, Treatment* treatment) {
    treatments->count++;
    if (treatments->count > treatments->capacity) {
        if (treatments->capacity < 10)
            treatments->capacity = 10;
        else 
            treatments->capacity *= 2;
        treatments->data = (Treatment**)realloc(treatments->data, treatments->capacity * sizeof(Treatment*));
    }
    treatments->data[treatments->count - 1] = treatment;
}

void remove_treatment(Treatments *treatments, Treatment *treatment) {
    size_t index = treatments->count;
    if (treatments->file != NULL) index = treatment->index;
    else {
        for (size_t i = 0; i < treatments->count; i++) {
            if (treatments->data[i] == treatment)
            {
                index = i;
                break;
            }
        }
    }

    treatments->count--;
    for (size_t i = index; i < treatments->count; i++) {
        treatments->data[i] = treatments->data[i + 1];

        if (treatments->file != NULL)
            treatments->data[i]->index = i;
    }
}

Treatment* create_treatment(Treatments *treatments, Animal *animal, time_t date, bool was_rabies_vaccinated, char* description) {
    Treatment *treatment = malloc(sizeof(Treatment));

    if (treatments->count == 0)
        treatment->id = 1;
    else
        treatment->id = treatments->data[treatments->count - 1]->id + 1;

    treatment->animal = animal;
    treatment->date = date;
    treatment->was_rabies_vaccinated = was_rabies_vaccinated;
    treatment->description = description;
    add_treatment(treatments, treatment);
    treatment->index = treatments->count - 1;
    add_treatment(animal->treatments, treatment);
    return treatment;
}

void free_treatment(Treatment *treatment) {
    free(treatment->description);
    free(treatment);
}

void delete_treatment(Treatment *treatment, Treatments *treatments) {
    remove_treatment(treatments, treatment);
    remove_treatment(treatment->animal->treatments, treatment);

    free_treatment(treatment);
}

Treatments *open_treatments(Animals *animals) {
    FILE *f = fopen("treatments", "r");

    if (f == NULL) {
        printf("Error opening treatments file!\n");
        exit(1);
    }

    Treatments *treatments = new_treatments();
    treatments->file = f;

    while (1) {
        size_t id;
        size_t animal_id;
        time_t date;
        int was_rabies_vaccinated;

        if (fscanf(f, "%zd ", &id) < 1)
            break;
        fscanf(f, "%zd ", &animal_id);
        fscanf(f, "%ld ", &date);
        fscanf(f, "%d ", &was_rabies_vaccinated);
        char* description = read_line(f);

        // https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
        Animal* animal = NULL;
        size_t l = 0;
        size_t r = animals->count - 1;
        while (l <= r) {
            size_t m = (l + r) / 2;
            if (animals->data[m]->id < animal_id)
                l = m + 1;
            else if (animals->data[m]->id > animal_id)
                r = m - 1;
            else {
                animal = animals->data[m];
                break;
            }
        }
        
        if (animal == NULL) {
            printf("Error: animal with id %zd not found!\n", animal_id);
            exit(1);
        }

        create_treatment(treatments, animal, date, was_rabies_vaccinated, description);

    }

    return treatments;
}

void close_treatments(Treatments *treatments) {
    FILE *f = fopen("treatments", "w");
    for (int i = 0; i < treatments->count; i++) {
        Treatment *treatment = treatments->data[i];
        fprintf(f, "%zd\n%zd\n%ld\n%d\n%s\n", treatment->id, treatment->animal->id, treatment->date, treatment->was_rabies_vaccinated, treatment->description);
    }
    fclose(f);

    for (int i = 0; i < treatments->count; i++)
        free_treatment(treatments->data[i]);
    free(treatments->data);
    free(treatments);
}


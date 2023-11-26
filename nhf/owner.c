#include <stdio.h>
#include <stdlib.h>
#include "animal.h"
#include "debugmalloc.h"
#include "owner.h"
#include "utils.h"

// TODO: reorder

void add_owner(Owners *owners, Owner* owner) {
    owners->count++;
    if (owners->count > owners->capacity) {
        if (owners->capacity < 10)
            owners->capacity = 10;
        else 
            owners->capacity *= 2;
        owners->data = (Owner**)realloc(owners->data, owners->capacity * sizeof(Owner*));
    }
    owners->data[owners->count - 1] = owner;
}

void remove_owner(Owners *owners, Owner *owner) {
    size_t index = owners->count;
    if (owners->file != NULL) index = owner->index;
    else {
        for (size_t i = 0; i < owners->count; i++) {
            if (owners->data[i] == owner)
            {
                index = i;
                break;
            }
        }
    }

    if (index == owners->count) {
        printf("Error: owner not found!\n");
        exit(1);
    }

    owners->count--;
    for (size_t i = index; i < owners->count; i++) {
        owners->data[i] = owners->data[i + 1];

        if (owners->file != NULL)
            owners->data[i]->index = i;
    }
}

// must be called using only the main owners list loaded from a file
Owner *create_owner(Owners *owners, char *name, char *address, char *contact) {
    Owner* owner = malloc(sizeof(Owner));

    if (owners->count == 0)
        owner->id = 1;
    else
        owner->id = owners->data[owners->count - 1]->id + 1;

    owner->name = name;
    owner->address = address;
    owner->contact = contact;
    owner->animals = new_animals();
    add_owner(owners, owner);
    owner->index = owners->count - 1;
    return owner;
}

void free_owner(Owner *owner) {
    free(owner->animals->data);
    free(owner->animals);
    free(owner->name);
    free(owner->address);
    free(owner->contact);
    free(owner);
}

void delete_owner(Owner *owner, Owners *owners, Animals *animals, Treatments *treatments) {
    remove_owner(owners, owner);
    for (int i = owner->animals->count - 1; i >= 0; i--) {
        Animal *animal = owner->animals->data[i];
        delete_animal(animal, animals, treatments);
    }

    free_owner(owner);
}

Owners *open_owners() {
    FILE *f = fopen("owners", "r");

    if (f == NULL) {
        printf("Error opening owners file!\n");
        exit(1);
    }

    Owners *owners = malloc(sizeof(Owners));
    owners->file = f;
    owners->count = 0;
    owners->capacity = 0;
    owners->data = NULL;

    while (1) {
        size_t id;
        if (fscanf(f, "%zd ", &id) < 1)
            break;
        char* name = read_line(f);
        char* address = read_line(f);
        char* contact = read_line(f);
        Owner* owner = create_owner(owners, name, address, contact);
        owner->id = id;
    }

    return owners;
}

void close_owners(Owners *owners) {
    FILE *f = fopen("owners", "w");
    for (int i = 0; i < owners->count; i++) {
        Owner *owner = owners->data[i];
        fprintf(f, "%zd\n%s\n%s\n%s\n", owner->id, owner->name, owner->address, owner->contact);
    }
    fclose(f);

    for (int i = 0; i < owners->count; i++) {
        free(owners->data[i]->animals->data);
        free(owners->data[i]->animals);
        free(owners->data[i]->name);
        free(owners->data[i]->address);
        free(owners->data[i]->contact);
        free(owners->data[i]);
    }
    free(owners->data);
    free(owners);
}


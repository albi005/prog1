#ifndef OWNER_H
#define OWNER_H

#include <stddef.h>
#include <stdio.h>

typedef struct Animals Animals;
typedef struct Treatments Treatments;


// allocated by create_owner and open_owners
typedef struct Owner {
    size_t id;
    size_t index; // Index in the main Owners array
    char *name;
    char *address;
    char *contact;
    Animals* animals;
} Owner;
#define OWNER_PROPERTY_COUNT 3

// Dynamic array of Owners
typedef struct Owners {
    size_t count;
    size_t capacity;
    Owner* *data;
    FILE *file;
} Owners;

// Create an Owner and add it to the main Owners array. Returns the created Owner.
Owner *create_owner(Owners *owners, char *name, char *address, char *contact);

// Delete an owner and its animals
void delete_owner(Owner *owner, Owners *owners, Animals *animals, Treatments *treatments);

// Open the `owners` file and read all Owners from it.
Owners *open_owners();

// Save owners to the `owners` file and free up owners and everything in it.
void close_owners(Owners *owners);

#endif

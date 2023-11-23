#ifndef OWNER_H
#define OWNER_H

#include <stddef.h>
#include <stdio.h>

typedef struct Animals Animals;
typedef struct Treatments Treatments;

// allocated by create_owner and open_owners
typedef struct Owner {
    size_t id;
    size_t index;
    char *name;
    char *address;
    char *contact;
    Animals* animals;
} Owner;
#define OWNER_PROPERTY_COUNT 3

typedef struct Owners {
    size_t count;
    size_t capacity;
    Owner* *data;
    FILE *file;
} Owners;

Owners *open_owners();
void close_owners(Owners *owners);

Owner *create_owner(Owners *owners, char *name, char *address, char *contact);
void delete_owner(Owner *owner, Owners *owners, Animals *animals, Treatments *treatments);

#endif

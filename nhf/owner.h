#ifndef OWNER_H
#define OWNER_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t id;
    char *name;
    char *address;
    char *contact;
} Owner;

typedef struct {
    size_t length;
    size_t capacity;
    Owner *data;
    FILE *file;
} Owners;

Owners *open_owners();
void close_owners(Owners *owners);

Owner *create_owner(Owners *owners, char *name, char *address, char *contact);
void remove_owner(Owners *owners, Owner *owner);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "owner.h"
#include "utils.h"

static void add_owner(Owners *owners, Owner owner) {
    owners->length++;
    if (owners->length > owners->capacity) {
        if (owners->capacity < 10)
            owners->capacity = 10;
        else 
            owners->capacity *= 2;
        owners->data = (Owner*)realloc(owners->data, owners->capacity * sizeof(Owner));
    }
    owners->data[owners->length - 1] = owner;
}

Owners *open_owners() {
    FILE *f = fopen("owners", "r");

    if (f == NULL) {
        printf("Error opening owners file!\n");
        exit(1);
    }

    Owners *owners = malloc(sizeof(Owners));
    owners->file = f;
    owners->length = 0;
    owners->capacity = 0;
    owners->data = NULL;

    while (1) {
        Owner owner;
        if (fscanf(f, "%zd ", &owner.id) < 1)
            break;
        owner.name = read_line(f);
        owner.address = read_line(f);
        owner.contact = read_line(f);

        add_owner(owners, owner);
    }

    return owners;
}
void close_owners(Owners *owners) {
    for (int i = 0; i < owners->length; i++) {
        free(owners->data[i].name);
        free(owners->data[i].address);
        free(owners->data[i].contact);
    }
    free(owners->data);
    free(owners);
}

Owner *create_owner(Owners *owners, char *name, char *address, char *contact);
void remove_owner(Owners *owners, Owner *owner);

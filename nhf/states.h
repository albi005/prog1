#ifndef STATES_H
#define STATES_H

#include "animal.h"
#include "owner.h"
#include "treatment.h"
#include "utils.h"
#include <stddef.h>

typedef enum {
    TreatmentDetailsState_Selecting,
    TreatmentDetailsState_Editing
} TreatmentDetailsState;

typedef struct {
    TreatmentDetailsState state;
    Treatment* treatment; // set when drawing
    int selected_index;
    char* old_value;
} TreatmentDetails;

typedef enum {
    AnimalDetailsState_Selecting,
    AnimalDetailsState_Editing,
} AnimalDetailsState;

typedef struct {
    AnimalDetailsState state;
    Animal* animal; // set when drawing
    size_t selected_index;
    char* old_value;
    TreatmentDetails treatment_details;
} AnimalDetails;

typedef enum {
    OwnerDetailsState_Selecting,
    OwnerDetailsState_Editing,
    OwnerDetailsState_Details
} OwnerDetailsState;

typedef struct {
    OwnerDetailsState state;
    Owner* owner; // set when drawing
    size_t selected_index; // set when drawing from owner, when owners list is not focused
    char* old_value;
    AnimalDetails animal_details;
} OwnerDetails;

typedef enum {
    VaxTabState_Selecting,
    VaxTabState_Details
} VaxTabState;

typedef struct {
    VaxTabState state;
    size_t selected_index;
    OwnerDetails owner_details;
} VaxTab;

typedef enum {
    OwnersTabState_Selecting,
    OwnersTabState_Details,
    OwnersTabState_Searching
} OwnersTabState;

typedef struct {
    OwnersTabState state;
    size_t selected_index;
    char* search_term;
    char* previous_search_term;
    size_t visible_count; // set when drawing
    OwnerDetails owner_details;
} OwnersTab;

typedef enum {
    AnimalsTabState_Selecting,
    AnimalsTabState_Details,
    AnimalsTabState_Searching
} AnimalsTabState;

typedef struct {
    AnimalsTabState state;
    size_t selected_index;
    char* search_term;
    char* previous_search_term;
    size_t visible_count; // set when drawing
    AnimalDetails animal_details;
} AnimalsTab;

typedef enum {
    TabsState_Vax,
    TabsState_Owners,
    TabsState_Animals
} TabsState;

typedef struct {
    TabsState state;
    VaxTab vax_tab;
    OwnersTab owners_tab;
    AnimalsTab animals_tab;
} Tabs;

typedef enum {
    AppState_Tabs,
    AppState_Exit
} AppState;

typedef struct {
    AppState state;
    Tabs tabs;
    Vec2i screen_size;
    Owners* owners;
    Animals* animals;
    Treatments* treatments;
} App;

#endif // STATES_H

#ifndef STATES_H
#define STATES_H

#include "animal.h"
#include "owner.h"
#include "treatment.h"
#include "utils.h"

typedef enum {
    TreatmentDetailsState_Selecting,
    TreatmentDetailsState_Editing
} TreatmentDetailsState;

typedef struct {
    TreatmentDetailsState state;
    Treatment* treatment;
    int selected_index;
    char* old_value;
} TreatmentDetails;

typedef enum {
    AnimalDetailsState_Selecting,
    AnimalDetailsState_Editing,
} AnimalDetailsState;

typedef struct {
    AnimalDetailsState state;
    Animal* animal;
    int selected_index;
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
    Owner* owner;
    int selected_index;
    char* old_value;
    AnimalDetails animal_details;
} OwnerDetails;

typedef enum {
    VaxTabState_Selecting,
    VaxTabState_Details
} VaxTabState;

typedef struct {
    VaxTabState state;
    int selected_index;
    OwnerDetails owner_details;
} VaxTab;

typedef enum {
    OwnersTabState_Selecting,
    OwnersTabState_Details
} OwnersTabState;

typedef struct {
    OwnersTabState state;
    int selected_index;
    OwnerDetails owner_details;
} OwnersTab;

typedef enum {
    AnimalsTabState_Selecting,
    AnimalsTabState_Details
} AnimalsTabState;

typedef struct {
    AnimalsTabState state;
    int selected_index;
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

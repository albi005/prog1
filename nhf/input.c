#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "econio.h"
#include "input.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

App init() {
    App app;
    app.state = AppState_Tabs;
    app.tabs.state = TabsState_Vax;
    app.tabs.vax_tab.state = VaxTabState_Selecting;
    app.tabs.vax_tab.selected_index = 0;
    app.tabs.owners_tab.state = OwnersTabState_Selecting;
    app.tabs.owners_tab.selected_index = 0;
    app.tabs.owners_tab.search_term = copy_string("");
    app.tabs.owners_tab.previous_search_term = NULL;
    app.tabs.animals_tab.state = AnimalsTabState_Selecting;
    app.tabs.animals_tab.selected_index = 0;
    app.tabs.animals_tab.search_term = copy_string("");
    app.tabs.animals_tab.previous_search_term = NULL;
    return app;
}

bool is_quit(char input) {
    return input == KEY_ESCAPE || input == 'q';
}

bool handle_tab(char input, Tabs* tabs) {
    if (input == KEY_TAB) {
        tabs->state = (tabs->state + 1) % 3;
        return true;
    }
    return false;
}

bool handle_list(char input, int* selected_index, int count) {
    switch (input) {
        case KEY_DOWN:
        case 'j':
            *selected_index = (*selected_index + 1) % count;
            return true;
        case KEY_UP:
        case 'k':
            *selected_index = (*selected_index - 1 + count) % count;
            return true;
    }
    return false;
}

// true when finished editing
bool handle_edit(char input, char** curr, char** old) {
    if (*old == NULL)
        *old = copy_string(*curr);

    size_t len = *curr == NULL ? 0 : strlen(*curr);

    switch (input) {
        case KEY_ENTER:
            free(*old);
            *old = NULL;
            return true;
        case KEY_BACKSPACE:
            if (len == 0)
                return false;
            while (is_continuation_byte((*curr)[len - 1]))
                len--;
            len--;
            *curr = realloc(*curr, sizeof(char) * (len + 1));
            (*curr)[len] = '\0';
            return false;
        case KEY_ESCAPE:
            free(*curr);
            *curr = *old;
            *old = NULL;
            return true;
        default:
        {
            len++;
            *curr = realloc(*curr, sizeof(char) * (len + 1));
            (*curr)[len - 1] = input;
            (*curr)[len] = '\0';
            return false;
        }
    }
}

// returns true when finished
bool handle_animal_details(char input, AnimalDetails* animal_details, Treatments* treatments) {
    Animal* animal = animal_details->animal;
    switch (animal_details->state) {
        case AnimalDetailsState_Selecting:
            if (handle_list(input, &animal_details->selected_index, ANIMAL_PROPERTY_COUNT + 1 + animal->treatments->count))
                return false;

            if (input == KEY_ENTER) {
                // add new treatment
                if (animal_details->selected_index == ANIMAL_PROPERTY_COUNT) {
                    create_treatment(treatments, animal, time(NULL), false, new_empty_string());
                    animal_details->selected_index = ANIMAL_PROPERTY_COUNT + 1;
                }
                animal_details->state = AnimalDetailsState_Editing;
                animal_details->old_value = NULL;
                return false;
            }

            // toggle vaccination
            if (input == ' ' && animal_details->selected_index > ANIMAL_PROPERTY_COUNT) {
                size_t index = animal_details->selected_index - ANIMAL_PROPERTY_COUNT - 1;
                index = animal->treatments->count - 1 - index; // reverse order
                animal->treatments->data[index]->was_rabies_vaccinated = !animal->treatments->data[index]->was_rabies_vaccinated;
            }
            break;
        case AnimalDetailsState_Editing:
        {
            char** value;
            switch (animal_details->selected_index) {
                case 0: value = &animal->name; break;
                case 1: value = &animal->species; break;
                default:
                {
                    size_t index = animal_details->selected_index - ANIMAL_PROPERTY_COUNT - 1;
                    index = animal->treatments->count - 1 - index; // reverse order
                    value = &animal
                        ->treatments
                        ->data[index]
                        ->description;
                    break;
                }
                            
            }
            bool finished = handle_edit(input, value, &animal_details->old_value);
            if (finished)
                animal_details->state = AnimalDetailsState_Selecting;
            return false;
        }
    }
    return is_quit(input);
}

// returns true when finished
bool handle_owner_details(char input, OwnerDetails* owner_details, Animals* animals, Treatments* treatments) {
    Owner* owner = owner_details->owner;
    switch (owner_details->state) {
        case OwnerDetailsState_Selecting:
            if (handle_list(input, &owner_details->selected_index, OWNER_PROPERTY_COUNT + 1 + owner->animals->count))
                return false;
            if (input == KEY_ENTER) {
                if (owner_details->selected_index < OWNER_PROPERTY_COUNT) {
                    owner_details->state = OwnerDetailsState_Editing;
                    owner_details->old_value = NULL;
                    return false;
                }

                if (owner_details->selected_index == OWNER_PROPERTY_COUNT) {
                    create_animal(animals, owner, new_empty_string(), new_empty_string());
                    owner_details->selected_index = OWNER_PROPERTY_COUNT + 1 + owner->animals->count - 1;
                }

                owner_details->state = OwnerDetailsState_Details;
                owner_details->animal_details.state = AnimalDetailsState_Selecting;
                owner_details->animal_details.selected_index = 0;

                return false;
            }
            break;
        case OwnerDetailsState_Editing:
        {
            char** value;
            switch (owner_details->selected_index) {
                case 0: value = &owner->name; break;
                case 1: value = &owner->address; break;
                case 2: value = &owner->contact; break;
            }

            bool finished = handle_edit(input, value, &owner_details->old_value);

            if (finished)
                owner_details->state = OwnerDetailsState_Selecting;

            return false;
        }
        case OwnerDetailsState_Details:
            if (handle_animal_details(input, &owner_details->animal_details, treatments))
                owner_details->state = OwnerDetailsState_Selecting;
            return false;
            
    }

    return is_quit(input);
}

void handle_input(char input, App* app) {
    Tabs* tabs = &app->tabs;
    switch (tabs->state)
    {
        case TabsState_Vax:
        {
            VaxTab* vax_tab = &tabs->vax_tab;
            switch (vax_tab->state)
            {
                case VaxTabState_Selecting:
                    if (input == KEY_ENTER) {
                        vax_tab->state = VaxTabState_Details;
                        vax_tab->owner_details.state = OwnerDetailsState_Selecting;
                        vax_tab->owner_details.selected_index = 0;
                        return;
                    }

                    if (handle_list(input, &vax_tab->selected_index, app->owners->count))
                        return;

                    break;
                case VaxTabState_Details:
                    if (handle_owner_details(input, &vax_tab->owner_details, app->animals, app->treatments))
                        vax_tab->state = VaxTabState_Selecting;
                    return;
            }
            break;
        }
        case TabsState_Owners:
        {
            OwnersTab* owners_tab = &tabs->owners_tab;
            switch (owners_tab->state)
            {
                case OwnersTabState_Selecting:
                    if (input == KEY_ENTER) {
                        if (owners_tab->selected_index == 0) {
                            owners_tab->state = OwnersTabState_Searching;
                            return;
                        }

                        // add new owner
                        if (owners_tab->selected_index == 1) {
                            // reset search
                            free(owners_tab->search_term);
                            owners_tab->search_term = copy_string("");
                            free(owners_tab->previous_search_term);
                            owners_tab->previous_search_term = NULL;

                            Owner* new_owner = create_owner(app->owners, new_empty_string(), new_empty_string(), new_empty_string());
                            owners_tab->selected_index = new_owner->index + 2;
                        }
                        owners_tab->state = OwnersTabState_Details;
                        owners_tab->owner_details.state = OwnerDetailsState_Selecting;
                        owners_tab->owner_details.selected_index = 0;

                        return;
                    }
                    if (handle_list(input, &owners_tab->selected_index, app->tabs.owners_tab.visible_count + 2))
                        return;
                    break;
                case OwnersTabState_Details:
                    if (handle_owner_details(input, &owners_tab->owner_details, app->animals, app->treatments))
                        owners_tab->state = OwnersTabState_Selecting;
                    return;
                case OwnersTabState_Searching:
                    if (handle_edit(input, &owners_tab->search_term, &owners_tab->previous_search_term))
                        owners_tab->state = OwnersTabState_Selecting;
                    return;
            }
            break;
        }
        case TabsState_Animals:
        {
            AnimalsTab* animals_tab = &tabs->animals_tab;
            switch (animals_tab->state)
            {
                case AnimalsTabState_Selecting:
                    if (input == KEY_ENTER) {
                        if (animals_tab->selected_index == 0) {
                            animals_tab->state = AnimalsTabState_Searching;
                            return;
                        }

                        animals_tab->state = AnimalsTabState_Details;
                        animals_tab->animal_details.state = AnimalDetailsState_Selecting;
                        animals_tab->animal_details.selected_index = 0;

                        return;
                    }
                    if (handle_list(input, &animals_tab->selected_index, app->tabs.animals_tab.visible_count + 1))
                        return;
                    break;
                case AnimalsTabState_Details:
                    if (handle_animal_details(input, &animals_tab->animal_details, app->treatments))
                        animals_tab->state = AnimalsTabState_Selecting;
                    return;
                case AnimalsTabState_Searching:
                    if (handle_edit(input, &animals_tab->search_term, &animals_tab->previous_search_term))
                        animals_tab->state = AnimalsTabState_Selecting;
                    return;
                            
            }
            break;
        }
    }

    handle_tab(input, tabs);

    if (is_quit(input))
        app->state = AppState_Exit;
}


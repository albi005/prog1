#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "draw.h"
#include "econio.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void draw_tabs(TabsState tabs_state, Rect bounds) {
    const Color backdrop = SURFACE_CONTAINER_LOWEST;
    const Color surface = SURFACE_CONTAINER;

    background_color(surface);
    econio_clrscr();
    draw_rect((Rect){0,0, bounds.w, 1}, backdrop);

    char* tabs_text[] = {"Oltások", "Tulajdonosok", "Állatok"};
    int x = 0;
    for (int i = 0; i < 3; i++) {
        econio_gotoxy(x, 0);
        if (i == tabs_state) {
            text_color(ON_SURFACE);
            background_color(surface);
        } else {
            text_color(ON_SURFACE_VARIANT);
            background_color(backdrop);
        }
        printf(" %s ", tabs_text[i]);
        x += count_utf8_code_points(tabs_text[i]) + 2;
    }
}

size_t get_max_name_length(Owners *os) {
    int longest = 0;
    for (size_t i = 0; i < os->count; i++) {
        Owner *o = os->data[i];
        int len = count_utf8_code_points(o->name);
        if (len > longest) longest = len;
    }
    return longest;
}

void draw_property(int x, int y, char* key, char* value, bool is_selected, bool editing, Color surface) {
    econio_gotoxy(x, y);
    background_color(surface);

    if (key != NULL) {
        text_color(ON_SURFACE_VARIANT);
        printf("%s: ", key);
    }

    if (is_selected) {
        if (editing) {
            text_color(ON_PRIMARY);
            background_color(PRIMARY);
        }
        else {
            text_color(surface);
            background_color(ON_SURFACE);
        }
    }
    else text_color(ON_SURFACE);

    if (value == NULL || value[0] == 0)
        printf(" ");
    else
        printf("%s", value);
}

void draw_add_button(int x, int y, bool selected, Color surface) {
    if (selected) {
        text_color(ON_PRIMARY);
        background_color(PRIMARY);
    }
    else {
        text_color(ON_SURFACE_VARIANT);
        background_color(surface);
    }
    econio_gotoxy(x, y);
    printf(" + ");
}

void draw_searched_property(char* value, char* start, size_t len, bool selected, Color surface) {
    text_color(selected ? surface : ON_SURFACE);
    for (int i = 0; value[i] != 0; i++) {
        char* c = value + i;
        if (c == start)
            text_color(selected ? ON_PRIMARY : PRIMARY);
        else if (c == start + len)
            text_color(selected ? surface : ON_SURFACE);

        printf("%c", *c);
    }
    text_color(selected ? surface : ON_SURFACE);
}

void draw_animal_details(AnimalDetails* animal_details, Rect bounds) {
    const Color surface = SURFACE_CONTAINER_HIGHEST;
    draw_rect(bounds, surface);
    background_color(surface);
    text_color(ON_SURFACE);

    int x = bounds.x + 4;
    int y = bounds.y + 1;

    Animal* animal = animal_details->animal;
    size_t selected_index = animal_details->selected_index;
    fit(&selected_index, ANIMAL_PROPERTY_COUNT + 1 + animal->treatments->count);
    bool editing = animal_details->state == AnimalDetailsState_Editing;

    draw_property(x, y += 1, "Név", animal->name, selected_index == 0, editing, surface);
    draw_property(x, y += 1, "Faj", animal->species, selected_index == 1, editing, surface);
    draw_property(x, y += 1, "Tulajdonos", animal->owner->name, false, editing, surface);
    draw_property(x, y += 1, "Cím", animal->owner->address, false, editing, surface);

    draw_add_button(x + 3, y += 2, selected_index == ANIMAL_PROPERTY_COUNT, surface);

    selected_index -= ANIMAL_PROPERTY_COUNT + 1;
    time_t current_time = time(NULL);
    for (int i = 0; i < animal->treatments->count; i++) {
        y++;
        Treatment *treatment = animal->treatments->data[animal->treatments->count - i - 1];

        bool selected = selected_index == i;
        if (selected)
            draw_rect((Rect){x - 1, y, bounds.w - 8, 1}, ON_SURFACE);
        else
            background_color(surface);

        econio_gotoxy(x, y);
        text_color(selected ? SURFACE_CONTAINER_HIGHEST : ON_SURFACE_VARIANT);
        if (treatment->was_rabies_vaccinated)
            printf("💉 ");
        else
            printf("   ");
        printf("%d napja  ", days_since(treatment->date, current_time));

        draw_property(x + 14, y, NULL, treatment->description, selected, editing, surface);
    }
}

void draw_owner_details(OwnerDetails* owner_details, Rect bounds) {
    const Color surface = SURFACE_CONTAINER_HIGH;
    
    draw_rect(bounds, surface);

    int x = bounds.x + 4;
    int y = bounds.y + 1;

    Owner* owner = owner_details->owner;
    size_t selected_index = owner_details->selected_index;
    fit(&selected_index, OWNER_PROPERTY_COUNT + 1 + owner->animals->count);
    bool editing = owner_details->state == OwnerDetailsState_Editing;

    draw_property(x, y += 1, "Név", owner->name, selected_index == 0, editing, surface);
    draw_property(x, y += 1, "Cím", owner->address, selected_index == 1, editing, surface);
    draw_property(x, y += 1, "Elérhetőség", owner->contact, selected_index == 2, editing, surface);

    draw_add_button(x + 3, y += 2, selected_index == OWNER_PROPERTY_COUNT, surface);

    selected_index -= OWNER_PROPERTY_COUNT + 1;
    for (int i = 0; i < owner->animals->count; i++) {
        y++;
        Animal *animal = owner->animals->data[i];

        bool selected = selected_index == i;
        if (selected) {
            draw_rect((Rect){x - 1, y, bounds.w - 8, 1}, ON_SURFACE);
            owner_details->animal_details.animal = animal;
        }
        else
            background_color(surface);

        econio_gotoxy(x, y);
        text_color(selected ? surface : ON_SURFACE);
        printf("%s  ", animal->name);

        text_color(selected ? SURFACE_CONTAINER_HIGHEST : ON_SURFACE_VARIANT);
        printf("%s", animal->species);
    }

    if (owner_details->state == OwnerDetailsState_Details)
        draw_animal_details(&owner_details->animal_details, add_margin(bounds, 4, 2));
}

void draw_vaccinations(Owners *owners, Animals *animals, Treatments *treatments, VaxTab* vax_tab) {
    if (owners->count == 0) return;

    // animal id -> last vaccination
    time_t *last_vaccinations = malloc(animals->count * sizeof(time_t));
    for (int i = 0; i < animals->count; i++) last_vaccinations[i] = 0;
    for (int i = 0; i < treatments->count; i++) {
        Treatment* t = treatments->data[i];
        if (!t->was_rabies_vaccinated) continue;

        Animal *animal = t->animal;
        size_t animal_index = animal->index;
        if (t->date > last_vaccinations[animal_index])
            last_vaccinations[animal_index] = t->date;
    }

    // owner id -> oldest last vaccination (priority)
    time_t *oldest_vaccinations = (time_t*)malloc(owners->count * sizeof(time_t));
    time_t current_time = time(NULL);
    time_t max_time = current_time + 1; // if the redraw was triggered by a new treatment, its date might equal the current time
    for (int i = 0; i < owners->count; i++) oldest_vaccinations[i] = max_time;
    for (int animal_index = 0; animal_index < animals->count; animal_index++) {
        Animal *animal = animals->data[animal_index];
        Owner *owner = animal->owner;
        size_t owner_index = owner->index;
        time_t oldest_vaccination = oldest_vaccinations[owner_index];
        time_t last_vaccination = last_vaccinations[animal_index];
        if (last_vaccination < oldest_vaccination)
            oldest_vaccinations[owner_index] = last_vaccination;
    }

    // bubble sort owners based on oldest vaccination.
    // first owner should have the lowest value.
    size_t *vax_idx = (size_t*)malloc(owners->count * sizeof(size_t));
    for (int i = 0; i < owners->count; i++) vax_idx[i] = i;
    for (int i = 0; i < owners->count - 1; i++) {
        for (int j = 0; j < owners->count - i - 1; j++) {
            time_t a = oldest_vaccinations[vax_idx[j]];
            time_t b = oldest_vaccinations[vax_idx[j + 1]];
            if (a > b) {
                size_t tmp = vax_idx[j + 1];
                vax_idx[j + 1] = vax_idx[j];
                vax_idx[j] = tmp;
            }
        }
    }

    fit(&vax_tab->selected_index, owners->count);

    const Color surface = SURFACE_CONTAINER;
    size_t max_name_length = get_max_name_length(owners);
    bool is_selecting = vax_tab->state == VaxTabState_Selecting;

    for (int i = 0; i < owners->count; i++) {
        size_t idx = vax_idx[i];
        Owner *o = owners->data[idx];
        time_t oldest = oldest_vaccinations[idx];
        size_t days = days_since(oldest, current_time);

        bool selected;
        if (is_selecting) {
            selected = vax_tab->selected_index == i;
            if (selected)
                vax_tab->owner_details.owner = o;
        }
        else {
            selected = vax_tab->owner_details.owner == o;
            if (selected)
                vax_tab->selected_index = i;
        }

        if (selected) {
            draw_rect((Rect){0, i + 2, 120, 1}, ON_SURFACE);
        }
        else
            background_color(surface);

        econio_gotoxy(2, i + 2);
        if (days > 365)
            text_color(selected ? ON_ERROR : ERROR);
        else if (oldest == max_time)
            text_color(selected ? surface : ON_SURFACE_VARIANT);
        else
            text_color(selected ? ON_PRIMARY : PRIMARY);
        if (oldest == 0)
            printf("soha");
        else if (oldest == max_time)
            printf("-");
        else
            printf("%zu napja", days);

        int x = 16;
        int y = i + 2;
        econio_gotoxy(x, y);
        text_color(selected ? surface : ON_SURFACE);
        printf("%s", o->name);
        x += max_name_length + 4;

        econio_gotoxy(x, y);
        printf("%s", o->address);
        x += 44;
    
        econio_gotoxy(x, y);
        printf("%s", o->contact);
    }

    free(last_vaccinations);
    free(oldest_vaccinations);
    free(vax_idx);
}

void draw_owners(Owners *os, OwnersTab* owners_tab, Rect bounds) {
    const Color surface = SURFACE_CONTAINER;

    bool is_selecting = owners_tab->state == OwnersTabState_Selecting;
    if (is_selecting)
        fit(&owners_tab->selected_index, 2 + owners_tab->visible_count);

    size_t selected_index = owners_tab->selected_index;
    draw_property(2, 2, "Keresés", owners_tab->search_term, selected_index == 0, owners_tab->state == OwnersTabState_Searching, surface);
    draw_add_button(2, 4, selected_index == 1, surface);
    selected_index -= 2;

    owners_tab->visible_count = 0;

    size_t search_term_len = owners_tab->search_term == NULL ? 0 : strlen(owners_tab->search_term);
    int max_name_length = get_max_name_length(os);
    for (int i = 0; i < os->count; i++) {
        Owner *owner = os->data[i];

        char* search_term_start = NULL;
        if (owners_tab->search_term[0] != 0) {
            search_term_start = strstr(owner->name, owners_tab->search_term);
            if (search_term_start == NULL) continue;
        }

        owners_tab->visible_count++;

        int x = 2;
        int y = owners_tab->visible_count + 4;

        bool selected = selected_index == owners_tab->visible_count - 1;
        if (selected) {
            draw_rect((Rect){0, y, 120, 1}, ON_SURFACE);
            owners_tab->owner_details.owner = owner;
        }
        else
            background_color(SURFACE_CONTAINER);

        econio_gotoxy(x, y);
        draw_searched_property(owner->name, search_term_start, search_term_len, selected, surface);
        x += max_name_length + 4;

        econio_gotoxy(x, y);
        printf("%s", owner->address);
        x += 44;
    
        econio_gotoxy(x, y);
        printf("%s", owner->contact);
    }

    if (owners_tab->state == OwnersTabState_Details)
        draw_owner_details(&owners_tab->owner_details, add_margin(bounds, 4, 2));
}

void draw_animals(Animals *as, Owners *os, AnimalsTab* animals_tab, Rect bounds) {
    const Color surface = SURFACE_CONTAINER;

    if (animals_tab->state == AnimalsTabState_Selecting)
        fit(&animals_tab->selected_index, 1 + animals_tab->visible_count);

    size_t selected_index = animals_tab->selected_index;
    draw_property(2, 2, "Keresés", animals_tab->search_term, selected_index == 0, animals_tab->state == AnimalsTabState_Searching, surface);
    selected_index--;

    animals_tab->visible_count = 0;

    size_t search_term_len = animals_tab->search_term == NULL ? 0 : strlen(animals_tab->search_term);
    size_t max_name_length = get_max_name_length(os);
    for (int i = 0; i < as->count; i++) {
        Animal *animal = as->data[i];

        char* search_term_start = NULL;
        if (animals_tab->search_term[0] != 0) {
            search_term_start = strstr(animal->name, animals_tab->search_term);
            if (search_term_start == NULL) continue;
        }

        animals_tab->visible_count++;

        int x = 2;
        int y = animals_tab->visible_count + 3;

        bool selected = selected_index == animals_tab->visible_count - 1;
        if (selected) { 
            draw_rect((Rect){0, y, 120, 1}, ON_SURFACE);
            animals_tab->animal_details.animal = animal;
        }
        else
            background_color(surface);

        econio_gotoxy(x, y);
        text_color(selected ? surface : ON_SURFACE);
        draw_searched_property(animal->name, search_term_start, search_term_len, selected, surface);
        x += 12;

        econio_gotoxy(x, y);
        printf("%s", animal->species);
        x += 12;
    
        econio_gotoxy(x, y);
        printf("%s", animal->owner->name);
        x += max_name_length + 4;

        econio_gotoxy(x, y);
        printf("%s", animal->owner->address);
    }

    if (animals_tab->state == AnimalsTabState_Details)
        draw_animal_details(&animals_tab->animal_details, add_margin(bounds, 4, 2));
}

void draw(App* app) {
    Rect screen_bounds = {0, 0, app->screen_size.x, app->screen_size.y};
    draw_tabs(app->tabs.state, screen_bounds);

    Rect tab_bounds = {0, 1, screen_bounds.w, screen_bounds.h - 1};

    switch (app->tabs.state) {
        case TabsState_Vax:
        {
            VaxTab* vax_tab = &app->tabs.vax_tab;

            draw_vaccinations(app->owners, app->animals, app->treatments, vax_tab);

            if (vax_tab->state == VaxTabState_Details) {
                draw_owner_details(
                    &vax_tab->owner_details,
                    add_margin(tab_bounds, 4, 2)
                );
            }
            break;
        }
        case TabsState_Owners:
            draw_owners(app->owners, &app->tabs.owners_tab, tab_bounds);
            break;
        case TabsState_Animals:
            draw_animals(app->animals, app->owners, &app->tabs.animals_tab, tab_bounds);
            break;
    }

    econio_gotoxy(999, 999);
}

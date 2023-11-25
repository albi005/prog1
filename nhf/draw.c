#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "draw.h"
#include "econio.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"
#include "utils.h"
#include <stdlib.h>

void draw_background() {
    background_color(SURFACE_CONTAINER_LOWEST);
    econio_clrscr();
}

void draw_tabs(TabsState tabs_state) {
    char* tabs_text[] = {"Oltások", "Tulajdonosok", "Állatok"};
    int x = 0;
    for (int i = 0; i < 3; i++) {
        econio_gotoxy(x, 0);
        if (i == tabs_state) {
            text_color(ON_SURFACE);
            background_color(SURFACE_CONTAINER);
        } else {
            text_color(ON_SURFACE_VARIANT);
            background_color(SURFACE_CONTAINER_LOWEST);
        }
        printf(" %s ", tabs_text[i]);
        x += count_utf8_code_points(tabs_text[i]) + 2;
    }
}

int get_max_name_length(Owners *os) {
    int longest = 0;
    for (int i = 0; i < os->count; i++) {
        Owner *o = os->data[i];
        int len = count_utf8_code_points(o->name);
        if (len > longest) longest = len;
    }
    return longest;
}

// returns the selected owner
Owner* draw_vaccinations(Owners *os, Animals *as, Treatments *ts, int selected_index) {
    // animal id -> last vaccination
    time_t *last_vaccinations = malloc(as->count * sizeof(time_t));
    for (int i = 0; i < as->count; i++) last_vaccinations[i] = 0;
    for (int i = 0; i < ts->count; i++) {
        Treatment* t = ts->data[i];
        if (!t->was_rabies_vaccinated) continue;

        Animal *animal = t->animal;
        size_t animal_index = animal->index;
        if (t->date > last_vaccinations[animal_index])
            last_vaccinations[animal_index] = t->date;
    }

    // owner id -> oldest last vaccination (priority)
    time_t *oldest_vaccinations = (time_t*)malloc(os->count * sizeof(time_t));
    time_t current_time = time(NULL);
    time_t max_time = current_time + 1; // if the redraw was triggered by a new treatment, its date might equal the current time
    for (int i = 0; i < os->count; i++) oldest_vaccinations[i] = max_time;
    for (int animal_index = 0; animal_index < as->count; animal_index++) {
        Animal *animal = as->data[animal_index];
        Owner *owner = animal->owner;
        size_t owner_index = owner->index;
        time_t oldest_vaccination = oldest_vaccinations[owner_index];
        time_t last_vaccination = last_vaccinations[animal_index];
        if (last_vaccination < oldest_vaccination)
            oldest_vaccinations[owner_index] = last_vaccination;
    }

    // bubble sort owners based on oldest vaccination.
    // first owner should have the lowest value.
    size_t *vax_idx = (size_t*)malloc(os->count * sizeof(size_t));
    for (int i = 0; i < os->count; i++) vax_idx[i] = i;
    for (int i = 0; i < os->count - 1; i++) {
        for (int j = 0; j < os->count - i - 1; j++) {
            time_t a = oldest_vaccinations[vax_idx[j]];
            time_t b = oldest_vaccinations[vax_idx[j + 1]];
            if (a > b) {
                size_t tmp = vax_idx[j + 1];
                vax_idx[j + 1] = vax_idx[j];
                vax_idx[j] = tmp;
            }
        }
    }

    for (int i = 0; i < os->count; i++) {
        size_t idx = vax_idx[i];
        Owner *o = os->data[idx];
        time_t oldest = oldest_vaccinations[idx];
        size_t days = days_since(oldest, current_time);
        bool is_selected = selected_index == i;

        if (is_selected) {
            draw_rect((Rect){0, i + 2, 120, 1}, SURFACE_VARIANT);
        }
        else
            background_color(SURFACE_CONTAINER);

        econio_gotoxy(2, i + 2);
        if (days > 365)
            text_color(ON_ERROR_CONTAINER);
        else if (oldest == max_time)
            text_color(ON_SURFACE_VARIANT);
        else
            text_color(ON_PRIMARY_CONTAINER);
        if (oldest == 0)
            printf("soha");
        else if (oldest == max_time)
            printf("-");
        else
            printf("%zu napja", days);

        econio_gotoxy(14, i + 2);
        text_color(ON_SURFACE);
        printf("%s", o->name);

        econio_gotoxy(36, i + 2);
        printf("%s", o->address);
    
        econio_gotoxy(80, i + 2);
        printf("%s", o->contact);
    }

    Owner *selected_owner = os->data[vax_idx[selected_index]];

    free(last_vaccinations);
    free(oldest_vaccinations);
    free(vax_idx);

    return selected_owner;
}

void draw_owners(Owners *os) {
    int max_name_length = get_max_name_length(os);
    for (int i = 0; i < os->count; i++) {
        Owner *o = os->data[i];

        econio_gotoxy(2, i + 2);
        text_color(ON_SURFACE);
        printf("%s", o->name);

        econio_gotoxy(2 + max_name_length + 2, i + 2);
        printf("%s", o->address);
    
        econio_gotoxy(2 + max_name_length + 2 + 30, i + 2);
        printf("%s", o->contact);
    }
}

void draw_animals(Animals *as) {
    for (int i = 0; i < as->count; i++) {
        Animal *a = as->data[i];

        econio_gotoxy(2, i + 2);
        text_color(ON_SURFACE);
        printf("%s", a->name);

        econio_gotoxy(20, i + 2);
        printf("%s", a->species);
    
        econio_gotoxy(30, i + 2);
        printf("%s", a->owner->name);
    }
}

// set background before
void draw_property(int x, int y, char* key, char* value, bool is_selected, bool editing, unsigned int surface) {
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
            text_color(ON_SURFACE);
            background_color(SURFACE_VARIANT);
        }
    }
    else text_color(ON_SURFACE);

    if (value == NULL || value[0] == 0)
        printf(" ");
    else
        printf("%s", value);
}

void draw_animal_details(AnimalDetails* animal_details, Rect bounds) {
    draw_rect(bounds, SURFACE_CONTAINER_HIGHEST);
    background_color(SURFACE_CONTAINER_HIGHEST);
    text_color(ON_SURFACE);

    int x = bounds.x + 4;
    int y = bounds.y + 1;

    Animal* animal = animal_details->animal;
    int selected_index = animal_details->selected_index;
    bool editing = animal_details->state == AnimalDetailsState_Editing;

    draw_property(x, y += 1, "Név", animal->name, selected_index == 0, editing, SURFACE_CONTAINER_HIGHEST);
    draw_property(x, y += 1, "Faj", animal->species, selected_index == 1, editing, SURFACE_CONTAINER_HIGHEST);
    draw_property(x, y += 1, "Tulajdonos", animal->owner->name, false, editing, SURFACE_CONTAINER_HIGHEST);
    draw_property(x, y += 1, "Cím", animal->owner->address, false, editing, SURFACE_CONTAINER_HIGHEST);

    selected_index -= ANIMAL_PROPERTY_COUNT;
    y++;
    time_t current_time = time(NULL);
    for (int i = 0; i < animal->treatments->count; i++) {
        y++;
        Treatment *treatment = animal->treatments->data[animal->treatments->count - i - 1];

        bool selected = selected_index == i;
        if (selected)
            draw_rect((Rect){x - 1, y, bounds.w - 8, 1}, SURFACE_VARIANT);
        else
            background_color(SURFACE_CONTAINER_HIGHEST);

        econio_gotoxy(x, y);
        text_color(ON_SURFACE);
        if (treatment->was_rabies_vaccinated)
            printf("💉 ");
        else
            printf("   ");
        printf("%d napja  ", days_since(treatment->date, current_time));

        draw_property(x + 14, y, NULL, treatment->description, selected, editing, SURFACE_CONTAINER_HIGHEST);
    }
}

void draw_owner_details(OwnerDetails* owner_details, Rect bounds) {
    draw_rect(bounds, SURFACE_CONTAINER_HIGH);
    background_color(SURFACE_CONTAINER_HIGH);
    text_color(ON_SURFACE);

    int x = bounds.x + 4;
    int y = bounds.y + 1;

    Owner* owner = owner_details->owner;
    int selected_index = owner_details->selected_index;
    bool editing = owner_details->state == OwnerDetailsState_Editing;

    draw_property(x, y += 1, "Név", owner->name, selected_index == 0, editing, SURFACE_CONTAINER_HIGH);
    draw_property(x, y += 1, "Cím", owner->address, selected_index == 1, editing, SURFACE_CONTAINER_HIGH);
    draw_property(x, y += 1, "Elérhetőség", owner->contact, selected_index == 2, editing, SURFACE_CONTAINER_HIGH);

    selected_index -= OWNER_PROPERTY_COUNT;
    y++;
    for (int i = 0; i < owner->animals->count; i++) {
        y++;
        Animal *animal = owner->animals->data[i];

        bool selected = selected_index == i;
        if (selected)
            draw_rect((Rect){x - 1, y, bounds.w - 8, 1}, SURFACE_VARIANT);
        else
            background_color(SURFACE_CONTAINER_HIGH);

        econio_gotoxy(x, y);
        text_color(ON_SURFACE);
        printf("%s  ", animal->name);

        text_color(ON_SURFACE_VARIANT);
        printf("%s", animal->species);
    }

    if (owner_details->state == OwnerDetailsState_Details)
        draw_animal_details(&owner_details->animal_details, add_margin(bounds, 6, 3));
}

void draw(App* app) {
    Rect screen_bounds = {0, 0, app->screen_size.x, app->screen_size.y};
    draw_background();
    draw_tabs(app->tabs.state);

    Rect tab_bounds = {0, 1, screen_bounds.w, screen_bounds.h - 1};
    draw_rect(tab_bounds, SURFACE_CONTAINER);

    switch (app->tabs.state) {
        case TabsState_Vax:
        {
            VaxTab vax_tab = app->tabs.vax_tab;

            // selected owner is set here to save recalculation
            app->tabs.vax_tab.owner_details.owner = draw_vaccinations(app->owners, app->animals, app->treatments, vax_tab.selected_index);

            if (vax_tab.state == VaxTabState_Details) {
                draw_owner_details(
                    &vax_tab.owner_details,
                    add_margin(tab_bounds, 6, 3)
                );
            }
            break;
        }
        case TabsState_Owners:
            draw_owners(app->owners);
            break;
        case TabsState_Animals:
            draw_animals(app->animals);
            break;
    }

    econio_gotoxy(999, 999);
}

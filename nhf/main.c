#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "econio.h"
#include "input.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"
#include "utils.h"

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

void draw_vaccinations(Owners *os, Animals *as, Treatments *ts, int selected_index) {
    // animal id -> last vaccination
    time_t *last_vaccinations = malloc(as->length * sizeof(time_t));
    for (int i = 0; i < as->length; i++) last_vaccinations[i] = 0;
    for (int i = 0; i < ts->length; i++) {
        Treatment t = ts->data[i];
        if (!t.was_rabies_vaccinated) continue;

        Animal *animal = t.animal;
        size_t animal_index = animal->index;
        if (t.date > last_vaccinations[animal_index])
            last_vaccinations[animal_index] = t.date;
    }

    // owner id -> oldest last vaccination (priority)
    time_t *oldest_vaccinations = (time_t*)malloc(os->count * sizeof(time_t));
    time_t current_time = time(NULL);
    time_t max_time = current_time + 1; // if the redraw was triggered by a new treatment, its date might equal the current time
    for (int i = 0; i < os->count; i++) oldest_vaccinations[i] = max_time;
    for (int animal_index = 0; animal_index < as->length; animal_index++) {
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
        size_t days = (current_time - oldest) / (60 * 60 * 24);
        bool is_selected = selected_index == i;

        if (is_selected)
            draw_rect((Rect){0, i + 2, 120, 1}, SURFACE_VARIANT);
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

    free(last_vaccinations);
    free(oldest_vaccinations);
    free(vax_idx);
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
    for (int i = 0; i < as->length; i++) {
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

void draw_owner_details(Owner *owner, Animals* as, Rect bounds) {
    draw_rect(bounds, SURFACE_CONTAINER_HIGH);
    background_color(SURFACE_CONTAINER_HIGH);
    text_color(ON_SURFACE);

    int x = bounds.x + 2;
    int y = bounds.y + 1;

    econio_gotoxy(x, y);
    printf("Név: %s", owner->name);
    econio_gotoxy(x, y += 1);
    printf("Cím: %s", owner->address);
    econio_gotoxy(x, y += 1);
    printf("Elérhetőség: %s", owner->contact);

    y++;
    for (int i = 0; i < as->length; i++) {
        Animal *a = as->data[i];
        if (a->owner == owner) {
            econio_gotoxy(x, y += 1);
            text_color(ON_SURFACE);
            printf("%s ", a->name);
            text_color(ON_SURFACE_VARIANT);
            printf("%s", a->species);
        }
    }
}

int main() {
    // init state
    Tabs tabs;
    tabs.state = TabsState_Vax;
    tabs.vax_tab.state = VaxTabState_Selecting;
    tabs.vax_tab.selected_index = 0;

    // init data
    Owners* owners = open_owners();
    Animals* animals = open_animals(owners);
    Treatments* treatments = open_treatments(animals);

    // init screen
    econio_rawmode();
    Vec2i screen_size = get_terminal_size();
    Rect screen_bounds = {0, 0, screen_size.x, screen_size.y};
    
    // main loop
    while (true) {
        // draw
        draw_background();
        draw_tabs(tabs.state);

        Rect tab_bounds = {0, 1, screen_bounds.w, screen_bounds.h - 1};
        draw_rect(tab_bounds, SURFACE_CONTAINER);

        switch (tabs.state) {
            case TabsState_Vax:
            {
                VaxTab vax_tab = tabs.vax_tab;
                draw_vaccinations(owners, animals, treatments, vax_tab.selected_index);
                switch (vax_tab.state) {
                    case VaxTabState_Selecting:
                        break;
                    case VaxTabState_Details:
                    {
                        draw_owner_details(
                            owners->data[vax_tab.selected_index],
                            animals,
                            add_margin(screen_bounds, 6, 3)
                        );
                        break;
                    }
                }
                break;
            }
            case TabsState_Owners:
                draw_owners(owners);
                break;
            case TabsState_Animals:
                draw_animals(animals);
                break;
        }

        // input
        int key = econio_getch();

        bool quit = false;
        handle_input(key, &tabs, owners, animals, treatments, &quit);

        if (quit)
            break;
    }

    econio_normalmode();
    close_owners(owners);
    close_animals(animals);
    close_treatments(treatments);

    printf("\n");
}

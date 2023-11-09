#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "econio.h"
#include "owner.h"
#include "utils.h"
#include "treatment.h"

typedef struct {
    int selected_tab;
} Tabs;

void draw_tabs(Tabs* tabs) {
    char* tabs_text[] = {"Oltások", "Tulajdonosok", "Állatok"};
    int x = 0;
    for (int i = 0; i < 3; i++) {
        econio_gotoxy(x, 0);
        if (i == tabs->selected_tab) {
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

void draw_background() {
    background_color(SURFACE_CONTAINER_LOWEST);
    econio_clrscr();
}

int get_max_name_length(Owners *os) {
    int longest = 0;
    for (int i = 0; i < os->length; i++) {
        Owner *o = os->data + i;
        int len = count_utf8_code_points(o->name);
        if (len > longest) longest = len;
    }
    return longest;
}

void draw_vaccinations(Owners *os, Animals *as, Treatments *ts) {
    // animal id -> last vaccination
    time_t *last_vaccinations = malloc(as->length * sizeof(time_t));
    for (int i = 0; i < as->length; i++) last_vaccinations[i] = 0;
    for (int i = 0; i < ts->length; i++) {
        Treatment t = ts->data[i];
        if (!t.was_rabies_vaccinated) continue;

        Animal *a = t.animal;
        size_t animal_index = a - as->data;
        if (t.date > last_vaccinations[animal_index])
            last_vaccinations[animal_index] = t.date;
    }

    // owner id -> oldest last vaccination (priority)
    time_t *oldest_vaccinations = (time_t*)malloc(os->length * sizeof(time_t));
    time_t current_time = time(NULL);
    time_t max_time = current_time + 1; // if the redraw was triggered by a new treatment, its date might equal the current time
    for (int i = 0; i < os->length; i++) oldest_vaccinations[i] = max_time;
    for (int animal_index = 0; animal_index < as->length; animal_index++) {
        Animal *animal = as->data + animal_index;
        Owner *owner = animal->owner;
        size_t owner_index = owner - os->data;
        time_t oldest_vaccination = oldest_vaccinations[owner_index];
        time_t last_vaccination = last_vaccinations[animal_index];
        if (last_vaccination < oldest_vaccination)
            oldest_vaccinations[owner_index] = last_vaccination;
    }

    // order owners based on oldest vaccination.
    // first owner should have the lowest
    size_t *vax_idx = (size_t*)malloc(os->length * sizeof(size_t));
    for (int i = 0; i < os->length; i++) vax_idx[i] = i;
    for (int i = 0; i < os->length - 1; i++) {
        for (int j = 0; j < os->length - i; i++) {
            time_t a = oldest_vaccinations[vax_idx[j]];
            time_t b = oldest_vaccinations[vax_idx[j + 1]];
            if (a > b) {
                size_t tmp = vax_idx[j + 1];
                vax_idx[j + 1] = vax_idx[j];
                vax_idx[j] = tmp;
            }
        }
    }

    for (int i = 0; i < os->length; i++) {
        size_t idx = vax_idx[i];
        Owner *o = os->data + idx;
        time_t oldest = oldest_vaccinations[idx];
        size_t days = (current_time - oldest) / (60 * 60 * 24);

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
    for (int i = 0; i < os->length; i++) {
        Owner *o = os->data + i;

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
        Animal *a = as->data + i;

        econio_gotoxy(2, i + 2);
        text_color(ON_SURFACE);
        printf("%s", a->name);

        econio_gotoxy(20, i + 2);
        printf("%s", a->species);
    
        econio_gotoxy(30, i + 2);
        printf("%s", a->owner->name);
    }
}

int main() {
    draw_background();
    
    Tabs tabs = {0};
    Owners* os = open_owners();
    Animals* as = open_animals(os);
    Treatments* ts = open_treatments(as);

    econio_rawmode();

    Vec2i size = get_terminal_size();
    draw_tabs(&tabs);

    while (true) {
        draw_rect(0, 1, size.x, size.y - 1, SURFACE_CONTAINER);

        switch (tabs.selected_tab) {
            case 0:
                draw_vaccinations(os, as, ts);
                break;
            case 1:
                draw_owners(os);
                break;
            case 2:
                draw_animals(as);
                break;
        }
        
        int key = econio_getch();

        if (key == 'q' || key == KEY_ESCAPE)
            break;

        if (key == KEY_TAB) {
            tabs.selected_tab = (tabs.selected_tab + 1) % 3;
            draw_tabs(&tabs);
        }
    }

    econio_normalmode();
    close_owners(os);
    close_animals(as);
    close_treatments(ts);

    printf("\n");
}

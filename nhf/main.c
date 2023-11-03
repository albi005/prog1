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
    time_t *last_vaccination = malloc(as->length * sizeof(time_t)); // animal id -> last vaccination
    for (int i = 0; i < as->length; i++) last_vaccination[i] = 0;
    for (int i = 0; i < ts->length; i++) {
        Treatment t = ts->data[i];
        Animal *a = t.animal;
        size_t animal_index = a - as->data;
        last_vaccination[animal_index] = t.date;
    }

    time_t *oldest_vaccination = (time_t*)malloc(os->length * sizeof(time_t)); // owner id -> oldest last vaccination (priority)
    time_t current_time = time(NULL);
    for (int i = 0; i < os->length; i++) oldest_vaccination[i] = current_time;
    for (int i = 0; i < as->length; i++) {
        Animal *a = as->data + i;
        size_t animal_index = a - as->data;
        Owner *o = a->owner;
        size_t owner_index = o - os->data;
        if (last_vaccination[animal_index] < oldest_vaccination[owner_index])
            oldest_vaccination[owner_index] = last_vaccination[animal_index];
    }

    // order owners based on oldest vaccination.
    // first owner should have the lowest
    size_t *vax_idx = (size_t*)malloc(os->length * sizeof(size_t));
    for (int i = 0; i < os->length; i++) vax_idx[i] = i;
    for (int i = 0; i < os->length - 1; i++) {
        for (int j = 0; j < os->length - i; i++) {
            time_t a = oldest_vaccination[vax_idx[j]];
            time_t b = oldest_vaccination[vax_idx[j + 1]];
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
        time_t oldest = oldest_vaccination[idx];
        size_t days = (current_time - oldest) / (60 * 60 * 24);

        econio_gotoxy(2, i + 2);
        if (days > 365)
            text_color(ON_ERROR_CONTAINER);
        else
            text_color(ON_SURFACE);
        if (oldest_vaccination == 0)
            printf("soha");
        else
            printf("%zu napja", days);

        econio_gotoxy(13, i + 2);
        text_color(ON_SURFACE);
        printf("%s", o->name);

        econio_gotoxy(36, i + 2);
        printf("%s", o->address);
    
        econio_gotoxy(70, i + 2);
        printf("%s", o->contact);
    }

    free(last_vaccination);
    free(oldest_vaccination);
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
}

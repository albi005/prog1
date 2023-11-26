#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "animal.h"
#include "console.h"
#include "debugmalloc.h"
#include "draw.h"
#include "econio.h"
#include "input.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"
#include "utils.h"

int main() {
    // init state
    App app = init();

    // load data
    app.owners = open_owners();
    app.animals = open_animals(app.owners);
    app.treatments = open_treatments(app.animals);

    // init screen
    econio_rawmode();
    app.screen_size = get_terminal_size();
    
    // main loop
    while (true) {
        draw(&app);
        
        int key = econio_getch();
        handle_input(key, &app);

        if (app.state == AppState_Exit)
            break;
    }

    // save data and clean up
    close_treatments(app.treatments);
    close_animals(app.animals);
    close_owners(app.owners);

    free(app.tabs.owners_tab.search_term);
    free(app.tabs.animals_tab.search_term);

    reset_colors();
    econio_normalmode();
    printf("\n");
}

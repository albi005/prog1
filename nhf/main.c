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
    App app;
    app.state = AppState_Tabs;
    app.tabs.state = TabsState_Vax;
    app.tabs.vax_tab.state = VaxTabState_Selecting;
    app.tabs.vax_tab.selected_index = 0;

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

    // clean up
    econio_normalmode();
    close_owners(app.owners);
    close_animals(app.animals);
    close_treatments(app.treatments);

    printf("\n");
}

#include "animal.h"
#include "econio.h"
#include "input.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"

bool is_quit(char input) {
    return input == KEY_ESCAPE || input == 'q';
}

void handle_input(char input, Tabs* tabs, Owners* owners, Animals* animals, Treatments* treatments, bool* quit) {
    switch (tabs->state) {
        case TabsState_Vax:
        {
            VaxTab vax_tab = tabs->vax_tab;
            switch (vax_tab.state) {
                case VaxTabState_Selecting:
                {
                    switch (input) {
                        case KEY_DOWN:
                        case 'j':
                            vax_tab.selected_index = (vax_tab.selected_index + 1) % owners->count;
                            return;
                        case KEY_UP:
                        case 'k':
                            vax_tab.selected_index = (vax_tab.selected_index - 1 + owners->count) % owners->count;
                            return;
                        case KEY_ENTER:
                            vax_tab.state = VaxTabState_Details;
                            vax_tab.owner_details.state = OwnerDetailsState_Selecting;
                            vax_tab.owner_details.selected_index = 0;
                            return;
                    }
                    break;
                }
                case VaxTabState_Details:
                {
                    // owner page
                    OwnerDetails owner_details = vax_tab.owner_details;
                    switch (input) {
                        case KEY_DOWN:
                        case 'j':
                            owner_details.selected_index = (owner_details.selected_index + 1) % animals->length;
                            return;
                        case KEY_UP:
                        case 'k':
                            owner_details.selected_index = (owner_details.selected_index - 1 + animals->length) % animals->length;
                            return;
                        case KEY_ENTER:
                        {
                            owner_details.state = OwnerDetailsState_Details;
                            return;
                        }
                        case KEY_ESCAPE:
                        case 'q':
                            vax_tab.state = VaxTabState_Selecting;
                            return;
                    }
                    
                    break;
                }
            }
            break;
        }
        case TabsState_Owners:
        {
            break;
        }
        case TabsState_Animals:
        {
            break;
        }
    }

    if (is_quit(input))
        *quit = true;
}


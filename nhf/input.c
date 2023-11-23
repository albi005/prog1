#include "animal.h"
#include "econio.h"
#include "input.h"
#include "owner.h"
#include "states.h"
#include "treatment.h"

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

void handle_input(char input, Tabs* tabs, Owners* owners, Animals* animals, Treatments* treatments, bool* quit) {
    switch (tabs->state) {
        case TabsState_Vax:
        {
            VaxTab* vax_tab = &tabs->vax_tab;
            switch (vax_tab->state) {
                case VaxTabState_Selecting:
                {
                    if (input == KEY_ENTER) {
                            vax_tab->state = VaxTabState_Details;
                            vax_tab->owner_details.state = OwnerDetailsState_Selecting;
                            vax_tab->owner_details.selected_index = 0;
                            return;
                    }

                    handle_list(input, &vax_tab->selected_index, owners->count)
                    || handle_tab(input, tabs);

                    break;
                }
                case VaxTabState_Details:
                {
                    // owner page
                    OwnerDetails* owner_details = &vax_tab->owner_details;

                    if (input == KEY_ENTER)
                        owner_details->state = OwnerDetailsState_Details;
                    else if (is_quit(input))
                        vax_tab->state = VaxTabState_Selecting;
                    else if (handle_list(input, &owner_details->selected_index, animals->length));
                    else
                        break;
                    
                    return;
                }
            }
            break;
        }
        case TabsState_Owners:
        {
            handle_tab(input, tabs);
            break;
        }
        case TabsState_Animals:
        {
            handle_tab(input, tabs);
            break;
        }
    }

    if (is_quit(input))
        *quit = true;
}


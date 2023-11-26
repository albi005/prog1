#ifndef INPUT_H
#define INPUT_H

#include "states.h"
#include "owner.h"
#include "animal.h"
#include "treatment.h"

// Returns an App with the initial state
App init();

// Updates the state based on a single character input/keypress
void handle_input(char input, App* app);

#endif // INPUT_H

#ifndef INPUT_H
#define INPUT_H

#include "states.h"
#include "owner.h"
#include "animal.h"
#include "treatment.h"

App init();
void handle_input(char input, App* app);

#endif // INPUT_H

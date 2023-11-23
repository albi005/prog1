#ifndef INPUT_H
#define INPUT_H

#include "states.h"
#include "owner.h"
#include "animal.h"
#include "treatment.h"

void handle_input(char input, Tabs* tabs, Owners* owners, Animals* animals, Treatments* treatments, bool* quit);

#endif // INPUT_H

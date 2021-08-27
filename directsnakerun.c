// Header files
#include "Custom Headers\allheaders.h"

// Data (struct, enum and constants)
#include "Custom Headers\dataandconstants.h"

#include "Custom Headers\globalvariables.h"

// Functions ####################################################
#include "Custom Headers\displayfuncs.h"
#include "Custom Headers\customcalc.h"
#include "Custom Headers\kbandmouse.h"
#include "Custom Headers\soundthings.h"

#include "Actual Games\getsnakemove.c"

int main()
{
    srand(time(NULL));
    startgame(FALSE);
}
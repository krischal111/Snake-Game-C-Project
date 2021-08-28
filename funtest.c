#include <stdio.h>
#include "Custom Headers\allheaders.h"
#include "Custom Headers\dataandconstants.h"
#include "Custom Headers\kbandmouse.h"
int main()
{
    char name[30];
    printf("Your text = ");
    scantext(name,30);
    // fgets(name,30,stdin);
    name[29] = 0;
    printf("Your text = %s",name);
    while(!GetAsyncKeyState(VK_SPACE) & MSB_s);
    while(!GetAsyncKeyState(VK_SPACE) & MSB_s);
}
#include"allheaders.h"

#include"dataandconstants.h"
char playgroundstr[20][20][3];
struct makeplayground playground;
struct makemenudata menudata;
#include"menutext.h"


#include"kbandmouse.h"
#include"customcalc.h"
#include"displayfuncs.h"


int interactive(char *menutext,int size,int n,int *y)
{
    struct keyboardinputs kb;
    menubegin:
    gotoxy(0,1);


    for(int i=0;i<n;i++ )
    {
        if(i == *y)
        {
            printf(" ");
        }
        printf(" %s   \n", menutext+i*size);
    }
    gotoxy(1,*y + 1);

    while(1)
    {
        Sleep(50);
        kb = gameinput(0);

        if(!kb.nothing)
        {
            if(kb.down)
                incremod(y,n);

            if(kb.up)
                decremod(y,n);

            if(kb.enter)
                return 0;

            if(kb.esc)
                return 1;

            goto menubegin;
        }
    }
}


int main()
{
    int y=0,esc = 0;

    menudata.gamerunning = 0;

startmain:
    {
        system("cls");
        if(menudata.gamerunning)
        {
            esc = interactive(mainmenu[0],20,7,&y);
        }
        else
        {
            esc = interactive(mainmenu[1],20,6,&y);
            y++;
        }
    }

    if(esc == 1 || y == 6)
    {
        system("cls");
        printf(" Exit game?");
        esc = interactive(confirmText[0],5,2,&y);
        if(esc == 1 || y != 0)
        {
            goto startmain;
        }
        else
            exit(0);

    }

    switch(y)
    {
    case 0:

        break;

    case 1:

        break;

    case 2:
        goto optionsmain;
        break;

    case 3:

        break;

    case 4:

        break;

    case 5:

        break;

    case 6:

        break;

    default:
        y=0;
    }

    goto startmain;


optionsmain:

    system("cls");
    esc = interactive(optionMenu[0],20,3,&y);
    if(esc == 1)
    {
        goto startmain;
    }

    switch(y)
    {
    case 0:
        goto soundoption;
        break;

    case 1:
        goto redefineoption;
        break;

    case 2:
        goto AIoption;
        break;
    }


soundoption:
    ;
redefineoption:
    ;
AIoption:
    ;
return 0;

}




//menudata.options.soundon = !menudata.options.soundon;

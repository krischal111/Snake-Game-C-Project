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
    int starty, startx;
    starty = 2; startx = 1;
    *y %= n; 
    struct keyboardinputs kb;

menubegin:
    ShowConsoleCursor(FALSE);    
    gotoxy(0,starty);
    for(int i=0;i<n;i++ )
    {
        printf("%*s",startx,"");        
        if(i == *y)
        {
            printf("--> ");
        }
        else
        {
            printf("    ");
        }
        printf(" %s   \n", (menutext+i*size));
    }
    ShowConsoleCursor(TRUE);
    gotoxy(startx+20,*y + starty);

    while(1)
    {
        Sleep(50);
        rerun:
        kb = menuinput();

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
            
            if(kb.numpress)
            {
                if(kb.number<n)
                {
                    y = kb.number+1;
                }
                else
                {
                    goto rerun;
                }
            }
            
            goto menubegin;
        }
    }
}


int main()
{
    srand(time(NULL));
    int y=0,esc = 0;

    menudata.gamerunning = 0;

startmain:
    {
        system("cls");
        printf(" Main menu:");
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
    case 0: //continue

        break;

    case 1: //start game

        break;

    case 2: //options
        goto optionsmain;
        break;

    case 3: //levels
        goto levelsmain;
        break;

    case 4: //highscores
        goto highscoresmain;
        break;

    case 5: //help
        goto helpmain;
        break;

    case 6: //exit

        break;

    default:
        y=0;
    }

    goto startmain;


optionsmain:

    system("cls");
    printf(" Options:");
    esc = interactive(optionMenu[0],20,2,&y);
    if(esc == 1)
    {
        y = 2;
        goto startmain;
    }

    switch(y)
    {
    case 0:
        y = menudata.options.soundon?0:1;
        goto soundoption;
        break;

    case 1:
        // goto redefineoption;
        // break;

    case 2:
        y = menudata.options.AImode?1:0;
        goto AIoption;
        break;

    }
    goto optionsmain;


soundoption:
    system("cls");
    printf(" Sound on/off:");
    esc = interactive(soundMenu[0],20,2,&y);
    if(esc == 1)
    {
        y=0;
        goto optionsmain;
    }

    switch(y)
    {
    case 0:
        menudata.options.soundon = TRUE;
        break;
    case 1:
        menudata.options.soundon = FALSE;
        break;
    }

    y=0;
    goto optionsmain;


redefineoption:
    system("cls");
    printf(" Redefine controls:");
    esc = interactive(redefineMenu[0],20,4,&y);
    if(esc == 1)
    {
        y = 1;
        goto optionsmain;
    }

    switch(y)
    {
    case 0: //current key and next key assignment
        printf("\t\tUp");
        break;

    case 1: //current key and next key assignment
        printf("\t\tDown");
        break;

    case 2: //current key and next key assignment
        printf("\t\tLeft");
        break;

    case 3: //current key and next key assignment
        printf("\t\tRight");
        break;
    };

    y=1;
    goto optionsmain;


AIoption:
    system("cls");
    printf(" Who controls the game:");
    esc = interactive(AIMenu[0],6,2,&y);
    if(esc == 1)
    {
        y = 1;
        goto optionsmain;
    }

    switch(y)
    {
    case 0:
        menudata.options.AImode = FALSE;
        break;

    case 1:
        menudata.options.AImode = TRUE;
        break;
    };

    y = 1;
    goto optionsmain;


levelsmain:
    system("cls");
    esc = interactive(levelsMenu[0],10,10,&y);
    if(esc == 1)
    {
        goto startmain;
    }

    if(y>=0 && y<10)
    {
        menudata.level = y+1;
        goto startmain;
    }
    goto startmain;



highscoresmain:
    system("cls");
    goto startmain;



helpmain:
    system("cls");
    printf("%s",helpText);

    while(1)
    {
        Sleep(50);
        if((GetAsyncKeyState(VK_ESCAPE) & 0x01)||(GetAsyncKeyState(VK_RETURN) & 0x01))
            goto startmain;

    }

    

    




return 0;

}






#include"Custom Headers\allheaders.h"           // Standard Header

#include"Custom Headers\dataandconstants.h"     // Data type creation, and constants
#include"Custom Headers\globalvariables.h"      // Global variables
#include"Custom Headers\menutext.h"             // Menu texts
#include"Custom Headers\soundthings.h"

#include"Custom Headers\kbandmouse.h"           // Important functions
#include"Custom Headers\customcalc.h"
#include"Custom Headers\displayfuncs.h"
#include"Custom Headers\filehandling.h"

#include"Actual Games\getsnakemove.c"           // Actual Game
void menu();
int interactive(char *, int, int, int *);
void intro();

void intro()
{
    ShowConsoleCursor(FALSE);
    struct userdata s;
    if(!readuserdata(userdatafilename,&s))
    {
        printf("Enter your good name = ");
        fgets(s.name,30,stdin);
        storeuserdata(userdatafilename, s);
    }
    system("cls");
    printf("\n     Welcome to the snakegame game, %s", s.name);
    if(menudata.options.soundon)
    playtuneusing(introtune);
    Sleep(2000);

    ShowConsoleCursor(TRUE);
    return;
}


int main()
{
    if(!readmenudata(menudatafilename))
    {
        system(makefoldertext);
        system("cls");
    }
    readBestscorelist(bestscorefilename);
    intro();
    menu();
}

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
        printf("%d. %s   \n",i+1, (menutext+i*size));
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
                if(kb.number<=n)
                {       // Remember, y is just a pointer, *y is the real value
                    *y = kb.number-1;
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


void menu()
{
    srand(time(NULL));
    int y=0,esc = 0;

    gameisrunning = FALSE;

startmain:
    {
        system("cls");
        printf(" Main menu:");
        if(gameisrunning)
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
            y=5+(gameisrunning?1:0);        // position of Exit game in Main menu
            goto startmain;
        }
        else
            goto the_end;

    }

    switch(y)
    {
    case 0: //continue
        startgame(gameisrunning);
        break;

    case 1: //start game
        startgame(FALSE);
        // system("cls");
        // system("getsnakemove.exe");
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
        y = 1+(gameisrunning?1:0);
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
        // This option has been removed, so absence of break; makes case 2 statements being executed

    case 2:
        y = menudata.options.AImode?1:0;
        goto AIoption;
        break;

    }
    goto optionsmain;


soundoption:
    system("cls");
    printf(" Sound on/off:");
    y = menudata.options.soundon?0:1;
    esc = interactive(soundMenu[0],20,2,&y);
    if(esc == 1)
    {
        y=0;    // position of sound option in option menu
        goto optionsmain;
    }

    switch(y)
    {
    case 0:
        menudata.options.soundon = TRUE;
        storemenudata(menudatafilename);
        break;
    case 1:
        menudata.options.soundon = FALSE;
        storemenudata(menudatafilename);
        break;
    }

    y=2;        // position of sound option in option menu
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
    y = menudata.options.AImode?1:0;
    esc = interactive(AIMenu[0],6,2,&y);
    if(esc == 1)
    {
        y = 1;      // position of AI option in option menu
        goto optionsmain;
    }

    switch(y)
    {
    case 0:
        menudata.options.AImode = FALSE;
        storemenudata(menudatafilename);
        break;

    case 1:
        menudata.options.AImode = TRUE;
        storemenudata(menudatafilename);
        break;
    };

    y = 1;          // position of AI option in option menu
    goto optionsmain;


levelsmain:
    system("cls");
    printf("Choose the level:");
    y = menudata.level;
    esc = interactive(levelsMenu[0],10,10,&y);
    if(esc == 1)
    {   
        y=2+(gameisrunning?1:0);        // position of level in startmain
        goto startmain;
    }

    if(y>=0 && y<10)
    {
        menudata.level = y+1;
        storemenudata(menudatafilename);
        y = 2+(gameisrunning?1:0);
        goto startmain;
    }
    y=2+(gameisrunning?1:0);            // position of level in startmain
    goto startmain;



highscoresmain:
    system("cls");
    readBestscorelist(bestscorefilename);
    displayBestscorelist();

    while(1)
    {
        Sleep(50);
        struct keyboardinputs kb = menuinput();
        if(kb.esc || kb.enter)
        {
            y=3+(gameisrunning?1:0);        // position of level in startmain
            goto startmain;
        }
    }

    y=3+(gameisrunning?1:0);        // position of highscore option in startmain
    goto startmain;



helpmain:
    system("cls");
    printf("%s",helpText);
    while(1)
    {
        Sleep(50);
        struct keyboardinputs kb = menuinput();
        if(kb.esc || kb.enter)
        {
            y=4+(gameisrunning?1:0);        // position of level in startmain
            goto startmain;
        }
    }


the_end:
return;
}
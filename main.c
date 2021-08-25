#include"allheaders.h"

#include"dataandconstants.h"
char playgroundstr[20][20][3];
struct makeplayground playground;
struct makemenudata menudata;
#include"menutext.h"


#include"kbandmouse.h"
#include"customcalc.h"
#include"displayfuncs.h"


void interactive(char *menutext,int size,int n,int *y){

    gotoxy(0,0);

    for(int i=0;i<n;i++ )
    {

        if(i == *y)
        {
            printf(" ");

        }
        printf(" %s   \n", menutext+i*size);
    }
    gotoxy(1,*y);

}


int main()
{
    int y=0,main_allow = 1,option_allow = 0,help_allow = 0,exit_allow = 1,option_menu_allow = 0,sound_allow = 0;
    menudata.gamerunning = 0;
    _Bool can_continue = FALSE;
    struct keyboardinputs kb;

    startmain:
    if(main_allow == 1)
    {

        system("cls");
        if(menudata.gamerunning)
        {
            interactive(mainmenu[0],20,7,&y);

        }

        else
        {
            interactive(mainmenu[1],20,6,&y);

        }

    }



    optionsmain:
       if(option_allow == 1)
        {
            system("cls");
            interactive(optionMenu,20,3,&y);

            getch();
            if(getch()=='\n')
            {
                    option_allow = 0;
                    option_menu_allow = 1;
                    printf("\t%d",y);
                    switch(y)
                    {
                        case 0:
                            system("cls");
                            printf("\tsound menu 1");
                            interactive(soundMenu,20,2,&y);
                            getchar();
                            getch();
                        case 1:
                            system("cls");
                            printf("\tredefine menu 2");
                            interactive(redefineMenu,20,4,&y);
                            getchar();
                            getch();
                        case 2:
                            system("cls");
                            printf("\tcontrol mode 3");
                            interactive(controlModeMenu,6,2,&y);
                            getchar();
                            getch();


                    }

            }
        }

    help:
        if(help_allow == 1)
        {
            system("cls");
            printf("\n %s",helpText);
            printf("\n Press any key to redirect to main menu");

            getchar();
            getch();
            help_allow = 0;
            main_allow = 1;
            exit_allow = 0;

            goto startmain;


        }

    soundoption:
        if(sound_allow==1)
        {
                system("cls");
                interactive(soundMenu,20,2,&y);
        }




    while(1)
    {
        Sleep(50);
        kb = gameinput(0);

        if(!kb.nothing)
        {
            if(kb.down)
                if(main_allow)
                    incremod(&y,7);
                else if(option_allow)
                    incremod(&y,3);


            if(kb.up)
                if(main_allow)
                    decremod(&y,7);
                else if(option_allow)
                    decremod(&y,3);
            if(kb.enter)
            {
                if(main_allow)
                {


                if(!menudata.gamerunning)
                {
                    y++;
                }

                switch (y)
                {
                    case 0:         //Call the resume operation

                    if(can_continue == FALSE)
                    {
                        goto startmain;
                    }
                    break;

                    case 1:          //Call the play operation
                        can_continue == TRUE;
                    break;

                    case 2:         //call options
                        option_allow = 1;
                        main_allow = help_allow = 0;

                        goto optionsmain;

                    break;

                    case 3:         //levels

                    break;

                    case 4:         //high scores

                    break;

                    case 5:
                        option_allow = main_allow = 0;

                        help_allow = 1;
                        goto help;         //help

                    break;

                    case 6:         //exit
                        if(exit_allow == 1)
                            goto exitMenu;
                        else
                        {
                            exit_allow = 1;
                            goto startmain;
                        }
                    break;
                }
                break;
                }

                if(option_allow == 1)
                {
                    option_allow = 0;

                    switch(y)
                    {
                    case 0:
                        sound_allow = 1;
                        goto soundoption;
                    }

                }
            }

            if(kb.esc)
            {
                exitMenu:
                system("cls");
                printf("\n Thank you");
                getchar();
                break;
            }
            goto startmain;
        }
    }
}
//menudata.options.soundon = !menudata.options.soundon;

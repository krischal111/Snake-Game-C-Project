// Header files
#include "allheaders.h"

// Data (struct, enum and constants)
#include "dataandconstants.h"

char playgroundstr[20][20][3];              // 2 characters for each block // never wanna look back on this
struct makeplayground playground;
struct makesnake snake;

// Functions ####################################################
#include "displayfuncs.h"
#include "customcalc.h"
#include "kbandmouse.h"
#include "soundthings.h"

enum doubledirection doubledirectinof(enum direction, enum direction);
char * bodyblock(enum doubledirection);
int getsnaketomove();
void printsnake();

int main()
{
    // playtuneusing(gameovermusic, gameovermusiclength);

    srand(time(NULL));
    system("cls");
    snake.length = 15;
    snake.body[0].location = (COORD){0,0};
    snake.body[0].going = right;

    getsnaketomove();
}

int getsnaketomove()
{
    enum direction wheredoigo=snake.body[0].going;
    int offsetcounter=0;
    int mod120counter=0;
    struct keyboardinputs kb;           // stores all inputs allowed in this game

    displayborder();
    while(1)
    {

        //################################### controls how fast snake moves
        Sleep(100);

        /*
        offsetcounter++;
        offsetcounter%=2;
        */ 
        incremod(&offsetcounter,2);             // This replaces the commented code
        incremod(&mod120counter,120);
        // locprint(0,50,"");
        // printf("%3d",mod120counter);

        // ############################################ controls human or AI mode
        kb=gameinput(0);

        
        {                   // controls exit or pause of game
        if(kb.esc)
        {
            break;
        }
        else if(kb.space)
        {
        do
        {
            Sleep(100);
            kb = gameinput(0);              // wait for human input when paused
        }while(kb.nothing);
        }
        }

        switch(snake.body[0].going)          // decide direction according to input
        {
            case right:
            case left:
            {
                if(kb.down)
                wheredoigo = down;
                else if(kb.up)
                wheredoigo = up;
            }
            break;
            case up:
            case down:
            {
                if(kb.right)
                wheredoigo = right;
                else if(kb.left)
                wheredoigo = left;
            }
            break;
        }


        // erases last 3 tails
        for(int i = snake.length-4; (i>=0) && i<snake.length; i++)
        {
            gameprint(snake.body[i].location.Y, snake.body[i].location.X,"  ");
        }

        //############################## spot for increasing/decreasing snake's length
        enum direction thisdirection, nextdirection;
        enum doubledirection bodyturntype;

        // move body
        for(int i = snake.length; i>0; i--)
        {
            snake.body[i] = snake.body[i-1];
        }

        // this moves the head to controlled direction
        switch(wheredoigo)
        {
            case up:
            snake.body[0].location.Y = mod(snake.body[0].location.Y-1,20);    // Decrements by 1 with modulo 20
            break;

            case down:
            snake.body[0].location.Y = mod(snake.body[0].location.Y+1,20);    // Increments by 1 with modulo 20 (customcalc.h)
            break;

            case left:
            snake.body[0].location.X = mod(snake.body[0].location.X-1,20);    // Comes from opposite end after entering from one
            break;

            case right:
            snake.body[0].location.X = mod(snake.body[0].location.X+1,20);    // Comes from opposite end after entering from one
            break;
        }
        snake.body[0].going = wheredoigo;

        printsnake();

        cursorloc(0,30);

        /*
        switch(mod120counter%10)
        {
        case 0:
        case 1:
        case 3:
        case 4:
        printf("\b\bo~");
        }
        */
    }
}





// Ignore these
enum doubledirection doubledirectinof(enum direction d0, enum direction d1)
{
    enum doubledirection dd;
    
    switch(d0)
    {
        case up:
        switch(d1)
        {
            case up:        dd = uup;       break;
            case down:      dd = opposite;  break;
            case left:      dd = upleft;    break;
            case right:     dd = upright;   break;
        }
        break;

        case down:
        switch(d1)
        {
            case up:        dd = opposite;  break;
            case down:      dd = ddown;     break;
            case left:      dd = downleft;  break;
            case right:     dd = downright; break;
        }
        break;

        case left:
        switch(d1)
        {
            case up:        dd = leftup;    break;
            case down:      dd = leftdown;  break;
            case left:      dd = lleft;     break;
            case right:     dd = opposite;  break;
        }
        break;

        case right:
        switch(d1)
        {
            case up:        dd = rightup;   break;
            case down:      dd = rightdown; break;
            case left:      dd = opposite;  break;
            case right:     dd = rright;    break;
        }
        break;
    }

    return dd;
} 

char * bodyblock(enum doubledirection dd)
{
    char * c;

    switch(dd)
    {
        case upright:
        c = (char *) upright_s;
        break;

        case rightdown:
        c = (char *) rightdown_s;
        break;

        case downleft:
        c = (char *) downleft_s;
        break;

        case leftup:
        c = (char *) leftup_s;
        break;

        case uup:
        c = (char *) uup_s;
        break;

        case ddown:
        c = (char *) ddown_s;
        break;

        case rright:
        c = (char *) rright_s;
        break;

        case lleft:
        c = (char *) lleft_s;
        break;

        case leftdown:
        c = (char *) leftdown_s;
        break;

        case downright:
        c = (char *) downright_s;
        break;

        case rightup:
        c = (char *) rightup_s;
        break;

        case upleft:
        c = (char *) upleft_s;
        break;
    }

    return c;
}


// 

// Important one
void printsnake()
{
    // Erase tail:
    gameprint(snake.body[snake.length].location.Y, snake.body[snake.length].location.X, "  ");
    gameprint(snake.body[snake.length-1].location.Y, snake.body[snake.length-1].location.X, "  ");

    // Print body:
    for(int i = snake.length-1; i>0; i--)
    {
        cursorloc(snake.body[i].location.Y+1,snake.body[i].location.X+1);
        printf("\333\333");
    }

    // Print head:
    gameprint(snake.body[0].location.Y, snake.body[0].location.X, "oo");
}


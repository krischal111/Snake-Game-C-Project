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

int getsnaketomove();
void printsnake();
void displayinfos(struct makegameinfo);

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
    struct makegameinfo gameinfo;

    displayborder(20,20);
    while(1)
    {

        //############################################ controls how fast snake moves
        Sleep(100);

        incremod(&offsetcounter,2);
        incremod(&mod120counter,120);

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

        //############################## spot for increasing/decreasing snake's length
        // if(mod120counter%20 == 0)
        // snake.length++;

        // where whole body moves
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
        
        // Increase score here;
        gameinfo.score = 0;
        gameinfo.kb = kb;
        gameinfo.level = 5;
        gameinfo.soundon = 1;
        gameinfo.gametype = 0;
        gameinfo.direction = wheredoigo;
        displayinfos(gameinfo);

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






// Important one
void printsnake()
{
    int l = snake.length;
    // Erase tail:
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "  ");        l--;

    // Print tail:
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\260\260");        l--;
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\261\261");        l--;
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\262\262");        l--;


    // These are half tails
    // for(int i = snake.length-1; i>snake.length -4; i--)
    // {
    //     gameprint(snake.body[i].location.Y, snake.body[i].location.X, bodyblock(doubledirectinof(snake.body[i].going, snake.body[i-1].going)));
    // }


    // Print body:
    for(int i = snake.length-4; i>0; i--)
    {
        gameprint(snake.body[i].location.Y, snake.body[i].location.X, "\333\333");
        
        // Half body mode
        // gameprint(snake.body[i].location.Y, snake.body[i].location.X, bodyblock(doubledirectinof(snake.body[i].going, snake.body[i-1].going)));
    }


    // Print head:
    gameprint(snake.body[0].location.Y, snake.body[0].location.X, "oo");

    cursorloc(0,30);
}

void displayinfos(struct makegameinfo g)
{
    // g.gametype;
    // g.kb;
    // g.level;
    // g.score;
    // g.soundon;
    // g.direction;
    locatecursor(1, 60);
    printf("Level = %10d",g.level);
    locatecursor(2,60);
    printf("Score = %10d",g.score);
    locatecursor(3,60);
    printf("Snake Length = %3d", snake.length);

    locatecursor(5,60);
    switch(g.direction)
    {
        case up:
        printf("Up   ");
        break;

        case down:
        printf("Down ");
        break;

        case left:
        printf("Left ");
        break;

        case right:
        printf("Right");
        break;        
    }

    locprint(6,61,"\332\304\277");
    locprint(7,63,"\263\b\b\b\263");
    locprint(8,59,"\332\304\305\304\305\304\277");
    locprint(9,65,"\263\b\b\b\263\b\b\b\263\b\b\b\263");
    locprint(10,59,"\300\304\301\304\301\304\331");
    locatecursor(7,62);
    if(g.kb.up)
    printf("\030");
    else
    printf(" ");

    locatecursor(9,62);
    if(g.kb.down)
    printf("\031");
    else
    printf(" ");

    locatecursor(9,60);
    if(g.kb.left)
    printf("\021");
    else
    printf(" ");

    locatecursor(9,64);
    if(g.kb.right)
    printf("\020");
    else
    printf(" ");
}
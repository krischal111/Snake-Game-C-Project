// Header files
#include "allheaders.h"

// Data (struct, enum and constants)
#include "dataandconstants.h"

char playgroundstr[20][20][3];              // 2 characters for each block // never wanna look back on this
struct makeplayground playground;
struct makesnake snake;
struct makemenudata menudata;

// Functions ####################################################
#include "displayfuncs.h"
#include "customcalc.h"
#include "kbandmouse.h"
#include "soundthings.h"

int getsnaketomove();
void printsnake();
void displayinfos(struct makegameinfo);
enum direction getdirection(enum direction, struct keyboardinputs);
void movesnake(enum direction);
void fastness();
void startgame(_Bool);

void fastness()
{
    Sleep(900/menudata.level);
}

int main()
{
    srand(time(NULL));
    startgame(FALSE);
}

void startgame(_Bool resumemode)
{
    system("cls");
    ShowConsoleCursor(FALSE);
    if(resumemode)
    {
        getsnaketomove();
    }
    else
    {
        menudata.level = 9;
        snake.length = 5;
        snake.body[0].location = (COORD) {0,0};
        snake.body[0].going    = right;
        getsnaketomove();
    }
}

int getsnaketomove()
{ 
    enum direction wheredoigo=snake.body[0].going;
    int mod120counter=0;
    struct keyboardinputs kb;           // stores all inputs allowed in this game
    struct makegameinfo gameinfo;

    displayborder(20,20);
    while(1)
    {

        // Fastness:
        fastness();
        // Sleep(100);
        incremod(&mod120counter,120);

        // ############################################ controls human or AI mode
        kb=gameinput(0);
        
        // controls exit or pause of game
        if(kb.esc)        break;
        else if(kb.space)
        do
        {   Sleep(100);
            kb = gameinput(0);              // wait for human input when paused
        }while(kb.nothing);

        // decide direcction, and move snake
        wheredoigo = getdirection(snake.body[0].going, kb);          
        //############################## spot for increasing/decreasing snake's length

        movesnake(wheredoigo);
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

    }
    menudata.gamerunning = TRUE;
    ShowConsoleCursor(TRUE);
}



enum direction getdirection(enum direction currentdirection, struct keyboardinputs kb)
{
    enum direction d=currentdirection;

    switch(currentdirection)          // decide direction according to input
    {
        case right:
        case left:
        {
            if(kb.down)
            d = down;
            else if(kb.up)
            d = up;
        }
        break;

        case up:
        case down:
        {
            if(kb.right)
            d = right;
            else if(kb.left)
            d = left;
        }
        break;
    }
    return d;    
}

void movesnake(enum direction d)
{
    // where whole body moves
    for(int i = snake.length; i>0; i--)
    {
        snake.body[i] = snake.body[i-1];
    }

    // this moves the head to controlled direction
    switch(d)
    {
        case up:
        decremods(&snake.body[0].location.Y, 20);    // Decrements by 1 with modulo 20                  
        break;

        case down:
        incremods(&snake.body[0].location.Y, 20);    // Increments by 1 with modulo 20 (customcalc.h)   
        break;

        case left:
        decremods(&snake.body[0].location.X, 20);    // Comes from opposite end after entering from one 
        break;

        case right:
        incremods(&snake.body[0].location.X, 20);    // Comes from opposite end after entering from one 
        break;
    }
    snake.body[0].going = d;
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

    int starty = 6, startx = 60;

    locprint(starty + 0, startx +4,"\332\304\304\304\277");
    locprint(starty + 1, startx +8,"\263\b\b\b\b\b\263");
    locprint(starty + 2, startx + 0,"\332\304\304\304\305\304\304\304\305\304\304\304\277");
    locprint(starty + 3, startx + 12,"\263\b\b\b\b\b\263\b\b\b\b\b\263\b\b\b\b\b\263");
    locprint(starty + 4, startx + 0,"\300\304\304\304\301\304\304\304\301\304\304\304\331");
    locatecursor(starty + 1, startx + 6);
    if(g.kb.up)
    printf("\030");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 6);
    if(g.kb.down)
    printf("\031");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 2);
    if(g.kb.left)
    printf("\021");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 10);
    if(g.kb.right)
    printf("\020");
    else
    printf(" ");
}


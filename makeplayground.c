#include "Custom Headers\allheaders.h"
#include "Custom Headers\dataandconstants.h"


char playgroundstr[20][20][3];              // 2 characters for each block // never wanna look back on this
struct makeplayground playground;
struct makeportal portals[5];
int numberofportals = 0;


//###############################################################################
// function declarations
// Related to snake game
void displayplayground(int);
void readplayground(int);
void displayborder();
void gotoxy(int, int);
void cursorloc(int, int);
struct keyboardinputs devinput();    // from developer or designer
void inputplayground();
int mod(int,int);

int main()
{
    // Initialize part
    // Creating emptyness inside
    for(int i = 0; i<20; i++)
    for(int j = 0; j<20; j++)
    playground.blocktype[i][j] = empty;

    printf("\n");
    displayborder();
    displayplayground(1);
    inputplayground();

    for(;;)
    {
        break;
    }

}

void inputplayground()
{
    struct keyboardinputs kb;
    int counter;
    int portalcounter=0;
    COORD location;
    {
        location.X = 0;
        location.Y = 0;
    }

    char curchar[2][3] = {"  ","\260\260"};
    strcpy(curchar[0],playgroundstr[location.X][location.Y]);

    for(;;)
    {
        counter++;
        counter = mod(counter,120);

        Sleep(100);
        kb = devinput();

        if(kb.esc)
        return ;

        if(!kb.nothing)
        {
            // print corresponding chars in corresponding location
            if(kb.up || kb.down || kb.left || kb.right)
            {
            cursorloc(location.Y+1,location.X+1);
            printf("%s",curchar[0]);

            if(kb.up)
                location.Y--;
            if(kb.down)
                location.Y++;
            if(kb.left)
                location.X--;
            if(kb.right)
                location.X++;
            location.X = mod(location.X,20);
            location.Y = mod(location.Y,20);
            }

            // Real blocks edit cases
            {
            if(kb.B)    // Barrier edit
            {
                playground.blocktype[location.X][location.Y] = barrier;
                strcpy(playgroundstr[location.X][location.Y],barrier_b);
            }

            if(kb.P)    // Portal edit
            {
            portalcounter++;
            if(portalcounter<=10)
            {
                if(portalcounter & 1)       // true if portalcounter is odd
                {
                    portals[numberofportals].mouth = location;
                }
                else                       // case of even
                {
                    portals[numberofportals].anus = location;
                    
                    _Bool sameentryexit = (portals[numberofportals].mouth.X == portals[numberofportals].anus.X) &&
                    (portals[numberofportals].mouth.Y == portals[numberofportals].anus.Y);

                    if(sameentryexit)
                    {
                        portalcounter-=2;
                    }
                    else
                    {
                        COORD c;

                        c = portals[numberofportals].mouth;
                        playground.blocktype[c.X][c.Y] = portal;
                        strcpy(playgroundstr[c.X][c.Y],portal_b);
                        cursorloc(c.Y+1, c.X+1);
                        printf("%s",portal_b);

                        c = portals[numberofportals].anus;
                        playground.blocktype[c.X][c.Y] = portal;
                        strcpy(playgroundstr[c.X][c.Y],portal_b);
                        cursorloc(c.Y+1, c.X+1);
                        printf("%s",portal_b);

                        numberofportals++;
                    }
                }
            }
            }

            strcpy(curchar[0],playgroundstr[location.X][location.Y]);
            cursorloc(location.Y+1,location.X+1);
            printf("%s",curchar[0]);
            }

            strcpy(curchar[0],playgroundstr[location.X][location.Y]);
            cursorloc(location.Y+1,location.X+1);
        }

    }
}

void displayborder()
{
    //Corners first:
    cursorloc(0,0);
    printf("%s",topleft_b);
    cursorloc(0,21);
    printf("%s",topright_b);
    cursorloc(21,0);
    printf("%s",bottomleft_b);
    cursorloc(21,21);
    printf("%s",bottomright_b);
    
    //horizontal and vertical borders
    for(int i=1; i<21; i++)
    {
        //horizontal on top and bottom:
        cursorloc(0,i);
        printf("%s",horizontal_b);
        cursorloc(21,i);
        printf("%s",horizontal_b);

        //vertical on left and right:
        cursorloc(i, 0);
        printf("%s",vertical_b);
        cursorloc(i, 21);
        printf("%s",vertical_b);
    }
}


void displayplayground(int mode)
{                               // I dont want to see this block again
    for(int i = 0; i<20; i++)
    {
    for(int j = 0; j<20; j++)
    {
        switch(playground.blocktype[i][j])
        {
            case empty:             // empty block
            {
                strcpy(playgroundstr[i][j],empty_b);
            }
            break;
            case barrier:           // barrier block
            {
                strcpy(playgroundstr[i][j],barrier_b);
            }
            break;
            case portal:            // portal block
            {
                strcpy(playgroundstr[i][j],portal_b);
            }
            break;
            default:                // default is empty
            {
                strcpy(playgroundstr[i][j],empty_b);
            }
        }
        cursorloc(j+1,i+1);
        printf("%s",playgroundstr[i][j]);

    }
    }
}

void gotoxy(int x, int y){
COORD CRD;
CRD.X=x;
CRD.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

void cursorloc(int y, int x)
{
    gotoxy(2*x,y);
}

struct keyboardinputs devinput()
{
    struct keyboardinputs input;

    static int counter;
    counter++; counter%=20;

    {
        input.up    = GetAsyncKeyState(VK_UP) & 0x01;
        input.down  = GetAsyncKeyState(VK_DOWN) & 0x01;
        input.right = GetAsyncKeyState(VK_RIGHT) & 0x01;
        input.left  = GetAsyncKeyState(VK_LEFT) & 0x01;
        input.enter = GetAsyncKeyState(VK_RETURN) & 0x01;
        input.space = GetAsyncKeyState(VK_SPACE) & 0x01;
        input.esc   = GetAsyncKeyState(VK_ESCAPE) & 0x01;
        input.B     = GetAsyncKeyState(0x42) & 0x01;        // B = 0x42 = ASCII 66
        input.P     = GetAsyncKeyState(0x50) & 0x01;        // P = 0x50 = ASCII 80
        
        input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.space||input.esc||input.B||input.P);
        return input;
    }
}

int mod(int number, int divider)
{   while(number<0) number+=divider;
    return number%divider;
}
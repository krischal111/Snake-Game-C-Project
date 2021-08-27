// Available functions
void displayborder(int, int);
void displayplayground(int);
void gotoxy(int, int);
void cursorloc(int, int);
void gameprint(int, int, const char *);
void locprint(int, int, char *);
void locatecursor(int, int);
enum doubledirection doubledirectinof(enum direction, enum direction);
const char * bodyblock(enum doubledirection);


// Required variables
/*
    globally declared:
    char playgroundstr[20][20]
    struct makeplayground playground;
*/

void displayborder(int x,int y)
{
    int xmax = x+1, ymax = y+1;
    
    //Corners first:
    cursorloc(0,0);
    printf("%s",topleft_b);
    cursorloc(0,xmax);
    printf("%s",topright_b);
    cursorloc(ymax,0);
    printf("%s",bottomleft_b);
    cursorloc(ymax,xmax);
    printf("%s",bottomright_b);
    
    //horizontal and vertical borders
    for(int i=1; i<xmax; i++)
    {
        //horizontal on top and bottom:
        cursorloc(0,i);
        printf("%s",horizontal_b);
        cursorloc(ymax,i);
        printf("%s",horizontal_b);
    }
    for(int i=1; i<ymax; i++)
    {
        //vertical on left and right:
        cursorloc(i, 0);
        printf(" %s",vertical_b);
        cursorloc(i, xmax);
        printf("%s ",vertical_b);
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

void gotoxy(int x, int y)
{
    COORD CRD;
    CRD.X=x;
    CRD.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

void locatecursor(int y, int x)
{
    COORD CRD;
    CRD.X=x;
    CRD.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

void cursorloc(int y, int x)
{
    gotoxy(2*x,y);
}

void gameprint(int y, int x, const char *c)
{
    cursorloc(y+1,x+1);
    printf("%s",c);
}

void locprint(int y, int x, char *c)
{
    gotoxy(x, y);
    printf("%s",c);
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

const char * bodyblock(enum doubledirection dd)
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

void ShowConsoleCursor(_Bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

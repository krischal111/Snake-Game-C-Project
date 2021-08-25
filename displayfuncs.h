// Available functions
void displayborder();
void displayplayground(int);
void gotoxy(int, int);
void cursorloc(int, int);
void gameprint(int, int, char *);
void locprint(int, int, char *);

// Required variables
/*
    globally declared:
    playgroundstr[20][20]
    playground.blocktype[20][20]
*/

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
        printf(" %s",vertical_b);
        cursorloc(i, 21);
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

void cursorloc(int y, int x)
{
    gotoxy(2*x,y);
}

void gameprint(int y, int x, char *c)
{
    cursorloc(y+1,x+1);
    printf("%s",c);
}

void locprint(int y, int x, char *c)
{
    gotoxy(x, y);
    printf("%s",c);
}


// Avaliable functions
int mod(int, int);
int addmod(int, int, int);
void incremod(int *, int);
void decremod(int *, int);
void incremods(short *, int);
void decremods(short *, int);
COORD randomcoordmod(int modulodivisor);
COORD randomcoord();


int mod(int number, int divisor)
{   while(number<0) number+=divisor;
    return number%divisor;
}

int addmod(int number, int addition, int modulodivisor)
{
    return mod((number + addition),modulodivisor);
}

void incremod(int *a, int d)
{
    (*a)++;
    while((*a)<0) (*a)+=d;
    (*a) %= d;
}

void decremod(int *a, int d)
{
    (*a)--;
    while((*a)<0) (*a)+=d;
    (*a) %= d;
}

void incremods(short *a, int d)
{
    (*a)++;
    while((*a)<0) (*a)+=d;
    (*a) %= d;
}

void decremods(short *a, int d)
{
    (*a)--;
    while((*a)<0) (*a)+=d;
    (*a) %= d;
}



COORD randomcoordmod(int modulodivisor)
{
    COORD c;
    c.X = mod(rand(),modulodivisor);
    c.Y = mod(rand(),modulodivisor);
    return c;
}

COORD randomcoord()
{
    COORD c;
    c.X = (short) (rand()%20);
    c.Y = (short) (rand()%20);
    return c;
}


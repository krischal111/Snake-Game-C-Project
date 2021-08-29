struct keyboardinputs devinput();       // from developer or designer
struct keyboardinputs gameinput(int);   // from gamer
struct keyboardinputs menuinputs();  // at menu

struct keyboardinputs devinput()
{
    struct keyboardinputs input;

    if((GetAsyncKeyState(VK_LSHIFT) & MSB_s) && (GetAsyncKeyState(VK_RSHIFT) & MSB_s) && (GetAsyncKeyState(VK_HOME) & MSB_s))
    exit(0);
    
    {
        input.up    = (GetAsyncKeyState(VK_UP) & MSB_LSB_s);
        input.down  = GetAsyncKeyState(VK_DOWN) & MSB_LSB_s;
        input.right = GetAsyncKeyState(VK_RIGHT) & MSB_LSB_s;
        input.left  = GetAsyncKeyState(VK_LEFT) & MSB_LSB_s;
        input.enter = GetAsyncKeyState(VK_RETURN) & MSB_LSB_s;
        input.space = GetAsyncKeyState(VK_SPACE) & MSB_LSB_s;
        input.esc   = GetAsyncKeyState(VK_ESCAPE) & MSB_LSB_s;
        input.B     = GetAsyncKeyState(0x42) & MSB_LSB_s;        // B = 0x42 = ASCII 66
        input.P     = GetAsyncKeyState(0x50) & MSB_LSB_s;        // P = 0x50 = ASCII 80



        input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.space||input.esc||input.B||input.P);
        return input;
    }
}

struct keyboardinputs gameinput(int mode)
{
    struct keyboardinputs input;

    static int counter;
    counter++; while(counter<0) counter+=20; counter%=20;

    input.space = GetAsyncKeyState(VK_SPACE) & 0x01;
    input.esc   = GetAsyncKeyState(VK_ESCAPE) & 0x01;

    if((GetAsyncKeyState(VK_LSHIFT) & MSB_s) && (GetAsyncKeyState(VK_RSHIFT) & MSB_s) && (GetAsyncKeyState(VK_HOME) & MSB_s))
    exit(0);

    if(mode == 0)        // Human mode
    {
        input.up    = GetAsyncKeyState(VK_UP) & MSB_LSB_s    || (GetAsyncKeyState(0x57) & MSB_LSB_s); // W
        input.down  = GetAsyncKeyState(VK_DOWN) & MSB_LSB_s  || (GetAsyncKeyState(0x53) & MSB_LSB_s); // S
        input.right = GetAsyncKeyState(VK_RIGHT) & MSB_LSB_s || (GetAsyncKeyState(0x44) & MSB_LSB_s); // D
        input.left  = GetAsyncKeyState(VK_LEFT) & MSB_LSB_s  || (GetAsyncKeyState(0x41) & MSB_LSB_s); // A
        input.enter = GetAsyncKeyState(VK_RETURN) & MSB_LSB_s;

        input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.space||input.esc);

        return input;
    }

    if(mode ==1)       // artificial intelligence mode
    {
        input.up    = 0;
        input.down  = 0;
        input.left  = 0;
        input.right = 0;

        enum direction h, v, AIdirection;

        COORD abscdiff, coorddifferencemod = 
        coordsubtractmod((gameelements.presenceofpowerfood)?gameelements.powerfoood:gameelements.foood,snake.body[0].location, 20, 20);

        if(coorddifferencemod.X<10)
        h = right;
        else
        h = left;

        if(coorddifferencemod.Y<10)
        v = down;
        else
        v = up;

        abscdiff.X = (coorddifferencemod.X >= 10)?20-coorddifferencemod.X : coorddifferencemod.X;
        abscdiff.Y = (coorddifferencemod.Y >= 10)?20-coorddifferencemod.Y : coorddifferencemod.Y;

        if(abscdiff.X>abscdiff.Y)
        AIdirection = h;
        else
        AIdirection = v;

        switch(AIdirection)
        {
            case up:
            input.up    = 1;
            break;
            case down:
            input.down  = 1;
            break;
            case right:
            input.right = 1;
            break;
            case left:
            input.left  = 1;
            break;
        }

        input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.space||input.esc);
        return input;
    }
}

void clearinput()
{

    GetAsyncKeyState(VK_ESCAPE);
    GetAsyncKeyState(VK_BACK);
    GetAsyncKeyState(VK_UP);    GetAsyncKeyState(0x57);
    GetAsyncKeyState(VK_DOWN);  GetAsyncKeyState(0x53);
    GetAsyncKeyState(VK_RIGHT); GetAsyncKeyState(0x44);
    GetAsyncKeyState(VK_LEFT);  GetAsyncKeyState(0x41);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_SHIFT);

    for(int i='A'; i<= 'Z'; i++)
    {
        GetAsyncKeyState(i);
    }

    for(int i = 0; i<=9; i++)
    {
        GetAsyncKeyState('0'+i);
        GetAsyncKeyState(VK_NUMPAD0 + i);
    }

    return;
}

struct keyboardinputs menuinput()
{
    Sleep(50);
    struct keyboardinputs input;

    input.esc   = (GetAsyncKeyState(VK_ESCAPE) & MSB_LSB_s)      || (GetAsyncKeyState(VK_BACK) * MSB_LSB_s);
    input.up    = (GetAsyncKeyState(VK_UP) & MSB_LSB_s)      || (GetAsyncKeyState(0x57) & MSB_LSB_s); // W
    input.down  = (GetAsyncKeyState(VK_DOWN) & MSB_LSB_s)    || (GetAsyncKeyState(0x53) & MSB_LSB_s); // S
    input.right = (GetAsyncKeyState(VK_RIGHT) & MSB_LSB_s)   || (GetAsyncKeyState(0x44) & MSB_LSB_s); // D
    input.left  = (GetAsyncKeyState(VK_LEFT) & MSB_LSB_s)    || (GetAsyncKeyState(0x41) & MSB_LSB_s); // A
    input.enter = (GetAsyncKeyState(VK_RETURN) & MSB_LSB_s);

    input.numpress = FALSE;
    for(int i = 0; i<=9; i++)
    {
        if(!input.numpress && ((GetAsyncKeyState('0'+i) & 0x01) || (GetAsyncKeyState(VK_NUMPAD0 + i) & 0x01)))
        {       // if input from number keys or numpad number keys
            input.numpress = TRUE;
            input.number = i;
        }
    }

    input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.esc||input.numpress);

    if((GetAsyncKeyState(VK_LSHIFT) & MSB_s) && (GetAsyncKeyState(VK_RSHIFT) & MSB_s) && (GetAsyncKeyState(VK_HOME) & MSB_s))
    exit(0);

    return input;
}

struct alphainputs normalinput()
{
    _Bool shift, caps;
    struct alphainputs a;
    for(int i='A'; i<= 'Z'; i++)
    {
        caps = GetKeyState(VK_CAPITAL) & LSB_s;
        shift = GetAsyncKeyState(VK_SHIFT) & MSB_s;
        if(GetAsyncKeyState(i) & LSB_s)
        {
            a.c = ((caps||shift) && (!caps || !shift))?i:(32+i);
            a.nothing = 0;
            return a;
            break;
        }
    }

    for(int i = 0; i<=9; i++)
    {
        if(((GetAsyncKeyState('0'+i) & LSB_s) && !(GetAsyncKeyState(VK_SHIFT) & MSB_s))|| (GetAsyncKeyState(VK_NUMPAD0 + i) & LSB_s))
        {
            a.c = i;
            a.nothing = 0;
            return a;
        }
    }

    if(GetAsyncKeyState(VK_SPACE) & LSB_s)
    {
        a.c = ' ';
        a.nothing = 0;
        return a;
    }

    if(GetAsyncKeyState(VK_RETURN) & MSB_s)
    {
        a.c = VK_RETURN;
        a.nothing = 0;
        return a;
    }

    if(GetAsyncKeyState(VK_BACK) & MSB_s)
    {
        a.c = VK_BACK;
        a.nothing = 0;
        return a;
    }

    a.nothing = !a.c;
    return a;
}

int scantext(char *str, int n)
{
    for(int i = 0; i<n; i++)
    {
        normalinput();
    }
    Sleep(100);
    struct alphainputs a;
    for(int i = 0; i<n; i++)
    {    
        lstart:
        do
        {
            Sleep(100);
            a = normalinput();
        }while((a.nothing)||  ( (i==(n-1)) && (a.c != VK_RETURN) ));

        if(a.c == VK_RETURN)
        {
            printf("\n");
            a.c = 0;
            str[i] = a.c;
            return i;
        }

        if(a.c == VK_BACK)
        {
            if(i>0)
        {            
            printf("\b \b");
            a.c = 0;
            i--;
            str[i] = a.c;
            goto lstart;
        }
            else if(i == 0)
        {
            goto lstart;
        }

        }
        
        printf("%c",a.c);
        str[i] = a.c;
    }
    return n-1;
}
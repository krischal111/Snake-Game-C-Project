struct keyboardinputs devinput();       // from developer or designer
struct keyboardinputs gameinput(int);   // from gamer
struct keyboardinputs menuinputs();  // at menu

struct keyboardinputs devinput()
{
    struct keyboardinputs input;

    if((GetAsyncKeyState(VK_LSHIFT) & 0x01) && (GetAsyncKeyState(VK_RSHIFT) & 0x01) && (GetAsyncKeyState(VK_HOME) & 0x01))
    exit(0);
    
    {
        input.up    = (GetAsyncKeyState(VK_UP) & 0x01);
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

struct keyboardinputs gameinput(int mode)
{
    struct keyboardinputs input;

    static int counter;
    counter++; while(counter<0) counter+=20; counter%=20;

    input.space = GetAsyncKeyState(VK_SPACE) & 0x01;
    input.esc   = GetAsyncKeyState(VK_ESCAPE) & 0x01;

    if((GetAsyncKeyState(VK_LSHIFT) & 0x01) && (GetAsyncKeyState(VK_RSHIFT) & 0x01) && (GetAsyncKeyState(VK_HOME) & 0x01))
    exit(0);

    if(mode == 0)        // Human mode
    {
        input.up    = GetAsyncKeyState(VK_UP) & 0x01    || (GetAsyncKeyState(0x57) & 0x01); // W
        input.down  = GetAsyncKeyState(VK_DOWN) & 0x01  || (GetAsyncKeyState(0x53) & 0x01); // S
        input.right = GetAsyncKeyState(VK_RIGHT) & 0x01 || (GetAsyncKeyState(0x44) & 0x01); // D
        input.left  = GetAsyncKeyState(VK_LEFT) & 0x01  || (GetAsyncKeyState(0x41) & 0x01); // A
        input.enter = GetAsyncKeyState(VK_RETURN) & 0x01;

        input.nothing = !(input.up||input.down||input.left||input.right||input.enter||input.space||input.esc);

        return input;
    }

    if(mode ==1)       // artificial intelligence mode
    {
        if(counter==0)
        {
        input.right = 0;
        input.down = -1;
        }

        if(counter==1)
        {
        input.right == -1;
        input.down = 0;
        }

        if(counter == 2)
        {
        input.nothing = -1;
        }
        return input;
    }
}

struct keyboardinputs menuinput()
{
    struct keyboardinputs input;

    input.esc   = (GetAsyncKeyState(VK_ESCAPE) & 0x01)  || (GetAsyncKeyState(VK_BACK) * 0x01);
    input.up    = (GetAsyncKeyState(VK_UP) & 0x01)      || (GetAsyncKeyState(0x57) & 0x01); // W
    input.down  = (GetAsyncKeyState(VK_DOWN) & 0x01)    || (GetAsyncKeyState(0x53) & 0x01); // S
    input.right = (GetAsyncKeyState(VK_RIGHT) & 0x01)   || (GetAsyncKeyState(0x44) & 0x01); // D
    input.left  = (GetAsyncKeyState(VK_LEFT) & 0x01)    || (GetAsyncKeyState(0x41) & 0x01); // A
    input.enter = (GetAsyncKeyState(VK_RETURN) & 0x01);

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

    if((GetAsyncKeyState(VK_LSHIFT) & 0x01) && (GetAsyncKeyState(VK_RSHIFT) & 0x01) && (GetAsyncKeyState(VK_HOME) & 0x01))
    exit(0);

    return input;
}

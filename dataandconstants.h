//###########################################################################
// Enums
enum color {background,cyan,yellow,purple,green,blue,red,orange, lightgray, darkgray,black};
enum direction {right, down, left, up};
enum doubledirection {upright,rightdown,downleft,leftup, uup, ddown, lleft, rright, leftdown,downright,rightup,upleft,opposite};
enum blocktype {empty, barrier, snakebody, food, powerfood, portal};

//###########################################################################
// Structs
struct keyboardinputs
{
    _Bool up,down,left,right,space,enter,esc;
    _Bool nothing;
    _Bool B, P;
    _Bool one, two, three, four, five, six, seven;
};

struct makeplayground
{
    enum blocktype blocktype[20][20];    // down 20 blocks, side 20 blocks
};

struct makeportal
{
    COORD start;
    COORD end;
    _Bool isthisaportal;
};

struct makesnake
{
    int length;
    struct 
    {
       COORD location;
       enum direction going;
    } body[400];
};

struct makegameinfo
{
    unsigned int score;
    int level;
    _Bool soundon;
    int gametype;
    struct keyboardinputs kb;
    enum direction direction;
};

struct scoredata
{
    char name[30];
    unsigned int score;
};

struct makemenudata
{
    _Bool gamerunning;
    struct options
    {
        _Bool soundon;
        _Bool AImode;
    } options;
    int level;
    int gametype;
};

struct makesound
{
    int f;
    int ms;
};

//###########################################################################
//Constants
const unsigned char softblock = 176, semisoftblock=177, semisolidblock=178, solidblock = 219;     // ░▒▓█
const unsigned char horizontal2border = 205,  vertical2border  = 186;                             //  ═ ║
const unsigned char topleft2border    = 201,  topmid2border    = 203,   topright2border     = 187;//  ╔╦╗
const unsigned char leftmid2border    = 204,  centre2border    = 206,   rightmid2border     = 185;//  ╠╬╣
const unsigned char bottomleft2border = 200,  bottommid2border = 202,   bottomright2border  = 188;//  ╚╩╝
const unsigned char horizontalborder  = 196,  verticalborder   = 179;                             //  ─ │ 304, 263
const unsigned char topleftborder     = 218,  topmidborder     = 194,   toprightborder      = 191;//  ┌┬┐ 332, 302, 277
const unsigned char leftmidborder     = 195,  centreborder     = 197,   rightmidborder      = 180;//  ├┼┤ 303, 305, 264
const unsigned char bottomleftborder  = 192,  bottommidborder  = 193,   bottomrightborder   = 217;//  └┴┘ 300, 301, 331
const unsigned char portalchar1       = 91,   portalchar2      = 93;                              //   []
const unsigned char upsolidblock      = 223,  downsolidblock   = 220;                             //  ▀ ▄

// Related to snake game
const char * empty_b       = "  ";
const char * topleft_b     = " \311";       //          "\272\311";
const char * topright_b    = "\273 ";       //          "\273\272";
const char * bottomleft_b  = " \310";       //          "\272\310";
const char * bottomright_b = "\274 ";       //          "\274\272";
const char * horizontal_b  = "\315\315";
const char * vertical_b    = "\272";
const char * barrier_b     = "\262\262";
const char * portal_b      = "[]";

const char * upright_s    = "\333\337";       //        █▀-->
const char * rightdown_s  = "\337\333";       //          -->▀█
const char * downleft_s   = "\334\333";       //          <--▄█
const char * leftup_s     = "\333\334";       //        █▄<--

const char * rright_s = "\337\337", * lleft_s = "\334\334";     // -->▀▀  ▄▄<--
const char * uup_s = "\333 ",       * ddown_s = " \333";        // '█ '  ' █'

const char * leftdown_s   = " \334";          //          ' ▄'<--
const char * downright_s  = " \337";          //          ' ▀'-->
const char * rightup_s    = "\337 ";           //           -->'▀ '
const char * upleft_s     = "\334 ";          //           <--'▄ '

char * helpmsg = "This is a snake game.";

struct makesound gameovermusic[] = 
{
    (struct makesound) {200, 300},
    (struct makesound) {220, 300},
    (struct makesound) {280, 500},
    (struct makesound) {225, 300},
    (struct makesound) {250, 300},
    (struct makesound) {300, 500},
    (struct makesound) {220, 300},
    (struct makesound) {250, 300},
    (struct makesound) {300, 300},
    (struct makesound) {250, 300},
    (struct makesound) {200, 700} 
};
int gameovermusiclength = 11;

    // IF soundon THEN
    //     SOUND 0, 0
    //     SOUND 200, 3
    //     SOUND 0, 0
    //     SOUND 220, 3
    //     SOUND 0, 0
    //     SOUND 280, 5
    //     SOUND 0, 0
    //     SOUND 225, 3
    //     SOUND 0, 0
    //     SOUND 250, 3
    //     SOUND 0, 0
    //     SOUND 300, 5
    //     SOUND 0, 0
    //     SOUND 220, 3
    //     SOUND 0, 0
    //     SOUND 250, 3
    //     SOUND 0, 0
    //     SOUND 300, 3
    //     SOUND 0, 0
    //     SOUND 250, 3
    //     SOUND 0, 0
    //     SOUND 200, 7
    //     SOUND 0, 0
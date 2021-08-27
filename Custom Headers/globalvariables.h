struct scoredata Best5Scores[5];        // Best5Scores

struct makemenudata menudata =           // Menudata
{
    .options =
    {
        .soundon = TRUE,
        .AImode = FALSE,
    },
    .level = 9,
    .gametype = 0,
};

int mod120counter=0;                    // Snake Game
struct makesnake snake;
struct makegameelements gameelements;
struct makeingameupdate ingameupdate;
struct makegameinfo gameinfo;

char playgroundstr[20][20][3];          // Display.h
struct makeplayground playground;

_Bool gameisrunning = FALSE;

struct makehackmode hackmode =
{
    .enablegameover = 1
};


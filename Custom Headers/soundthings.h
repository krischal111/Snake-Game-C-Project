typedef struct makesound {int f; /* frequency */     int t;  /*time*/} makesound;
typedef struct soundlist {int length;    struct makesound * sound;   } soundlist;
void playtuneusing(soundlist);

void playtuneusing(soundlist s)
{
    for(int i = 0; i < s.length; i++)
    {
        Beep(s.sound[i].f, s.sound[i].t);
    }
}

// Soundlist available:
makesound gmusic[] =
{
    {2750, 50},
    {2250, 70},
    {1950, 90},
    {1550, 110},
    {1150, 140},
    {750, 150},
    {750, 150},
    {550, 160},
    {550, 160},
    {250, 200},
    {250, 200},
    {250, 200},
    {200, 200},
    {200, 200},
    {100, 600},
};

soundlist gameovertune = {   .length = 15,   .sound = gmusic  };

makesound intromusic[] =
{
    {1,2}
};
soundlist introtune =   {   .length = 1  ,   .sound = intromusic};

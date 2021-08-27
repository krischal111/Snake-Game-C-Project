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
    {200, 300},
    {220, 300},
    {280, 500},
    {225, 300},
    {250, 300},
    {300, 500},
    {220, 300},
    {250, 300},
    {300, 300},
    {250, 300},
    {200, 700}
};

soundlist gameovertune = {   .length = 11,   .sound = gmusic  };

makesound intromusic[] =
{
    {1,2}
};
soundlist introtune =   {   .length = 1  ,   .sound = intromusic};
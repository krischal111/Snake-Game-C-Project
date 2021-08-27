typedef struct makesound {int f; /* frequency */     int t;  /*time*/} makesound;
typedef struct soundlist {int length;    struct makesound * sound;   } soundlist;

void playtuneusing(soundlist s)
{
    for(int i = 0; i < s.length; i++)
    {
        Beep(s.sound[i].f, s.sound[i].t);
    }
}

// Soundlist available:

//Game_over
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

//Game_start
makesound intromusic[] =
{
    {750, 50},
    {7500, 70},
    {1950, 90},
    {1550, 110},
    {1150, 140},
    {7500, 150},
    {7500, 150},
    {5500, 160},
    {5500, 160},
    {2500, 200},
    {2500, 200},
    {2500, 200},
    {2000, 200},
    {2000, 200},
    {2100, 200},
};
soundlist introtune =   {   .length = 15  ,   .sound = intromusic};

//Normal_food_eaten
makesound foodeatmusic[] =
{
    {2750, 150},
};
soundlist foodeattune =   {   .length = 1  ,   .sound = foodeatmusic};

//Powerup_eaten
makesound powereatmusic[] =
{
    {1750, 90},
    {1950, 50},
};
soundlist powereattune =   {   .length = 2  ,   .sound = powereatmusic};

//Portal_accessed
makesound portalmusic[] =
{
    {1250, 50},
    {1250, 50},
    {1950, 90},
    {1950, 90},
    {1150, 90},

};
soundlist portaltune =   {   .length = 5  ,   .sound = portalmusic};
// ############################# struct available:
struct makesound    {int f;         int ms;                     };
// struct soundlist    {int length;    struct makesound * sound;   };

// ############################# functions available:
void playtuneusing(struct makesound *,int);


void playtuneusing(struct makesound s[],int l)
{
    for(int i = 0; i<l; i++)
    {
        Beep(s[i].f, s[i].ms);
    }
}

// void playtuneusing2(struct soundlist s)
// {
//     for(int i = 0; i < s.length; i++)
//     {
//         Beep(s.sound[i].f, s.sound[i].ms);
//     }
// }



// Soundlist available:
// struct soundlist    gameovertune =
// {
//     (int) 11,                           // length
//     (struct makesound *)                // pointer to the array of the struct
//     {
//     (struct makesound) {200, 300},
//     (struct makesound) {220, 300},
//     (struct makesound) {280, 500},
//     (struct makesound) {225, 300},
//     (struct makesound) {250, 300},
//     (struct makesound) {300, 500},
//     (struct makesound) {220, 300},
//     (struct makesound) {250, 300},
//     (struct makesound) {300, 300},
//     (struct makesound) {250, 300},
//     (struct makesound) {200, 700} 
//     }
// };

/*
struct makesound * gameovermusic[] = 
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
*/

#include <stdio.h>
#include <time.h>
#include <windows.h>
#define beepgap 3
#define onesecond CLOCKS_PER_SEC

int main()
{
    float secs, mins;
    clock_t starttime, endtime, thistime;
    int seconds;
    _Bool beepon = 1;
    int prevs;

    printf("Enter number of minutes and seconds you want to wait = ");
    scanf("%f %f",&mins, &secs);
    
    mins+=mins+secs/60;             // Everything is calculated in terms of minutes


    starttime = clock();
    endtime = (clock_t)(starttime + mins*60*onesecond);

    thistime = clock();
    seconds = (thistime-starttime)/onesecond;

    for(; thistime<=endtime;)
    {
        if((seconds%beepgap == 0) && beepon)
        {
            for(int i = (mins*60 - seconds)/(beepgap); i>0; i--)
            {
                Beep(1000,70);
            }
            beepon = 0;
            prevs = seconds;
        }
        else
        {
            if(seconds>prevs)
            beepon = 1;
        }
        Sleep(100);
        thistime = clock();
        seconds = (thistime-starttime)/onesecond;
    }

    Beep(750, 100);
    Beep(1000,400);

}

void playtuneusing(struct makesound * s,int l)
{
    for(int i = 0; i<l; i++)
    {
        Beep(s[i].f, s[i].ms);

    }
}
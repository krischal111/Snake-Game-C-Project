#include<stdio.h>
#include<windows.h>

int main()
{
    int y, x;
    char c[100];
    while(!(GetAsyncKeyState(VK_RCONTROL) & 0x01))
    {
        scanf("%d %d", &y, &x);
        sprintf(c, "starty + %d, startx + %d", y-6, x-56);
        printf("%s\n",c);
        //printf("%s\n",SetClipboardData(1,(HANDLE)c));
    }
}
#include<stdio.h>
#include<windows.h>

int main()
{
   printf("sizeof(short) = %d", sizeof(short));
   printf("\nMSB and LSB are set = %x",(int)((short)( (1<< (sizeof(short)*8-1))+1 )) );
   printf("\n%d",'0');
}
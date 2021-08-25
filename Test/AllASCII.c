#include<stdio.h>
int main()
{
    for(unsigned int i=0;i<=255;i++)
    {
        printf("'%d' = ''%c'' = '0%o'\t%s",i,i,i,((i%4==0)?"\n":""));
    }
    while(getchar()!='\n');
}
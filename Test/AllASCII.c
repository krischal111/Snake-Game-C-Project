<<<<<<< HEAD
#include<stdio.h>
int main()
{
    for(unsigned int i=0;i<=255;i++)
    {
        printf("'%d' = ''%c'' = '0%o'\t%s",i,i,i,((i%4==0)?"\n":""));
    }
    while(getchar()!='\n');
=======
#include<stdio.h>
int main()
{
    for(unsigned int i=0;i<=255;i++)
    {
        printf("'%d' = ''%c'' = '0%o'\t%s",i,i,i,((i%4==0)?"\n":""));
    }
    while(getchar()!='\n');
>>>>>>> ef584b26dd893532aae6ae6ba62425e96a138b68
}
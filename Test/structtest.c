#include<stdio.h>

struct structure 
{
    int a;
    int b;
};

struct structure structurefunction()
{
    struct structure str = {.a = 4, .b = 5};
    return str;
} 

int main()
{
    if(structurefunction().a == 4)
    {
        printf("a = 4");
    }

}
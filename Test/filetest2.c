#include <stdio.h>
#include <windows.h>

int main()
{
    char path[50], filename[30];
    char combined[100]="";
    printf("Enter path and a filename = ");
    gets(path);
    fflush(stdin);
    gets(filename);

    strcat(combined,path);
    strcat(combined,"/");
    strcat(combined,filename);

    FILE * myfile = fopen(combined, "w");
    printf("Value of myfile (%s) = %d",combined,myfile);
    printf("(%s)\n",(myfile==NULL)?"NULL":"Not a NULL pointer");
    fclose(myfile);

    if(myfile == NULL)
    {
        char * c = calloc(strlen(path)+10, sizeof(char));
        strcat(c,"mkdir \"");
        strcat(c,path);
        strcat(c,"\"");
        system(c);
    }

    myfile = fopen(combined, "w");
    printf("Value of myfile (%s) = %d",combined,myfile);
    printf("(%s)\n",(myfile==NULL)?"NULL":"Not a NULL pointer");
    fclose(myfile);

}
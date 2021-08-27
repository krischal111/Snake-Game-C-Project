#include<stdio.h>
#include<windows.h>
FILE *fopen_mkdir(char *path, char *mode) ;
void rek_mkdir(char *path) ;

int main()
{
   char filepath[] ="Test1\\Test2\\Test3/Test4/Test5/testfile.txt";
   FILE * myfile = fopen_mkdir(filepath,"w");
   fprintf(myfile,"%s",filepath);
   fclose(myfile);
   return 0;
}

void rek_mkdir(char *path) 
{
   char *sep = strrchr(path, '\\');
   if(sep == NULL)
   sep = strrchr(path,'/');
   if(sep != NULL) 
   {
      *sep = 0;
      rek_mkdir(path);
      *sep = '/';
   }
   char * c = calloc(strlen(path)+10, sizeof(char));
   strcat(c,"mkdir \"");
   strcat(c,path);
   strcat(c,"\"");
   system(c);
   free(c);

}

FILE *fopen_mkdir(char *path, char *mode) 
{
   char *sep = strrchr(path, '/');
   if(sep) 
   { 
      char *path0 = strdup(path);
      path0[ sep - path ] = 0;
      rek_mkdir(path0);
      free(path0);
   }
   return fopen(path,mode);
}
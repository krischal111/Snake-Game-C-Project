void storeBestscorelist(struct scoredata, char *);      // to store provided best score in its place
_Bool readBestscorelist(char *);                         // to read best scores from file
void displayBestscorelist();                            // to display provided best scores

void storeBestscorelist(struct scoredata mybestscore, char * filename)
{
    int isscorenew=0;
    struct scoredata bestscoretemp;                     // Make temporary scoredata structure variable
    for(int i=0; i<5; i++)
    {
        if(Best5Scores[i].score < mybestscore.score)    // If provided best score is larger than already existing
        {
            isscorenew=1;                               // The score is really a best score
            bestscoretemp = Best5Scores[i];             // Store old best score in temporary structure
            Best5Scores[i]  = mybestscore;              // My best score is stored in the record
            mybestscore   = bestscoretemp;              // My best score becomes the old best score so that list is shifted down
        }
    }

    if(isscorenew)                                          // write the best score if really score is best score
    {
    FILE * myfile = fopen(filename,"wb"); // write binary open for writing data directly
    if(myfile==NULL)                                        // If unsuccessful go back without doing anything
    return;
    fwrite(Best5Scores, sizeof(Best5Scores),1,myfile);      // store data into file
    fclose(myfile);                                         // close the file
    }
}

_Bool readBestscorelist(char * filename)
{
    int endcheck = 0;
    struct scoredata score1;                    // Making a temporary score structure variable
    score1.name[0]='\0';                        // Initialize name to nothing, by making first character '\0' i.e. end of string
    score1.score=0;                             // Initializing score to zero
    for(int i = 0; i<5; i++)                    // Initializing all Best5Scores data to 0, failsafe for random garbage initialization
    {
        Best5Scores[i] = score1;                  
    }

    FILE * myfile = fopen(filename,"rb");     // Open the bestscore file
    if(myfile==NULL)                                            // If unsuccessful, return without doing anything
    {
        return 0;
    }
    
    for(int i = 0; i<5; i++)
    {                                                           // Read all best score data, until end of file or 5 best scores reached
        endcheck = fread(&score1,sizeof(struct scoredata),1,myfile);

        if(endcheck == EOF)
        break;

        Best5Scores[i]=score1;
    }

    fclose(myfile);                                             // Close the file and return
    return 1;
}

void displayBestscorelist()
{
    printf(" SN %-30s\t%10s","Names","Scores");             // Displaying the best scores
    for(int i = 0; i<5; i++)
    {
        printf("\n%2d. %-30s\t%10d",i+1,Best5Scores[i].name,Best5Scores[i].score);
    }
    return;
}

void storemenudata(char * filename)
{
    FILE * myfile = fopen(filename,"wb");
    {
    if(myfile == NULL)
    return;
    }
    fwrite(&menudata, sizeof(menudata),1,myfile);
    fclose(myfile);
    return;
}


_Bool readmenudata(char * filename)
{
    FILE * myfile = fopen(filename, "rb");
    {
        if(myfile == NULL)
        return 0;
    }
    fread(&menudata, sizeof(menudata),1,myfile);
    fclose(myfile);
    return 1;
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
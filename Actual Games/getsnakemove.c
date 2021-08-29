int getsnaketomove();
void printsnake();
void displayinfos(struct makegameinfo);
enum direction getdirection(enum direction, struct keyboardinputs);
void movesnake(enum direction);
void fastness();
void startgame(_Bool);
void displaygameelements();
void gamedataupdates();
COORD goodrandomcoord();
void gameover();
void lengthandscoreupdate();

void fastness()
{
    Sleep(900/menudata.level);
}

void startgame(_Bool resumemode)
{
    readBestscorelist(bestscorefilename);

    int s=0;
    int score = 0;

    system("cls");
    ShowConsoleCursor(FALSE);
    if(resumemode)
    {
        score = getsnaketomove();
    }
    else
    {
        // snake initilization
        snake.length = 1;
        snake.body[0].location = (COORD) {0,0};
        snake.body[0].going    = right;

        // gameelements initialization
        gameelements.barriercount = 0;

        gameelements.foood = goodrandomcoord();
        gameelements.nofoodduration = 0;

        gameelements.portalcount = 0;

        gameelements.presenceofpowerfood = TRUE;
        gameelements.powerfoood = goodrandomcoord();
        gameelements.powerfoodduration = 30;

        gameelements.eat50counter=0;

        gameelements.powerupsavailable = FALSE;
        gameelements.powerupson = FALSE;

        // ingameupdate initialization
        ingameupdate = (struct makeingameupdate)
        {
            .gameover = FALSE,
            .lengthincrease = 4,
            .scoreincrease = 0
        };
        score = getsnaketomove();
    }

    if(ingameupdate.gameover)
    {
        gameisrunning = FALSE;
        gameover();
    }
}
 
int getsnaketomove()
{
    enum direction  wheredoigo = snake.body[0].going;
    struct keyboardinputs kb;           // stores all inputs allowed in this game

    displayborder(20,20);
    ShowConsoleCursor(FALSE);

    while(1)
    {
        // Fastness:
        fastness();

        // This is special counter, counts from 0 to 119, which helps with periodic ui things in the game, such as score and things
        incremod(&mod120counter,120);

        // ############################################ controls human or AI mode
        kb=gameinput((menudata.options.AImode?1:0));

        // controls exit or pause of game
        if(kb.esc)        break;
        else if(kb.space)
        do
        {   Sleep(100);
            kb = gameinput(0);              // wait for human input when paused
        }while(kb.nothing);

        // decide direction, and move snake
        wheredoigo = getdirection(snake.body[0].going, kb);
        //############################## spot for increasing/decreasing snake's length

        lengthandscoreupdate();
        movesnake(wheredoigo);
        displaygameelements();
        printsnake();

        gamedataupdates();

        if(ingameupdate.gameover)
        break;

        // Increase score here;

        gameinfo.kb = kb;
        gameinfo.level = menudata.level;
        gameinfo.soundon = 1;
        gameinfo.gametype = 0;
        gameinfo.direction = wheredoigo;
        gameinfo.gametype = menudata.gametype;
        displayinfos(gameinfo);

        cursorloc(0,30);
    }
    if(ingameupdate.gameover)
    gameisrunning = FALSE;
    else
    gameisrunning = TRUE;
    ShowConsoleCursor(TRUE);
    return gameinfo.score;
}

void lengthandscoreupdate()
{
    int l = ingameupdate.lengthincrease;
    int s = ingameupdate.scoreincrease;

    int scorechange = menudata.level / 2;

    if(l<0)     // if length needs to be decreased
    {
        snake.length--;
        l++;        // after length decreases, the negative value of length increased increases towards positive
    }
    else if(l>0)
    {
        snake.length++;
        l--;
    }

    if(s<0)
    {
        scorechange      = (-s)<scorechange?(-s):scorechange;    // if score is to be decrease, it decreases by smaller of |s| or |scorechange|
        gameinfo.score  -= scorechange;
        s               += scorechange;
    }
    else if(s>0)
    {
        scorechange      = s<scorechange?s:scorechange;
        gameinfo.score  += scorechange;
        s               -= scorechange;
    }

    ingameupdate.lengthincrease = l;
    ingameupdate.scoreincrease  = s;
}

enum direction getdirection(enum direction currentdirection, struct keyboardinputs kb)
{
    enum direction d=currentdirection;

    switch(currentdirection)          // decide direction according to input
    {
        case right:
        case left:
        {
            if(kb.down)
            d = down;
            else if(kb.up)
            d = up;
        }
        break;

        case up:
        case down:
        {
            if(kb.right)
            d = right;
            else if(kb.left)
            d = left;
        }
        break;
    }
    return d;
}

void movesnake(enum direction d)
{
    // where whole body moves
    for(int i = snake.length; i>0; i--)
    {
        snake.body[i] = snake.body[i-1];
    }

    // this moves the head to controlled direction
    switch(d)
    {
        case up:
        decremods(&snake.body[0].location.Y, 20);    // Decrements by 1 with modulo 20
        break;

        case down:
        incremods(&snake.body[0].location.Y, 20);    // Increments by 1 with modulo 20 (customcalc.h)
        break;

        case left:
        decremods(&snake.body[0].location.X, 20);    // Comes from opposite end after entering from one
        break;

        case right:
        incremods(&snake.body[0].location.X, 20);    // Comes from opposite end after entering from one
        break;
    }
    snake.body[0].going = d;
}

// Important one
void printsnake()
{
    int l = snake.length;
    // Erase tail:
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "  ");        l--;

    // Print tail:
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\260\260");        l--;
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\261\261");        l--;
    gameprint(snake.body[l].location.Y, snake.body[l].location.X, "\262\262");        l--;


    // These are half tails
    // for(int i = snake.length-1; i>snake.length -4; i--)
    // {
    //     gameprint(snake.body[i].location.Y, snake.body[i].location.X, bodyblock(doubledirectinof(snake.body[i].going, snake.body[i-1].going)));
    // }


    // Print body:
    for(int i = snake.length-4; i>0; i--)
    {
        gameprint(snake.body[i].location.Y, snake.body[i].location.X, "\333\333");

        // Half body mode
        // gameprint(snake.body[i].location.Y, snake.body[i].location.X, bodyblock(doubledirectinof(snake.body[i].going, snake.body[i-1].going)));
    }


    // Print head:
    gameprint(snake.body[0].location.Y, snake.body[0].location.X, "oo");

    cursorloc(0,30);
}

void displayinfos(struct makegameinfo g)
{
    // g.gametype;
    // g.kb;
    // g.level;
    // g.score;
    // g.soundon;
    // g.direction;
    locatecursor(1, 60);
    printf("Level = %10d",g.level);
    locatecursor(2,60);
    printf("Score = %10d",g.score);
    locatecursor(3,60);
    printf("Snake Length = %3d", snake.length);

    locatecursor(5,60);
    switch(g.direction)
    {
        case up:
        printf("Up   ");
        break;

        case down:
        printf("Down ");
        break;

        case left:
        printf("Left ");
        break;

        case right:
        printf("Right");
        break;
    }

    int starty = 6, startx = 60;

    locprint(starty + 0, startx +4,"\332\304\304\304\277");
    locprint(starty + 1, startx +8,"\263\b\b\b\b\b\263");
    locprint(starty + 2, startx + 0,"\332\304\304\304\305\304\304\304\305\304\304\304\277");
    locprint(starty + 3, startx + 12,"\263\b\b\b\b\b\263\b\b\b\b\b\263\b\b\b\b\b\263");
    locprint(starty + 4, startx + 0,"\300\304\304\304\301\304\304\304\301\304\304\304\331");
    locatecursor(starty + 1, startx + 6);
    if(g.kb.up)
    printf("\030");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 6);
    if(g.kb.down)
    printf("\031");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 2);
    if(g.kb.left)
    printf("\021");
    else
    printf(" ");

    locatecursor(starty + 3, startx + 10);
    if(g.kb.right)
    printf("\020");
    else
    printf(" ");
}

void displaygameelements()
{
    for(int i = 0; i<gameelements.portalcount; i++)
    {
        gameprint(gameelements.portal[i].start.Y, gameelements.portal[i].start.X,portal_b_list[i]);
        gameprint(gameelements.portal[i].end.Y, gameelements.portal[i].end.X,portal_b_list[i]);
    }

    for(int i = 0; i<gameelements.barriercount; i++)
    {
        gameprint(gameelements.barrierblock[i].Y, gameelements.barrierblock[i].X, barrier_b);
    }

    gameprint(gameelements.foood.Y, gameelements.foood.X,food_f[mod120counter%2]);

    if(gameelements.presenceofpowerfood)
    {
        gameprint(gameelements.powerfoood.Y, gameelements.powerfoood.X, powerfood_f[mod120counter%2]);
    }
    else
    {
        gameprint(gameelements.powerfoood.Y, gameelements.powerfoood.X, "  ");
    }
}

void gamedataupdates()
{
    // Check for portal, and if on there, teleport.
    for(int i = 0; i<gameelements.portalcount; i++)
    {
        if(coordcmp(gameelements.portal[i].start,snake.body[0].location))
        {
            snake.body[0].location = gameelements.portal[i].end;
            if(menudata.options.soundon)
            playtuneusing(&portaltune);
        }
        else if(coordcmp(gameelements.portal[i].end,snake.body[0].location))
        {
            snake.body[0].location = gameelements.portal[i].start;
            if(menudata.options.soundon)
            playtuneusing(&portaltune);
        }
    }

    // check for barriers, and if on there, game is over
    for(int i = 0; i<gameelements.barriercount; i++)
    {
        if(coordcmp(gameelements.barrierblock[i],snake.body[0].location))
        {
            if(hackmode.enablegameover)
            ingameupdate.gameover = TRUE;
        }
    }

    // check if on food, and if on there, score and length increase + new food spawns
    if(coordcmp(gameelements.foood,snake.body[0].location))
    {
        ingameupdate.scoreincrease += menudata.level;
        ingameupdate.lengthincrease += 1;
        incremod(&gameelements.eat50counter,50);

        gameelements.nofoodduration = 0;
        gameelements.foood = goodrandomcoord();

        if(gameelements.eat50counter %5 == 0)
        {   // powerfood generates only when normol food is eaten + once in 5 periodically
            gameelements.presenceofpowerfood = TRUE;
            gameelements.powerfoood = goodrandomcoord();
            gameelements.powerfoodduration = 40;
            if(menudata.options.soundon)
            // playtuneusing(&powerappeartune);
            ;
        }
        if(menudata.options.soundon)
        playtuneusing(&foodeattune);
    }

    // no food duration increases with each move
    gameelements.nofoodduration++;

    // if no food duration > 100, 1. snake's length and 2. score decreases, 3. no food duration timer resets 
    if(gameelements.nofoodduration>100)
    {
        ingameupdate.lengthincrease--;
        ingameupdate.scoreincrease -= 2*menudata.level;
        gameelements.nofoodduration = 0;
    }

    // if powerfood present
    if(gameelements.presenceofpowerfood)
    {
        // 1. check if snake is eating it, if yes score increase, and length increases
        if(coordcmp(gameelements.powerfoood,snake.body[0].location))
        {
            ingameupdate.scoreincrease += menudata.level * gameelements.powerfoodduration;
            ingameupdate.lengthincrease++;

            // After snake eats it, powerfood expires
            gameelements.presenceofpowerfood = FALSE;

            if(menudata.options.soundon)
            playtuneusing(&powereattune);
        }

        // powerfood duration decreases, each time when powerfood is present and not eaten. 
        gameelements.powerfoodduration--;

        // powerfood expires when not eaten in time.
        if(gameelements.powerfoodduration<=0)
        gameelements.presenceofpowerfood = FALSE;
    }

    // Snake cannot eat itself, it causes game over
    for(int i = 4; i<snake.length; i++)
    if(coordcmp(snake.body[i].location,snake.body[0].location))
    {
        if( hackmode.enablegameover)
        ingameupdate.gameover = TRUE;
    }

    // Snake can get so hungry, that it loses its own body parts, if it loses all his body, game is over.
    if(snake.length == 0)
    {
        if( hackmode.enablegameover)
        ingameupdate.gameover = TRUE;
    }
}

COORD goodrandomcoord()
{
    COORD c;
    _Bool doitagain;

    do
    {
        doitagain = FALSE;      // DOITAGAIN STARTS WITH FALSE ON EACH ITERATION 
        c = randomcoord();

        for(int i = 0; i<gameelements.portalcount; i++)
        {
            doitagain = doitagain || coordcmp(gameelements.portal[i].start, c);
            doitagain = doitagain || coordcmp(gameelements.portal[i].end  , c);
        }

        for(int i = 0; i<gameelements.barriercount; i++)
        doitagain = doitagain || coordcmp(gameelements.barrierblock[i],c);

        doitagain = doitagain || coordcmp(gameelements.foood,c);

        doitagain = doitagain || coordcmp(gameelements.powerfoood,c);

        for(int i = 0; i<snake.length; i++)
        doitagain = doitagain || coordcmp(snake.body[i].location,c);

    // but when random coordinate matches with anything else, doitagain becomes true, causing loop to DO IT AGAIN
    }while(doitagain);
    return c;
}

void gameover()
{
    Sleep(500);
    if(menudata.options.soundon)
    playtuneusing(&gameovertune);
    system("cls");
    _Bool newhighscore = FALSE;
    struct keyboardinputs kb;
    locprint(3,5,"Game Over\n");

    
    for(int i = 0; (i<5) && !(newhighscore) ; i++)
    {
        newhighscore = newhighscore || (gameinfo.score > Best5Scores[i].score);
    }
    
    if(!newhighscore)   // when no high score
    {
        printf("\n Your score was: %d",gameinfo.score);
        Sleep(500);
        for(int i = 0; i<50; i++)
        {
            Sleep(100);
            kb = menuinput();
            if(kb.esc || kb.enter)
            break;
        }
    }
    else
    {
        struct scoredata mybestscore;
        
        fflush(stdin);
        mybestscore.score = gameinfo.score;
        printf("\nCongrats!!! You set a new High Score. \nYour score = %d\n", gameinfo.score);
        printf("Please enter your good name: ");
        Sleep(500);
        if(menudata.options.AImode)
        {
            strcpy(mybestscore.name,"Artificial Intelligence");
            ShowConsoleCursor(TRUE);
            for(int i = 0; i<strlen(mybestscore.name); i++)
            {
                printf("%c",*("Artificial Intelligence"+i));
                Sleep(70);
            }
            printf("\n");
        }
        else
        {
            ShowConsoleCursor(TRUE);
            fflush(stdin);
            Sleep(200);
            // fgets(mybestscore.name,30,stdin);
            scantext(mybestscore.name, 30);
        }
        storeBestscorelist(mybestscore, bestscorefilename);
    }
    
}

char mainmenu[7][20] =
{
    "Resume",
    "Start new game",
    "Options",
    "Levels",
    "High score",
    "Help",
    "Exit"
};

char optionMenu[3][20] =
{
    "Sound on/off",
    "Control mode",
    "Choose map"
};


char soundMenu[2][20] =
{
    "Sound on",
    "Sound off"
};


char redefineMenu[4][20] =
{
    "Up",
    "Down",
    "Left",
    "Right"
};


char AIMenu[2][6]=
{
    "Human",
    "AI"
};


char mapMenu[4][20] =
{
    "No Map",
    "Choose Map",
    "Random Map",
    "Campaign map"
};


// Sujan will make the map, and update the names here:
char chooseMap[5][20] = 
{
    "Map 1",
    "Map 2",
    "Map 3",
    "Map 4",
    "Map 5"
};


char levelsMenu[10][10] =
{
    "Level 1",
    "Level 2",
    "Level 3",
    "Level 4",
    "Level 5",
    "Level 6",
    "Level 7",
    "Level 8",
    "Level 9",
    "Level 10"
};

char helpText[2000] = 

" Navigation in the Menu:\n"
" Press <arrow keys> or WASD to navigate through the menu. You can also press <number key> to go to specified option directly.\n"
" Press <enter> to enter the selected option in the menu. Press <esc> to go back.\n"
" Any setting you change will be saved when you launch this game again.\n\n"

" Navigation in the Game:\n"
" Use <arrow keys> or WASD to move the snake in human mode. Press <enter> key to activate the powerups mode..\n"
" Press <space> key to pause the game. Press <esc> key to go back to menu, where you can continue later.\n"
" Collect fruits to increase length. Boosts will speed up movement and also score you more.\n"
" Have fun!\n\n"

" Info about the Snake Game:\n"
" Snake game is the game of snake having adventures, in a location that exists on a flat torus universe.\n"
" That means opposite sides of the map are connected, and when anything exits from one side, it enters from opposite side.\n"
" Snake can move in any four directions. Snake cannot eat itself, because it dies from its own venom \n"

" Though snake produces its own venom, ingesting it causes nothing, beause it is not poisonous.\n"
" If snake doesn't eat for long time, it start to lose unnecessary body parts to save energy, starting from tail.\n"
" If snakes loses all its body parts, it dies, and the game is over.\n\n"

" In campaign mode, snake has to eat required number of foods, and gain enough energy to open portal to new map.\n"
" Once all maps are completed, game concludes.\n\n"

" About the Developers:\n"
" This game was made by 4 students of Pulchowk Campus, IOE, Nepal, as a project for C programming in the first semester.\n"
" Game Design        :  Krischal Khanal.\n"
" Map Design         :  Sujan Basnet.\n"
" Menu and UI Design :  Aavash Bhattarai, Krischal Khanal\n"
" Documentation      :  Manish Yadav, Aavash Bhattarai, Sujan Basnet, Krischal Khanal"
" "

"\n\n"
" Press enter to redirect to main menu.";

char confirmText[2][5] =
{
    "Yes",
    "No"
};

#include "fuck.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <ncurses.h>
#include <vector>
#include <unistd.h> //usleep

const std::vector<std::vector<const char*>> Fuck::letters = {};
const std::vector<std::vector<const char*>> Fuck::man = {
    {
     "                                     ",
     "                /^^^\\                ",
     "               o\"  ) )               ",
     "               (--  |                ",
     "                 | |                 ",
     "                 |  |                ",
     "                 || |                ",
     "                 || |                ",
     "                 / _)                ",
     "                / /\\ \\               ",
     "               ()|  ()\\              ",
     "               | |    \\ \\            ",
     "              O__|    O_/            "
    },

    {
"                                     ",
"                                     ",
"                /^^^\\                ",
"               o\"  ) )               ",
"               (--  |                ",
"                 | |                 ",
"                 |  |                ",
"                 || |                ",
"                 || |                ",
"                /\\  )                ",
"               / /\\ \\                ",
"              ()|  ()\\               ",
"              | |    \\ \\             ",
"             O__|    O_/             "
    },

    {
"                                     ",
"                                     ",
"                /^^^\\                ",
"               o\"  ) )               ",
"               (--  |                ",
"                 | |                 ",
"                 |  |                ",
"                 || |                ",
"                 || |                ",
"                 |  )                ",
"                 | |                 ",
"                 | |                 ",
"                 | |                 ",
"                O__|                 ",
    },

    {
"                                     ",
"                                     ",
"                /^^^\\                ",
"              (| \"o\" |)              ",
"               (_---_)               ",
"               __| |__               ",
"              |  . .  |              ",
"              | |   | |              ",
"              | |   | |              ",
"             /  ||Y||  \\             ",
"                || ||                ",
"                () ()                ",
"                || ||                ",
"               ooO Ooo               ",
    },

    {
     "     _                         _     ",
     "    |_|                       |_|    ",
     "    | |         /^^^\\         | |    ",
     "   _| |_      (| \"o\" |)      _| |_   ",
     " _| | | | _    (_---_)    _ | | | |_ ",
     "| | | | |' |    _| |_    | `| | | | |",
     "\\          /   / . . \\   \\          /",
     " \\        /  / /|   |\\ \\  \\        / ",
     "   \\    /  / /  |   |  \\ \\  \\    /   ",
     "     \\  \\/ /    ||Y||    \\ \\/  /     ",
     "       \\_/      || ||      \\_/       ",
     "                () ()                ",
     "                || ||                ",
     "               ooO Ooo               "
    }
};

void Fuck::handleArgs(char* &arg) {
    static bool stringDetected = false;
    static bool stringFinished = false;
    bool isOption = false;
    char key = '-';

    if (arg[0] == key) isOption = true;

    if (isOption){
        stringFinished = true;
    }

    if ( !strcmp(arg,"-h") || !strcmp(arg,"--help")){
        printf("%s",helpMessage);
        exit(0);
    }else if ( !strcmp(arg,"-v") || !strcmp(arg,"--version")){
        printf("fuck %s",version);
        exit(0);
    }else if ( !strcmp(arg,"-l") || !strcmp(arg,"--love")){
        isLoved = true;
    }else if ( !strcmp(arg,"-e") || !strcmp(arg,"--exaggerate")){
        isExaggerated = true;
    }else if (isOption){
        std::cout<<"fuck: invalid option -- '"<<arg<<"'\nTry 'fuck --help' for more information.\n";
        exit(0);
    }else{
        if (stringDetected == false) {
            fuckThing.clear(); //clear java
        }

        if (!stringFinished){
            stringDetected = true;
            fuckThing.push_back(arg);
        }else{
            std::cout<<"fuck: invalid argument -- '"<<arg<<"'\nTry 'fuck --help' for more information.\n";
            exit(0);
        }
    }
}

Fuck::Fuck(){
    bool isExaggerated = false;
    bool isLoved = false;
    
    manWidth = strlen(man[0][0]);
    manHeight = man[0].size();
}

void Fuck::runLinux(){
    
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr,true);

    getmaxyx(stdscr, w_Height, w_Width); //gives row and column numbers
                                         
    maxbobbleLen = std::max(w_Width/2,30);

    man_x = w_Width-1;

    if (w_Height > manHeight)
        man_y = ( w_Height - manHeight ) / 2;
    else
        man_y = 0;
    
    while(true){
        //eskiyi temizleyecak bir fonksiyon yaz.
        for(int i=0; i<std::min(w_Height,manHeight); i++)
            for(int j=0; j<std::min(std::min(w_Width,manWidth),(w_Width-man_x)); j++)
                mvaddch(man_x+i,man_y+j,' ');

        man_x += 3;

        counter%=3;
        counter++;

        if ((man_x - 3) <= abs(w_Width - manWidth)/2)
        {
            printMan(3);
            usleep(70000);
            printMan(4);
            printSpeech();
            usleep(100000);
        }
        else
            printMan(counter);


        usleep(30000);
    }
    
}
void Fuck::runWindows(){
}
void Fuck::runApple(){
}

void Fuck::printMan(int idx){
    for(int i=0; i<std::min(w_Height,manHeight); i++)
        for(int j=0; j<std::min(std::min(w_Width,manWidth),(w_Width-man_x)); j++)
            mvaddch(man_x+i,man_y+j,man[idx][i][j]);
    refresh();
}

void Fuck::printSpeech(){
    int bobbleLen;
    if (fuckThing.size() < maxbobbleLen){
       bobbleLen = fuckThing.size();  
    }else{
        bobbleLen = maxbobbleLen;
    }

    // find man coordinates and print according to that
}

void Fuck::temp(){
    for(std::string a : fuckThing)
        std::cout<<a<<std::endl;
}

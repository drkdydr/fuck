#include "fuck.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <ncurses.h>
#include <vector>

const std::vector<std::vector<const char*>> Fuck::letters = {};
const std::vector<std::vector<const char*>> Fuck::man = {
    {
     "                                     ",
     "                /^^^\                ",
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
"               o\"  ) \)               ",
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
    }else{
        //handle unknown options, 
        //space seperated but not inside quote situations, 
    }
}

void Fuck::runLinux(){
    printf("Wow linux btw?!");
    // initscr();
    // cbreak();
    // noecho();
    // nodelay(stdscr,true);

}
void Fuck::runWindows(){
}
void Fuck::runApple(){
}

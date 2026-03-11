#include <ncurses.h>
#include <string.h> // for strcmp
#include <iostream> // for std
#include "fuck.h"


int main (int argc, char *argv[]){

    Fuck *f = new Fuck();

    if (argc > 1)
        for (int i=1; i<argc; i++) f->handleArgs(argv[i]);
    f->temp();
    #ifdef __linux__ // for fucking communist femboys
        // f->runLinux();
    #elif _WIN32 // for stupid windows fuckers
        printf("This application is not compatible with Windows currently. (But it will.)");
        // f->runWindows();
    #elif __APPLE__ // for rich people
        printf("This application is not compatible with MacOS (and it won't)");
        // Linux and mac are alike because of both are UNIX based
        // This means maybe I can transform app easily for mac.
        // f->runApple();
    #endif


    return 0;  
}

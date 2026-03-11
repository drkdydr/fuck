#ifndef FUCK_H
#define FUCK_H

#include <iostream>
#include <vector>

class Fuck {
    
    const char* version = "v.0.0";
    const char* helpMessage =
    "fuck is small terminal program to fuck the things that makes you mad\n\
    usage: fuck [-le] <message> (java for default) \n\
    \n\
    options:\n\
    \n\
           -h, --help           : prints this help message\n\
           -v, --version        : prints version info\n\
    \n\
           -l, -love            : love, do not hate (fuck sitcoms)\n\
           -e, --exaggerate     : exaggerates your feelings and prints message\n\
                                  in big characters (not working yet.) \n\
           -n, --no-prefix      : removes the prefixes (like 'FUCK' or 'I LOVE')\n\
    \n\
    'fuck' made with hate and pain please enjoy!\n"; // custom prefix eklemeye çok üşendim.

    std::vector<std::string> fuckThing = {"JAVA"};

    static const std::vector<std::vector<const char*>> letters; // ascii code of letter - 32 = index
    static const std::vector<std::vector<const char*>> man; // i0: walking frame1
                                                            // i1: stand still sideways
                                                            // i2: walking frame2
                                                            // i3: stand still towards you
                                                            // i4: does the hand thingy

    bool isExaggerated;
    bool isLoved;
    bool noPrefix;
    
    int w_Height;
    int w_Width;
    int manHeight;
    int manWidth;
    int man_x;
    int man_y;
    int letterHeight;
    int letterWidth;

    int maxbubbleLen;
    int speechLen; 

    int counter;

    void printSpeech();
    void clearSpeech();
    void printMan(int idx);

    public: 
        Fuck();
        void handleArgs(char* &arg); 
        void runLinux();
        void runWindows(); //This time I will make app windows compatible
        void runApple(); 

};


#endif

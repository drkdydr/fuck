#include "fuck.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h> //usleep
#include <vector>

#define ANGER_LIMIT 15

// LOGIC:
// if you push back so many times he gets mad (ANGER)
// if he has hate he swears (HATE)

//todo: 
// bubble'da ok kısmında ufak bir problem var.

const std::vector<std::vector<const char *>> Fuck::man = {
    {"                                     ",
     "                                     ",
     "                /^^^\\                ",
     "               o\"  ) )               ",
     "               (--  _|               ",
     "                 | |                 ",
     "                 |  |                ",
     "                 || |                ",
     "                 || |                ",
     "                 / _)                ",
     "                / /\\ \\               ",
     "               ()|  ()\\              ",
     "               | |    \\ \\            ",
     "              O__|    O_/            "},

    {"                                     ",
     "                                     ",
     "                /^^^\\                ",
     "               o\"  ) )               ",
     "               (--  _|               ",
     "                 | |                 ",
     "                 |  |                ",
     "                 || |                ",
     "                 || |                ",
     "                 |  )                ",
     "                 | |                 ",
     "                 | |                 ",
     "                 | |                 ",
     "                O__|                 "},

    {"                                     ",
     "                                     ",
     "                /^^^\\                ",
     "               o\"  ) )               ",
     "               (--  _|               ",
     "                 | |                 ",
     "                 |  |                ",
     "                 || |                ",
     "                 || |                ",
     "                /\\  )                ",
     "               / /\\ \\                ",
     "              ()|  ()\\               ",
     "              | |    \\ \\             ",
     "             O__|    O_/             "},

    {"                                     ",
     "                                     ",
     "                /^^^\\                ",
     "               o\"  ) )               ",
     "               (--  _|               ",
     "                 | |                 ",
     "                 |  |                ",
     "                 || |                ",
     "                 || |                ",
     "                 |  )                ",
     "                 | |                 ",
     "                 | |                 ",
     "                 | |                 ",
     "                O__|                 "},

    {"                                     ",
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
     "               ooO Ooo               "},

    {"     _                         _     ",
     "    |_|                       |_|    ",
     "    | |         /\\^/\\         | |    ",
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
     "               ooO Ooo               "},

    {
        "                                     ",
        "      _                       _      ",
        "     '(|        /^^^\\        |)`     ",
        "     | |      (| \"o\" |)      | |     ",
        " ____| |       (_---_)       | |____ ",
        "(__[)   \\       _| |_       /   (]__)",
        "(___[)   \\     / . . \\     /   (]___)",
        "(___[)    \\  / /|   |\\ \\  /    (]___)",
        " (_[)____  \\/ / |   | \\ \\/  ____(]_) ",
        "         \\_ /   ||Y||   \\ _/         ",
        "                || ||                ",
        "                () ()                ",
        "                || ||                ",
        "               ooO Ooo               "
    }
};

void Fuck::handleArgs(char *&arg) {
  static bool stringDetected = false;
  static bool stringFinished = false;
  bool isOption = false;
  char key = '-';

  if (arg[0] == key)
    isOption = true;

  if (isOption && stringDetected) {
    speechLen--; // remove extra space in line 149
    stringFinished = true;
  }

  if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
    printf("%s", helpMessage);
    exit(0);
  } else if (!strcmp(arg, "-v") || !strcmp(arg, "--version")) {
    printf("fuck %s", version);
    exit(0);
  } else if (!strcmp(arg, "-l") || !strcmp(arg, "--love")) {
    isLoved = true;
  } else if (!strcmp(arg, "-e") || !strcmp(arg, "--exaggerate")){
    isExaggerated = true;
  } else if (!strcmp(arg, "-n") || !strcmp(arg, "--no-prefix")) {
    noPrefix = true;
  } else if (isOption) {
    std::cout << "fuck: invalid option -- '" << arg
              << "'\nTry 'fuck --help' for more information.\n";
    exit(0);
  } else {

    if (stringDetected == false) {
      fuckThing.clear(); // clear java
      speechLen = 0;
    }

    if (!stringFinished) {
      stringDetected = true;

      fuckThing.push_back(arg);
      speechLen += strlen(arg) + 1; // for space
                                    
    } else {
      std::cout << "fuck: invalid argument -- '" << arg
                << "'\nTry 'fuck --help' for more information.\n";
      exit(0);
    }
  }
}

Fuck::Fuck() {
    isExaggerated = false;
  isLoved = false;
  noPrefix = false;

  speechLen = 4; // because of JAVA

  manWidth = strlen(man[0][0]);
  manHeight = man[0].size();
}

void Fuck::exaggerate(){
    for(std::string &s : fuckThing)
        for(int i = 0; s[i] != '\0'; i++)
            s[i] = std::toupper(static_cast<unsigned char>(s[i]));
}

void Fuck::runLinux() {

  bool didThingy = false; // have mascott did the hand thing
                          
  int input;
  int angerPoint = 0; // times you press KEY_RIGHT

  if (isExaggerated) exaggerate();

  // initializing/configuring ncurses
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  curs_set(0); // makes cursor invincible
  clear();
  refresh();
  keypad(stdscr, TRUE); // for arrow key macros

  getmaxyx(stdscr, w_Height, w_Width); // gives row and column numbers

  maxbubbleLen = std::max(w_Width / 2, 30);

  man_x = w_Width - 1;

  if (w_Height > manHeight)
    man_y = (w_Height - manHeight) / 2;
  else
    man_y = 0;

  while (man_x >= -manWidth && (input = getch())) {
        flushinp(); // delete key buffer
    for (int i = 0; i < std::min(w_Height, manHeight); i++)
      for (int j = 0;
           j < std::min(std::min(w_Width, manWidth), (w_Width - man_x)); j++)
        mvaddch(man_y + i, man_x + j, ' ');

    if (input == KEY_LEFT){ // make him faster
          man_x = std::max(-manWidth, man_x - 5); // cannot go further than end point
    }else if (input == KEY_RIGHT){ // make him struggle
          man_x = std::min(w_Width - 1, man_x + 5); // cannot go further than start point
          counter = 1; // both feet on ground (struggling effect)
            angerPoint ++;
    }

    if (angerPoint == ANGER_LIMIT){
      angerPoint = 0;
      makeHandThing(true, true); // has hate and has anger
    } 
      // also we hold info that "did the hand thingy" if mascott goes back of the center again does not did hand thing again

    counter %= 4; // which man apperance will shown

    if (((man_x - 3) <= abs(w_Width - manWidth) / 2) && !didThingy) { 
        man_x = abs(w_Width - manWidth) / 2; // place mascott middle
      didThingy = true; // I did not like the way I handle.
      if (isLoved){
            makeHandThing(false, false); // has no hate nor anger (love)
      }else{
            makeHandThing(true, false); // has hate but no anger (hate)
      }
    } else
        man_x-=3;
      printMan(counter);

    usleep(300000); // wait before next iteration (0.3 sec)
    counter++;
  }
  clear();
  refresh();
  endwin();
} 
void Fuck::runWindows() {}
void Fuck::runApple() {}

void Fuck::printMan(int idx) {
  for (int i = 0; i < std::min(w_Height, manHeight); i++)
    for (int j = 0;
         j < std::min(std::min(w_Width, manWidth), (w_Width - man_x)); j++)
      mvaddch(man_y + i, man_x + j, man[idx][i][j]);
  refresh();
}

void Fuck::printSpeech(bool hasAnger) {

  std::vector<std::string> bufferList;
  std::string buffer;


  if (hasAnger) // if 
        buffer = "STOP IT!!";
  else if (noPrefix)
    buffer = "";
  else if (isLoved)
    buffer = "I LOVE ";
  else 
    buffer = "FUCK ";

  speechLen += buffer.size();

  int bubbleLen;

  if (speechLen < maxbubbleLen) {
    bubbleLen = speechLen;
  } else {
    bubbleLen = maxbubbleLen;
  }

  // anger mode overrides hate thing 
  if (!hasAnger){
        for (std::string s : fuckThing) {

          if (buffer.size() + s.size() > bubbleLen) {
            buffer.pop_back();
            bufferList.push_back(buffer);
            buffer = "";
          } else {
            buffer.append(s);
            buffer.append(" ");
          }
        }
  }

  if (!buffer.empty()) {
    buffer.pop_back(); // removes last character of string (space in this case)
    bufferList.push_back(buffer);
  }

  // print borders

  for (int i = 1; i <= (bubbleLen + 2) / 2; i++) {
        mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) - i, '_');
        mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) + i - 1, '_');
    if (i != 1){
        mvaddch(man_y - 2, man_x + (manWidth / 2) - i, '_');
        mvaddch(man_y - 2, man_x + (manWidth / 2) + i - 1, '_');
    }else{
        mvaddch(man_y - 1, man_x + (manWidth / 2) - 1, '\\');
        mvaddch(man_y - 1, man_x + (manWidth / 2), '/');
    }
  }

  for (int i = 0; i < bufferList.size() + 2; i++) {
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) - (bubbleLen + 4) / 2, '|');
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) + ((bubbleLen + 4) / 2) - 1, '|');
  }

  // print words
  for (int i = 0; i < bufferList.size(); i++) {
    mvprintw(man_y - 2 - bufferList.size() + i,
             man_x + (manWidth / 2) - (bufferList[i].size() / 2), "%s",
             bufferList[i].c_str());
  }

  refresh();
  usleep(3000000);

  // remove bubble 
  for (int i = 1; i <= (bubbleLen + 2) / 2; i++) {
        mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) - i, ' ');
        mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) + i - 1, ' ');
    if (i != 1){
        mvaddch(man_y - 2, man_x + (manWidth / 2) - i, ' ');
        mvaddch(man_y - 2, man_x + (manWidth / 2) + i - 1, ' ');
    }else{
        mvaddch(man_y - 1, man_x + (manWidth / 2) - 1, ' ');
        mvaddch(man_y - 1, man_x + (manWidth / 2), ' ');
    }
  }

  for (int i = 0; i < bufferList.size() + 2; i++) {
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) - (bubbleLen + 4) / 2, ' ');
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) + ((bubbleLen + 4) / 2) - 1, ' ');
  }

  // print words
  for (int i = 0; i < bufferList.size(); i++) {
    mvaddch(man_y - 2 - bufferList.size() + i,
            man_x + (manWidth / 2) - (bufferList[i].size() / 2),' ');
    for(int j = 1; j<bufferList[i].size(); j++)
        addch(' ');
  }
  refresh();
  speechLen -= buffer.size(); // revert size change

}

void Fuck::makeHandThing(bool hasHate, bool hasAnger){
      printMan(4);
      usleep(1000000); // usleep sleeps for microseconds (10^6 microseconds = 1 second)
      if (hasHate) // hate
          printMan(5); // hate
      else
          printMan(6); // love
      usleep(200000);
      printSpeech(hasAnger);
      usleep(600000);
      printMan(4);
      usleep(200000);
      flushinp(); // delete inputs that came while sleeping
}

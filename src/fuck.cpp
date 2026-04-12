#include "fuck.h"
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h> //usleep
#include <vector>

//todo: 
// custom prefix opsiyonu eklenecek.
// exaggerate flag'i çalışır hale getirilecek.
// bubble'da ok kısmında ufak bir problem var.

const std::vector<std::vector<const char *>> Fuck::letters = {};
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
  } else if (!strcmp(arg, "-e") || !strcmp(arg, "--exaggerate")) {
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

void Fuck::runLinux() {

  bool didThingy = false;

  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  curs_set(0); // makes cursor invincible
  clear();
  refresh();

  getmaxyx(stdscr, w_Height, w_Width); // gives row and column numbers

  maxbubbleLen = std::max(w_Width / 2, 30);

  man_x = w_Width - 1;

  if (w_Height > manHeight)
    man_y = (w_Height - manHeight) / 2;
  else
    man_y = 0;

  while (man_x >= -manWidth) {
    for (int i = 0; i < std::min(w_Height, manHeight); i++)
      for (int j = 0;
           j < std::min(std::min(w_Width, manWidth), (w_Width - man_x)); j++)
        mvaddch(man_y + i, man_x + j, ' ');


    counter %= 4;

    if (((man_x - 3) <= abs(w_Width - manWidth) / 2) && !didThingy) { 
        man_x = abs(w_Width - manWidth) / 2;
      didThingy = true; // I did not like the way I handle.
      printMan(4);
      usleep(1000000); // usleep sleeps for microseconds (10^6 microseconds = 1 second)
      if (isLoved)
          printMan(6);
      else
          printMan(5);
      usleep(200000);
      printSpeech();
      usleep(600000);
      printMan(4);
      usleep(200000);
    } else
        man_x-=3;
      printMan(counter);

    usleep(300000);
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

void Fuck::printSpeech() {

  std::vector<std::string> bufferList;
  std::string buffer;

  if (noPrefix)
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
  if (!buffer.empty()) {
    buffer.pop_back(); // removes last character of string (space in this case)
    bufferList.push_back(buffer);
  }

  // print borders
  mvprintw(man_y - 1, man_x + ((manWidth - 2) / 2), "\\/");
  mvprintw(man_y - (bufferList.size() + 4), man_x + (manWidth / 2), "__");
  for (int i = 0; i < (bubbleLen + 2) / 2; i++) {
    mvaddch(man_y - 2, man_x + (manWidth / 2) - 1 - i, '_');
    mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) - 1 - i, '_');
    mvaddch(man_y - 2, man_x + (manWidth / 2) + 1 + i, '_');
    mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) + 1 + i, '_');
  }
  for (int i = 0; i < bufferList.size() + 2; i++) {
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) - (bubbleLen + 4) / 2, '|');
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) + (bubbleLen + 4) / 2, '|');
  }

  // print words
  for (int i = 0; i < bufferList.size(); i++) {
    mvprintw(man_y - 2 - bufferList.size() + i,
             man_x + (manWidth / 2) - (bufferList[i].size() / 2), "%s",
             bufferList[i].c_str());
  }

  refresh();
  usleep(3000000);

  // remove bubble (I couldn't think a way that makes more sense)
  mvprintw(man_y - 1, man_x + ((manWidth - 2) / 2), "  ");
  mvprintw(man_y - (bufferList.size() + 4), man_x + (manWidth / 2), "  ");
  for (int i = 0; i < (bubbleLen + 2) / 2; i++) {
    mvaddch(man_y - 2, man_x + (manWidth / 2) - 1- i, ' ');
    mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) - 1 - i, ' ');
    mvaddch(man_y - 2, man_x + (manWidth / 2) + 1 + i, ' ');
    mvaddch(man_y - (bufferList.size() + 4), man_x + (manWidth / 2) + 1 + i, ' ');
  }
  for (int i = 0; i < bufferList.size() + 2; i++) {
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) - (bubbleLen + 4) / 2, ' ');
    mvaddch(man_y - 2 - i, man_x + (manWidth / 2) + (bubbleLen + 4) / 2, ' ');
  }

  // print words
  for (int i = 0; i < bufferList.size(); i++) {
    mvaddch(man_y - 2 - bufferList.size() + i,
            man_x + (manWidth / 2) - (bufferList[i].size() / 2),' ');
    for(int j = 1; j<bufferList[i].size(); j++)
        addch(' ');
  }
  refresh();

}


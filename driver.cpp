#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

//GLOBAL VARIABLES
const int BUFF_SIZE = 90000;
char buffer[BUFF_SIZE];
vector<string> hold(800," ");

//MENU OPEN OPTION
int Mopen(const char * input){
  int fd = open(input, O_RDWR);
  int n=read(fd,buffer,BUFF_SIZE);
  hold.resize(n);
  for(int i=0; i<hold.size();i++)
    {
      hold[i] = buffer[i];
      cout<<hold[i];
    }
}

//MENU SAVE OPTION
int save(){}

//MENU SAVE AS OPTION
int saveAs(const char * input){

}

//DRIVER
int main(int argc, const char* argv[]){
  Mopen(argv[1]);
  
  initscr();
  keypad(stdscr, true);
  int brow, bcols;
  getmaxyx(stdscr, brow, bcols);

  WINDOW* textWin = newwin(brow-2, bcols-10, 1, 5);
  box(textWin, 0, 0);

  mvwprintw(stdscr, 0, 0, "F1: Menu");
  mvwprintw(stdscr, 0, bcols/2 - 2, "CSCI 1730 Editor!");

  wrefresh(stdscr);
  wrefresh(textWin);

  wgetch(textWin);
  endwin();

  
}



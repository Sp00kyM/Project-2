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
int fd;

//MENU FUNCTION
void Menu(){
}
//MENU OPEN OPTION
int Mopen(const char * input, WINDOW * win){
  fd = open(input, O_RDWR|O_CREAT);
  int bytes_in=read(fd,buffer,BUFF_SIZE);
  hold.resize(bytes_in);
  int buffplace = 0;
  for(int i=0; i<hold.size();i++)
    {
        hold[i] = buffer[i];
      waddstr(win,hold[i].c_str());
    }
}
//MENU SAVE OPTION
int Msave(){
  write(fd,buffer,hold.size());
}
int MsaveAs(const char* input){
  fd = open(input, O_RDWR|O_CREAT,0666);
  write(fd,buffer,hold.size());
}
int main(int argc, const char* argv[]){
  initscr();
  keypad(stdscr, TRUE);
  int brow, bcols;
  getmaxyx(stdscr, brow, bcols);
  noecho();

  WINDOW* textWin = newwin(brow-2, bcols-10, 1, 5);
  //WINDOW * textWin = newpad(brow-2,bcols-10);
  box(textWin, 0, 0);
  keypad(textWin, TRUE);
  mvwprintw(stdscr, 0, 0, "F1: Menu");
  mvwprintw(stdscr, 0, bcols/2 - 2, "CSCI 1730 Editor!");

  Mopen(argv[1],textWin);
  wrefresh(stdscr);
  wrefresh(textWin);

  int ch;
  int cursorY, cursorX;
  getyx(textWin, cursorY, cursorX);
  wmove(textWin,0,0);
  //bounds for textbox
  int textrow, textcol;
  int place = textrow;
  getmaxyx(textWin,textrow,textcol);
  while(ch = getch()){
    wmove(textWin,cursorY,cursorX);
    if(ch == KEY_UP){
      cursorY--;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else if(ch == KEY_DOWN){
      place++;
      if(place > textrow){
        cursorY--;
        wmove(textWin,textrow,0);
        wscrl(textWin,1);
        waddch(textWin,hold[1][1]);
        wrefresh(textWin);
      }
      cursorY++;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else if(ch == KEY_LEFT){
      cursorX--;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
   }
    else if(ch==KEY_RIGHT){
      cursorX++;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else if(ch == KEY_DC || ch == KEY_BACKSPACE || ch == '\b'){
      cursorX--;
      wmove(textWin,cursorY,cursorX);
      wdelch(textWin);
      wrefresh(textWin);
    }
    else if(ch == KEY_ENTER || ch == '\n'){
      waddch(textWin,'\n');
      cursorY++;
      cursorX =0;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else{
      waddch(textWin,ch);
      cursorX++;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    wmove(textWin,cursorY,cursorX);
  }
}

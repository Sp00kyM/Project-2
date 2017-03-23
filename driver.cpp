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
  int fix = 0;
  for(int i=0; i<hold.size()&& fix<BUFF_SIZE;i++)
    {
      while((buffer[fix]!='\n')&&fix<BUFF_SIZE){
            hold[i]+=buffer[fix];
            fix++;
      }
      fix++;
      waddstr(win,hold[i].c_str());
      waddch(win,'\n');
    }
}
//MENU SAVE OPTION
int Msave(){
  write(fd,buffer,hold.size());
}

//MENU SAVE AS OPTION
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
  scrollok(textWin,TRUE);
  int ch;
  int cursorY, cursorX;
  getyx(textWin, cursorY, cursorX);
  wmove(textWin,0,0);
  //bounds for textbox
  int textrow, textcol;
  getmaxyx(textWin,textrow,textcol);
  int place = textrow;
  while(ch = getch()){
    wmove(textWin,cursorY,cursorX);
    if(ch == KEY_UP){
      if(place >= textrow){
        place--;
        place = place - textrow;
        cursorY++;
        cursorX=0;
        wscrl(textWin,-1);
        mvwaddstr(textWin,cursorY,cursorX,hold[place].c_str());
        wrefresh(textWin);
      }
      cursorY--;
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else if(ch == KEY_DOWN){
      if(place < hold.size()-1){
        place++;
        cursorY--;
        cursorX=0;
        wscrl(textWin,1);
        mvwaddstr(textWin,cursorY,cursorX,hold[place].c_str());
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


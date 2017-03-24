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
  bool showMenu = false;
  keypad(stdscr, TRUE);
  int brow, bcols, trow, tcols;
  getmaxyx(stdscr, brow, bcols);
  noecho();

  WINDOW* boxWin = newwin(brow-2, bcols-10, 1, 5);
  box(boxWin, 0, 0);
  getmaxyx(boxWin, trow, tcols);
  WINDOW* textWin = newwin(trow-2, tcols-2, 2, 6);
  WINDOW* menuWin = newwin(10, 20, trow/2, tcols/2);
  WINDOW* textWin = newwin(brow-2, bcols-10, 1, 5);
  //WINDOW * textWin = newpad(brow-2,bcols-10);
  box(menuWin, 0, 0);
  keypad(textWin, TRUE);
  mvwhline(menuWin, 2, 1, 0, 18);
  mvwprintw(stdscr, 0, 0, "F1: Menu");
  mvwprintw(stdscr, 0, bcols/2 - 2, "CSCI 1730 Editor!");
  displayText(textWin);

  PANEL* menu = new_panel(menuWin);
  
  string menuOps[4] = {"Open", "Save", "Save As", "Exit"};
  int menuChoice;
  int highlight = 0;
  
  mvwprintw(menuWin, 1, 7, "My Menu");
  
  Mopen(argv[1],textWin);
  wrefresh(stdscr);
  wrefresh(textWin);
  wrefresh(boxWin);
  wrefresh(menuWin);
  scrollok(textWin,TRUE);
  int ch;
  int cursorY, cursorX;
  getyx(textWin, cursorY, cursorX);
  wmove(textWin,0,0);
  hide_panel(menu);
  //bounds for textbox
  int textrow, textcol;
  getmaxyx(textWin,textrow,textcol);
  int place = textrow;
  update_panels();
  doupdate();
  while(ch = getch()){
    wmove(textWin,cursorY,cursorX);
    for(int i = 0; i < 4; i++) {
      if(i == highlight)
        wattron(menuWin, A_REVERSE);
      mvwprintw(menuWin, i+3, 1, menuOps[i].c_str());
      wattroff(menuWin, A_REVERSE);
    }

    if(showMenu == true){
       if(ch == KEY_F(1)){
        hide_panel(menu);
        showMenu = false;
      }
      switch(ch) {
      case KEY_UP:
        highlight--;
        if(highlight == -1)
          highlight = 0;
        break;
      case KEY_DOWN:
        highlight++;
        if(highlight == 4)
          highlight = 3;
        break;
      default:
        break;
      }
    }
    else {
      if(ch == KEY_F(1)){
        show_panel(menu);
        showMenu = true;
      }
    }
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
  update_panels();
    doupdate();
}


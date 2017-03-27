#include <sys/stat.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <panel.h>

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
      //cout<<hold[i];                                                                                                                                                                    
    }
}

//MENU SAVE OPTION                                                                                                                                                                        
int save(){}

//MENU SAVE AS OPTION                                                                                                                                                                     
int saveAs(const char * input){

}

void displayText(WINDOW* win){
  int y, x;
  getbegyx(win, y, x);
  for(int i = 0; i <hold.size(); i++){
    waddch(win, *hold[i].c_str());
  }

}

//DRIVER                                                                                                                                                                                  
int main(int argc, const char* argv[]){
  Mopen(argv[1]);
  bool showMenu = false;
  initscr();
  keypad(stdscr, TRUE);
  int brow, bcols, trow, tcols;
  getmaxyx(stdscr, brow, bcols);

  WINDOW* boxWin = newwin(brow-2, bcols-10, 1, 5);
  box(boxWin, 0, 0);
  getmaxyx(boxWin, trow, tcols);
  WINDOW* textWin = newwin(trow-2, tcols-2, 2, 6);
  WINDOW* menuWin = newwin(10, 20, trow/2, tcols/2);                                                                                              

  box(menuWin, 0, 0);                                                                                                                                                       

  PANEL* menu = new_panel(menuWin);                                                                                                                                       

  mvwhline(menuWin, 2, 1, 0, 18);
  mvwprintw(stdscr, 0, 0, "F1: Menu");
  mvwprintw(stdscr, 0, bcols/2 - 2, "CSCI 1730 Editor!");
  displayText(textWin);

  string menuOps[4] = {"Open", "Save", "Save As", "Exit"};
  int menuChoice;
  int highlight = 0;

  mvwprintw(menuWin, 1, 7, "My Menu");

  wrefresh(stdscr);
  wrefresh(boxWin);
  wrefresh(textWin);
  wrefresh(menuWin);
  int ch;
  hide_panel(menu);
  update_panels();
  doupdate();

  while(ch = getch()){
    for(int i = 0; i < 4; i++) {
      if(i == highlight)
        wattron(menuWin, A_REVERSE);
      mvwprintw(menuWin, i+3, 1, menuOps[i].c_str());
      wattroff(menuWin, A_REVERSE);
    }

    choice = wgetch(menuWin);

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

    update_panels();
    doupdate();
  }
  endwin();
}


#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <panel.h>
#include <fstream>

using namespace std;

//GLOBAL VARIABLES
const int BUFF_SIZE = 900000;
char buffer[BUFF_SIZE];
vector<string> hold(800," ");
int fd;
const char * fileHold;

//MENU FUNCTION

void Menu(){
}
//MENU OPEN OPTION
int Mopen(const char * input, WINDOW * win){
  const char * fileHold = input;
  fd = open(input, O_RDWR|O_CREAT);
  int bytes_in=read(fd,buffer,BUFF_SIZE);
  hold.resize(bytes_in);
  int fix = 0;
  int linecount;
  for(int i=0; i<hold.size()&& fix<BUFF_SIZE;i++)
    {
      while((buffer[fix]!='\n')&&fix<BUFF_SIZE){
            hold[i]+=buffer[fix];
            fix++;
      }
      fix++;
      waddstr(win,hold[i].c_str());
      waddch(win,'\n');
      linecount++;
    }
  close(fd);
  hold.resize(linecount);
}
//MENU SAVE OPTION
int Msave(){
  string line;
  int linecount=0;
  ofstream myfile;
  myfile.open(fileHold);
  myfile.clear();
  for(int i=0; i<hold.size();i++){
    myfile<<hold[i];
    myfile<<'\n';
  }
}

//MENU SAVE AS OPTION
int MsaveAs(const char* input){
  fileHold = input;
  fd = open(input,O_RDWR|O_CREAT);
  close(fd);
  string line;
  int linecount=0;
  ofstream myfile;
  myfile.open(input);
  myfile.clear();
  for(int i=0; i<hold.size();i++){
    myfile<<hold[i];
    myfile<<'\n';
  }
}
int main(int argc, const char* argv[]){
  initscr();
  // bool showMenu = false;///////////////////////////////////////////////////  keypad(stdscr, TRUE);
  int brow, bcols, textrow, textcol;
  getmaxyx(stdscr, brow, bcols);
  noecho();

  WINDOW* boxWin = newwin(brow-2, bcols-10, 1, 5);
  box(boxWin, 0, 0);

  getmaxyx(boxWin, textrow, textcol);
  WINDOW* textWin = newwin(textrow-2, textcol-2, 2, 6);
  //WINDOW* menuWin = newwin(10, 20, textrow/2, textcol/2);
  // box(menuWin, 0, 0);
  keypad(textWin, TRUE);
  mvwprintw(stdscr, 0, 0, "F1: Menu");
  mvwprintw(stdscr, 0, bcols/2 - 2, "CSCI 1730 Editor!");

  //PANEL* menu = new_panel(menuWin);

  //mvwhline(menuWin, 2, 1, 0, 18);

  //string menuOps[4] = {"Open", "Save", "Save As", "Exit"};
  //int menuChoice;
  //int highlight = 0;

  //mvwprintw(menuWin, 1, 7, "My Menu");

  // wrefresh(menuWin);
  //hide_panel(menu);
  //update_panels();
  //doupdate();

  Mopen(argv[1],textWin);
  //wrefresh(stdscr);
  //wrefresh(textWin);
  //wrefresh(boxWin);
  int ch;
  int cursorY, cursorX;
  getyx(textWin, cursorY, cursorX);
  //bounds for textbox
  getmaxyx(textWin,textrow,textcol);
  int place = textrow;
  scrollok(textWin,TRUE);
  wrefresh(stdscr);
  wrefresh(boxWin);
  wrefresh(textWin);
  //wrefresh(menuWin);

  //hide_panel(menu);

  //update_panels();
  //doupdate();
  while(ch = getch()){
    /* //menu stuff
       for(int i = 0; i < 4; i++) {
    if(i == highlight)
      wattron(menuWin, A_REVERSE);
    mvwprintw(menuWin, i+3, 1, menuOps[i].c_str());
    wattroff(menuWin, A_REVERSE);
    //wrefresh(menuWin);
    }*/


    /*
     if(showMenu == true) {
      wrefresh(menuWin);
      if(ch == KEY_F(1)){
        hide_panel(menu);
        showMenu = false;
        //wrefresh(menuWin);/////////////////////////////
        update_panels();
        doupdate();
        wrefresh(textWin);
        refresh();
        //wrefresh(textWin);/////////////////////////////////
      }

      switch(ch){
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
      //break;

    }

    else if(showMenu == false) {
      //      hide_panel(menu);
      //wrefresh(textWin);
      refresh();
      if(ch == KEY_F(1)){
        show_panel(menu);
        showMenu = true;
        wrefresh(menuWin);
        //wrefresh(textWin);
        //refresh();
        update_panels();
        doupdate();
        wrefresh(textWin);
      }
    */
    //if(showMenu = false){
    //hide_panel(menu);
    //update_panels();
    //doupdate();
      //wmove(textWin,cursorY,cursorX);
      //      if(ch == KEY_F(1)){
      //show_panel(menu);
      //showMenu = true;
      //update_panels();
      //doupdate();
      //wrefresh(menuWin);
    //}
      if(ch == KEY_UP){
        if(place!=0){
          if(cursorY==1){
            place--;
            cursorY++;
            cursorX=0;
            wscrl(textWin,-1);
            mvwaddstr(textWin,cursorY,cursorX,hold[place].c_str());//cstr
            wrefresh(textWin);
            place++;
          }
          place--;
          if(cursorY!=0){
            cursorY--;
            wmove(textWin,cursorY,cursorX);
            wrefresh(textWin);
          }
        }
      }
      else if(ch == KEY_DOWN){
        if(place < hold.size()-1 && cursorY == textrow){
          place++;
          cursorY--;
          cursorX=0;
          wscrl(textWin,1);
          mvwaddstr(textWin,cursorY,cursorX,hold[place].c_str());//cstr
          wrefresh(textWin);
          place--;
        }
        if(place<hold.size()-1){
        place++;
        cursorY++;
        wmove(textWin,cursorY,cursorX);
        }
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
        int Xhold = cursorX;
        wmove(textWin,cursorY,cursorX);
        wdelch(textWin);
        char * wholeline = new char[textcol];
        mvwinnstr(textWin,cursorY,0,wholeline,textcol);
        hold[place-1] = string(wholeline);
        cursorX = Xhold;
        wmove(textWin,cursorY,cursorX);
        wrefresh(textWin);
      }
      else if(ch == KEY_ENTER || ch == '\n'){
        hold.resize(hold.size()+1);//prepping for a new line
        int Xhold = cursorX;//grabbing the X coordinate

        //grabbing the beginning of the line
        wmove(textWin,cursorY,0);
        char * preentergrab = new char[cursorX];
        winnstr(textWin,preentergrab,cursorX);
        wmove(textWin,cursorY,cursorX);
        string preenterhold = preentergrab;
        //grabbing the rest of the line and storing it
        char * postentergrab = new char [textcol-cursorX];
        winnstr(textWin, postentergrab, textcol-cursorX);
        string postenterhold = postentergrab;
        //updating the two line affected
        hold[place-1] = preenterhold;
        for(int k = hold.size();k > place;k--){
          hold[k] = hold[k-1];
        }
        hold[place] = postenterhold;
        cursorY++;
        cursorX=0;
        //updating the line
        waddch(textWin,'\n');
        place++;
        wrefresh(textWin);//////////////////////////////////////////////////////
        //for loop to do shit
        scrollok(textWin,FALSE);
        wmove(textWin, cursorY,0);
        for(int i = place;i<hold.size();i++){
          waddstr(textWin,hold[i].c_str());//cstr
          waddch(textWin,'\n');
        }
        scrollok(textWin,TRUE);
        wmove(textWin,cursorY,cursorX);
        wprintw(textWin,postenterhold.c_str());//cstr
        wmove(textWin,cursorY,cursorX);
        wrefresh(textWin);
      }
      else{
        cursorX++;
        int Xhold = cursorX;
        cursorX--;
        char * linegrab = new char[textcol-cursorX];
        winnstr(textWin,linegrab, textcol-cursorX);
        string linehold = linegrab;
        waddch(tex for(int i=0;i<linehold.size();i++){
          cursorX++;
          wmove(textWin, cursorY,cursorX);
          waddch(textWin,linehold[i]);
        }
        char * wholeline = new char[textcol];
        mvwinnstr(textWin,cursorY,0,wholeline,textcol);
        hold[place-1] = string(wholeline);
        cursorX = Xhold;
        wmove(textWin,cursorY,cursorX);
        wrefresh(textWin);
      }
    /*
      if(showMenu == true) {
        if(ch == KEY_F(1)){
          hide_panel(menu);
          showMenu = false;
          }
      }
    */
        /*
      }
      switch(ch){
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
        */
    //else if(ch == KEY_F(1)){
        //show_panel(menu);
        //showMenu = true;
        //}
      //update_panels();
      //doupdate();
  wrefresh(textWin);
  if(ch == KEY_F(4)){MsaveAs("ducky.txt"); break;}
  }
  endwin();
  //endwin();

}
tWin,ch);
          

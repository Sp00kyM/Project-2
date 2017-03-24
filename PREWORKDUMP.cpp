 else if(ch == KEY_DC || ch == KEY_BACKSPACE || ch == '\b'){
      cursorX--;
      wmove(textWin,cursorY,cursorX);
      wdelch(textWin);
      wrefresh(textWin);
    }
 else if(ch == KEY_ENTER || ch == '\n'){
      //grabbing the beginning of the line
      char * preentergrab = new char[-(cursorX-textcol)];
      winnstr(textWin,preentergrab,-(cursorX-textcol));
      string preenterhold = preentergrab;
      //grabbing the rest of the line and storing it
      char * postentergrab = new char [textcol-cursorX];
      winnstr(textWin, postentergrab, textcol-cursorX);
      string postenterhold = postentergrab;
      place++;
      hold[place] = postenterhold;
      hold[place-1] = preenterhold;
      cursorY++;
      cursorX=0;
      //updating the line
      waddch(textWin,'\n');
      scrollok(textWin,TRUE);
      wmove(textWin,cursorY,cursorX);
      wprintw(textWin,postenterhold.c_str());
      wmove(textWin,cursorY,cursorX);
      wrefresh(textWin);
    }
    else{
      cursorX++;
      waddch(textWin,ch);
      int Xhold = cursorX;
      char * linegrab = new char[textcol-cursorX];
      winnstr(textWin,linegrab, textcol-cursorX);
      string linehold = linegrab;
      for(int i=0;i<linehold.size();i++){
        cursorX++;
        wmove(textWin, cursorY,cursorX);
        waddch(textWin,linehold[i]);
      }

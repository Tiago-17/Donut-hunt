#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"

void windowSetUp(int * cols, int * rows, WINDOW * wnd) {
	// Window Setup
	getmaxyx(wnd,*cols,*rows);
	raw();
	noecho();
	keypad(stdscr,true);
	refresh();
	clear();
}

void getInput(int key, Player *user) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, user);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, user);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, user);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, user);
    break;
  case 'q':
  case 'Q':
    refresh();
    endwin();
    break;
  case 'P':
  case 'p':
    // prevRoom[*roomsAmount] = *randomizePosition(wnd, &prevRoom[*roomsAmount - 1],*rows,*cols,firstPosition,0);
    // *roomsAmount++;
    updatePlayerPosition(user);
    break;
  default:
    break;
  }
}
/*  This is an important function, which will handle the input taken from the user keyboard
    Keys: 
    {
      W: Go up
      A: Go left
      S: Go down
      D: Go right
      Q: Quit the game
      P: Delete the actual map and create an entire new map again 
    } 
*/





int main() {
	Player * user;
	WINDOW *wnd = initscr();
	srand(time(NULL));

	// Variables
	int cols, rows, roomsAmount = 0, maxRooms = 30;
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation

	// Setup ncurses window in CLI
	windowSetUp(&cols, &rows, wnd);

  // map matrix setup
  Tile ** map = matrixSetup(rows, cols);

	// player and map setups
	NormalRoom * roomsArray[maxRooms];
	NormalRoom * firstRoom = createRoom(cols,rows,map);
	user = playerSetUp(firstRoom);
	roomsArray[roomsAmount] = firstRoom;
	updatePlayerPosition(user);

  // create the whole map
	NormalRoom * room = roomsArray[0];
  createMap(wnd,room,roomsArray,maxRooms,firstPosition,cols,rows,map);

	// game loop
	while(1) {
		if (roomsAmount == maxRooms) break;
		int ch = getch();
		getInput(ch, user);
	}

	endwin();
	return 0;
}
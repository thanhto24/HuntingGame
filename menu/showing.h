#pragma once
#include "header.h"

//functions used to design screen
HWND WINAPI GetConsoleWindowNT(void);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void clearScreen();
void gotoxy(SHORT x, SHORT y);
void TextColor(int color);

//blocks' moving in different level
void level2(mainScreen &game);
void level3(mainScreen &game);
void level4(mainScreen &game);
void level5(mainScreen &game);
void levelMove(mainScreen &game, int level, int roundSelect);

//move the blue key
void drawUnKey(mainScreen &game, int yr, int xr, char art[50][120], int y1, int x1);
void drawKey(mainScreen &game, int yr, int xr, int y1, int x1);
void drawHint(mainScreen &game, int y, int x);

//draw the board for playing
void drawBorder(int color);
void drawingLine(mainScreen &game, int i, int j);
void drawingBoard(mainScreen &game, char bgArt[40][120]);
void drawOutsideBoard(int &level, Player &user, bool accountLogedIn);

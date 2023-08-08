#pragma once
#include "header.h"

//functions used to design screen
HWND WINAPI GetConsoleWindowNT(void);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void clearScreen();
void gotoxy(SHORT x, SHORT y);
void TextColor(int color);


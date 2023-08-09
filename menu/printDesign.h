#pragma once
#include "header.h"

//functions used to design screen
HWND WINAPI GetConsoleWindowNT(void);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void clearScreen();
void gotoxy(SHORT x, SHORT y);
void TextColor(int color);

//functions for showing Menu Choice box
void title();
void printSignUpBoard(int directX, int directY);
void printSignInBoard(int directX, int directY);
void printChoiceBox(int directX, int directY);
void deleteChoiceBox(int directX, int directY);
void printMenuBox(int directX, int directY);
void deleteMenuBox(int directX, int directY);

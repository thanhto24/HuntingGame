#pragma once
#include "header.h"

//BIG FUNCTION
// exact menu
void generateMenu(int &roundSelect, int Choice, string FileName);

//SMALL FUNCTION
// function get orders from keyboard
void getEvents(int &roundSelect, int &Choice); 
// split up from printMenu, make it easy to change later
void printCredit();
// function show interactive screen 
void printMenu(int roundSelect, int Choice, string FileName);

#ifndef HEADER_H
#define HEADER_H
// =====    INCLUDE LIBRARY     =====
#pragma once
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <vector>
#include <iomanip>
#include <new>
#include <chrono>
#include <thread>
// #include <mmsystem.h>

#include <windows.h> //color, gotoxy, ...
#include <conio.h>   //kbhit
#include <string.h>
#include <string>
#include <sstream>
#include <stdlib.h> //random
#include <fstream>  // file

// #include "showing.h"
// #include "account.h"
// #include "printDesign.h"
// #include "menu.h"

// =====    DEFINE      =====

#define KeyUp 72
#define KeyDown 80
#define KeyLeft 75
#define KeyRight 77
#define Space 32
#define Esc 27

#define ii pair<int, int>
#define iii pair<ii, int>
#define f first
#define s second
#define mp make_pair

// =====    NAMESPACE   =====

using namespace std;
using namespace std::chrono;

// =====    STRUCT      =====

struct characterBlockInfor{
    int TDiffer;                //totalDifferentCharacter
    int *charBlock;             //characterBlock
    int TChar;                  //totalCharacter - number of remaining blocks in game
};

struct State
{
    int numRow, numCol;         // size of saved board (8bytes)
};

struct Player
{
    char username[17];          //17bytes
    char password[15];          //15bytes
    int record;                 //score(4bytes)
    State savedStage; 
};

struct Point
{
    int x, y;
};

struct Snake
{
    vector<Point> body;
    Point head, tail;
    int direction;
    bool feed;
    bool turnRed = false;
};

struct Board
{
    bool game_active;
    int **viewBoard;
    int hei, wid;
    int level;
    int hh, mm, ss;
    bool haveBigApple;
    int score;
    int scoreToPass;
    bool isWin;
    vector<iii> gate; // pair<<vị trí (x, y)>, giá trị>
    vector<iii> teleport;
    vector<Point> landMines;
    bool updated;
};

struct User
{
    string fileName;
    // vector<pair<int, int>> bodyOfSnake;
    vector<Point> bodyOfSnake;
    int points;
    int level;
    int direct;
    int record;
    char account[99];
    char password[99];
    // char fileName[99];
};

// =====    VARIABLE    =====

//244 = 15*16 + 4 red text white background
const int RW = 244;
//242 = 15*16 + 2 green text white background
const int GreenW = 242;
//240 = 15*16 + 0 black text white background
const int BlackW = 240;
const int boxColor = 2*16+ 15;
const int titleColor = 2*16 + 15;

const char MSSV[] = " 22127174221273222212738822127441";
const int snakeColor = 14;
const int appleColor = 221;
const int bigAppleColor = 238;
const int wallColor = 68;
const int gateColor = 3;
const int basicColor = 7;
const int backgroundColor = 114;
const int teleportGateColor = 176;
const int landMineColor = 16;

#endif
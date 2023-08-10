#pragma once
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <new>
#include <fstream>
//#include <chrono>
#include <thread>
#include <windows.h>
#include <mmsystem.h>

#pragma pack (1)
//#pragma comment(lib, "winmm.lib")

using namespace std;
//using namespace std::chrono;

#define ii pair<int, int>
#define iii pair<ii, int>
#define f first
#define s second
#define mp make_pair
#define KeyUp 72
#define KeyDown 80
#define KeyLeft 75
#define KeyRight 77
#define Space 32
#define Esc 27

const char MSSV[] = " 22127174221273222212738822127441";

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

struct State
{
    int numRow, numCol;         // size of saved board (8bytes)
};

struct Player
{
    char account[20];			//20bytes
    char password[20];			//20bytes
};

struct User
{
    string fileName;
    // vector<pair<int, int>> bodyOfSnake;
    vector<Point> bodyOfSnake;
    int points;
    int level;
    int direct = 0;
    //int record;
	Player player;
};

//244 = 15*16 + 4 red text white background
const int RW = 244;
//242 = 15*16 + 2 green text white background
const int GreenW = 242;
//240 = 15*16 + 0 black text white background
const int BlackW = 240;
const int boxColor = 2*16+ 15;
const int titleColor = 2*16 + 15;
#include "account.cpp"
#include "printDesign.cpp"
#include "menu.cpp"
